/*	$OpenBSD: altq_cbq.c,v 1.4 2002/03/14 03:15:50 millert Exp $	*/
/*	$KAME: altq_cbq.c,v 1.9 2000/12/14 08:12:45 thorpej Exp $	*/

/*
 * Copyright (c) Sun Microsystems, Inc. 1993-1998 All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the SMCC Technology
 *      Development Group at Sun Microsystems, Inc.
 *
 * 4. The name of the Sun Microsystems, Inc nor may not be used to endorse or
 *      promote products derived from this software without specific prior
 *      written permission.
 *
 * SUN MICROSYSTEMS DOES NOT CLAIM MERCHANTABILITY OF THIS SOFTWARE OR THE
 * SUITABILITY OF THIS SOFTWARE FOR ANY PARTICULAR PURPOSE.  The software is
 * provided "as is" without express or implied warranty of any kind.
 *  
 * These notices must be retained in any copies of any part of this software.
 */

#include <sys/param.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <net/if_types.h>
#include <netinet/in.h>

#include <altq/altq.h>
#include <altq/altq_conf.h>
#include <altq/altq_cbq.h>

/*
 * Local Data structures.
 */
static cbq_state_t *cbq_list = NULL;

/*
 * Forward Declarations.
 */

static int	cbq_add_class(struct cbq_add_class *);
static int	cbq_delete_class(struct cbq_delete_class *);
static int	cbq_modify_class(struct cbq_modify_class *);
static int 	cbq_class_create(cbq_state_t *, struct cbq_add_class *,
				 struct rm_class *, struct rm_class *);
static int	cbq_class_destroy(cbq_state_t *, struct rm_class *);
static struct rm_class  *clh_to_clp(cbq_state_t *, u_long);
static int	cbq_add_filter(struct cbq_add_filter *);
static int	cbq_delete_filter(struct cbq_delete_filter *);

static int	cbq_clear_hierarchy(struct cbq_interface *);
static int	cbq_clear_interface(cbq_state_t *);
static int	cbq_request(struct ifaltq *, int, void *);
static int	cbq_set_enable(struct cbq_interface *, int);
static int	cbq_ifattach(struct cbq_interface *);
static int	cbq_ifdetach(struct cbq_interface *);
static int	cbq_enqueue(struct ifaltq *, struct mbuf *,
			    struct altq_pktattr *);
static struct mbuf 	*cbq_dequeue(struct ifaltq *, int);
static void	cbqrestart(struct ifaltq *);
static void 	get_class_stats(class_stats_t *, struct rm_class *);
static int 	cbq_getstats(struct cbq_getstats *);
static void	cbq_purge(cbq_state_t *);

static int
cbq_add_class(acp)
	struct cbq_add_class *acp;
{
	char		*ifacename;
	struct rm_class	*borrow, *parent;
	cbq_state_t	*cbqp;

	ifacename = acp->cbq_iface.cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);

	/* check parameters */
	if (acp->cbq_class.priority >= RM_MAXPRIO ||
	    acp->cbq_class.maxq > CBQ_MAXQSIZE)
		return (EINVAL);

	/* Get pointers to parent and borrow classes.  */
	parent = clh_to_clp(cbqp, acp->cbq_class.parent_class_handle);
	borrow = clh_to_clp(cbqp, acp->cbq_class.borrow_class_handle);

	/*
	 * A class must borrow from it's parent or it can not
	 * borrow at all.  Hence, borrow can be null.
	 */
	if (parent == NULL && (acp->cbq_class.flags & CBQCLF_ROOTCLASS) == 0) {
		printf("cbq_add_class: no parent class!\n");
		return (EINVAL);
	}

	if ((borrow != parent)  && (borrow != NULL)) {
		printf("cbq_add_class: borrow class != parent\n");
		return (EINVAL);
	}

	return cbq_class_create(cbqp, acp, parent, borrow);
}

static int
cbq_delete_class(dcp)
	struct cbq_delete_class *dcp;
{
	char		*ifacename;
	struct rm_class	*cl;
	cbq_state_t	*cbqp;

	ifacename = dcp->cbq_iface.cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);

	if ((cl = clh_to_clp(cbqp, dcp->cbq_class_handle)) == NULL)
		return (EINVAL);

	/* if we are a parent class, then return an error. */
	if (is_a_parent_class(cl))
		return (EINVAL);

	/* if a filter has a reference to this class delete the filter */
	acc_discard_filters(&cbqp->cbq_classifier, cl, 0);

	return cbq_class_destroy(cbqp, cl);
}

static int
cbq_modify_class(acp)
	struct cbq_modify_class *acp;
{
	char		*ifacename;
	struct rm_class	*cl;
	cbq_state_t	*cbqp;

	ifacename = acp->cbq_iface.cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);

	/* Get pointer to this class */
	if ((cl = clh_to_clp(cbqp, acp->cbq_class_handle)) == NULL)
		return (EINVAL);

	if (rmc_modclass(cl, acp->cbq_class.nano_sec_per_byte,
			 acp->cbq_class.maxq, acp->cbq_class.maxidle,
			 acp->cbq_class.minidle, acp->cbq_class.offtime,
			 acp->cbq_class.pktsize) < 0)
		return (EINVAL);
	return (0);
}

/*
 * struct rm_class *
 * cbq_class_create(cbq_mod_state_t *cbqp, struct cbq_add_class *acp,
 *		u_long handle, struct rm_class *parent,
 *		struct rm_class *borrow)
 *
 * This function create a new traffic class in the CBQ class hierarchy of
 * given paramters.  The class that created is either the root, default,
 * or a new dynamic class.  If CBQ is not initilaized, the the root class
 * will be created.
 */
static int
cbq_class_create(cbqp, acp, parent, borrow)
	cbq_state_t *cbqp;
	struct cbq_add_class *acp;
	struct rm_class *parent, *borrow;
{
	struct rm_class	*cl;
	cbq_class_spec_t *spec = &acp->cbq_class;
	u_long		chandle;
	int		i;

	/*
	 * allocate class handle
	 */
	switch (spec->flags & CBQCLF_CLASSMASK) {
	case CBQCLF_ROOTCLASS:
		if (parent != NULL)
			return (EINVAL);
		if (cbqp->ifnp.root_)
			return (EINVAL);
		chandle = ROOT_CLASS_HANDLE;
		break;
	case CBQCLF_DEFCLASS:
		if (cbqp->ifnp.default_)
			return (EINVAL);
		chandle = DEFAULT_CLASS_HANDLE;
		break;
	case CBQCLF_CTLCLASS:
		if (cbqp->ifnp.ctl_)
			return (EINVAL);
		chandle = CTL_CLASS_HANDLE;
		break;
	case 0:
		/* find a free class slot */
		for (i = 0; i < CBQ_MAX_CLASSES; i++)
			if (cbqp->cbq_class_tbl[i] == NULL)
				break;
		if (i == CBQ_MAX_CLASSES)
			return (ENOSPC);
		chandle = (u_long)i;
		break;
	default:
		/* more than two flags bits set */
		return (EINVAL);
	}

	/*
	 * create a class.  if this is a root class, initialize the
	 * interface.
	 */
	if (chandle == ROOT_CLASS_HANDLE) {
		rmc_init(cbqp->ifnp.ifq_, &cbqp->ifnp, spec->nano_sec_per_byte,
			 cbqrestart, spec->maxq, RM_MAXQUEUED,
			 spec->maxidle, spec->minidle, spec->offtime,
			 spec->flags);
		cl = cbqp->ifnp.root_;
	} else {
		cl = rmc_newclass(spec->priority,
				  &cbqp->ifnp, spec->nano_sec_per_byte,
				  rmc_delay_action, spec->maxq, parent, borrow,
				  spec->maxidle, spec->minidle, spec->offtime,
				  spec->pktsize, spec->flags);
	}
	if (cl == NULL)
		return (ENOMEM);

	/* return handle to user space. */
	acp->cbq_class_handle = chandle;

	cl->stats_.handle = chandle;
	cl->stats_.depth = cl->depth_;

	/* save the allocated class */
	switch (chandle) {
	case NULL_CLASS_HANDLE:
	case ROOT_CLASS_HANDLE:
		break;
	case DEFAULT_CLASS_HANDLE:
		cbqp->ifnp.default_ = cl;
		break;
	case CTL_CLASS_HANDLE:
		cbqp->ifnp.ctl_ = cl;
		break;
	default:
		cbqp->cbq_class_tbl[chandle] = cl;
		break;
	}
	return (0);
}

/*
 * int
 * cbq_class_destroy(cbq_mod_state_t *, struct rm_class *) - This
 *	function destroys a given traffic class.  Before destorying
 *	the class, all traffic for that class is released.
 */
static int
cbq_class_destroy(cbqp, cl)
	cbq_state_t *cbqp;
	struct rm_class *cl;
{
	u_long	chandle;

	chandle = cl->stats_.handle;

	/* delete the class */
	rmc_delete_class(&cbqp->ifnp, cl);

	/*
	 * free the class handle
	 */
	switch (chandle) {
	case ROOT_CLASS_HANDLE:
		cbqp->ifnp.root_ = NULL;
		break;
	case DEFAULT_CLASS_HANDLE:
		cbqp->ifnp.default_ = NULL;
		break;
	case CTL_CLASS_HANDLE:
		cbqp->ifnp.ctl_ = NULL;
		break;
	case NULL_CLASS_HANDLE:
		break;
	default:
		if (chandle >= CBQ_MAX_CLASSES)
			break;
		cbqp->cbq_class_tbl[chandle] = NULL;
	}

	return (0);
}

/* convert class handle to class pointer */
static struct rm_class *
clh_to_clp(cbqp, chandle)
	cbq_state_t *cbqp;
	u_long chandle;
{
	switch (chandle) {
	case NULL_CLASS_HANDLE:
		return (NULL);
	case ROOT_CLASS_HANDLE:
		return (cbqp->ifnp.root_);
	case DEFAULT_CLASS_HANDLE:
		return (cbqp->ifnp.default_);
	case CTL_CLASS_HANDLE:
		return (cbqp->ifnp.ctl_);
	}

	if (chandle >= CBQ_MAX_CLASSES)
		return (NULL);

	return (cbqp->cbq_class_tbl[chandle]);
}

static int
cbq_add_filter(afp)
	struct cbq_add_filter *afp;
{
	char		*ifacename;
	cbq_state_t	*cbqp;
	struct rm_class	*cl;

	ifacename = afp->cbq_iface.cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);

	/* Get the pointer to class. */
	if ((cl = clh_to_clp(cbqp, afp->cbq_class_handle)) == NULL)
		return (EINVAL);

	return acc_add_filter(&cbqp->cbq_classifier, &afp->cbq_filter,
			      cl, &afp->cbq_filter_handle);
}

static int
cbq_delete_filter(dfp)
	struct cbq_delete_filter *dfp;
{
	char		*ifacename;
	cbq_state_t	*cbqp;
    
	ifacename = dfp->cbq_iface.cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);
    
	return acc_delete_filter(&cbqp->cbq_classifier,
				 dfp->cbq_filter_handle);
}

/*
 * cbq_clear_hierarchy deletes all classes and their filters on the
 * given interface.
 */
static int
cbq_clear_hierarchy(ifacep)
	struct cbq_interface *ifacep;
{
	char		*ifacename;
	cbq_state_t	*cbqp;

	ifacename = ifacep->cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);

	return cbq_clear_interface(cbqp);
}

static int
cbq_clear_interface(cbqp)
	cbq_state_t *cbqp;
{
	int		again, i;
	struct rm_class	*cl;

	/* free the filters for this interface */
	acc_discard_filters(&cbqp->cbq_classifier, NULL, 1);

	/* clear out the classes now */
	do {
		again = 0;
		for (i = 0; i < CBQ_MAX_CLASSES; i++) {
			if ((cl = cbqp->cbq_class_tbl[i]) != NULL) {
				if (is_a_parent_class(cl))
					again++;
				else {
					cbq_class_destroy(cbqp, cl);
					cbqp->cbq_class_tbl[i] = NULL;
				}
			}
		}
		if (cbqp->ifnp.ctl_ != NULL &&
		    !is_a_parent_class(cbqp->ifnp.ctl_)) {
			cbq_class_destroy(cbqp, cbqp->ifnp.ctl_);
			cbqp->ifnp.ctl_ = NULL;
		}
		if (cbqp->ifnp.default_ != NULL &&
		    !is_a_parent_class(cbqp->ifnp.default_)) {
			cbq_class_destroy(cbqp, cbqp->ifnp.default_);
			cbqp->ifnp.default_ = NULL;
		}
		if (cbqp->ifnp.root_ != NULL &&
		    !is_a_parent_class(cbqp->ifnp.root_)) {
			cbq_class_destroy(cbqp, cbqp->ifnp.root_);
			cbqp->ifnp.root_ = NULL;
		}
	} while (again);

	return (0);
}

static int
cbq_request(ifq, req, arg)
	struct ifaltq *ifq;
	int req;
	void *arg;
{
	cbq_state_t *cbqp = (cbq_state_t *)ifq->altq_disc;

	switch (req) {
	case ALTRQ_PURGE:
		cbq_purge(cbqp);
		break;
	}
	return (0);
}

/*
 * static int
 * cbq_set_enable(struct cbq_enable *ep) - this function processed the
 *	ioctl request to enable class based queueing.  It searches the list
 *	of interfaces for the specified interface and then enables CBQ on
 *	that interface.
 *
 *	Returns:	0, for no error.
 *			EBADF, for specified inteface not found.
 */

static int
cbq_set_enable(ep, enable)
	struct cbq_interface *ep;
	int enable;
{
	int 	error = 0;
	cbq_state_t	*cbqp;
	char 	*ifacename;

	ifacename = ep->cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);

	switch (enable) {
	case ENABLE:
		if (cbqp->ifnp.root_ == NULL || cbqp->ifnp.default_ == NULL ||
		    cbqp->ifnp.ctl_ == NULL) {
			if (cbqp->ifnp.root_ == NULL)
				printf("No Root Class for %s\n", ifacename);
			if (cbqp->ifnp.default_ == NULL)
				printf("No Default Class for %s\n", ifacename);
			if (cbqp->ifnp.ctl_ == NULL)
				printf("No Control Class for %s\n", ifacename);
			error = EINVAL;
		} else if ((error = altq_enable(cbqp->ifnp.ifq_)) == 0) {
			cbqp->cbq_qlen = 0;
		}
		break;

	case DISABLE:
		error = altq_disable(cbqp->ifnp.ifq_);
		break;
	}
	return (error);
}

/* copy the stats info in rm_class to class_states_t */
static void
get_class_stats(statsp, cl)
	class_stats_t	*statsp;
	struct rm_class	*cl;
{
	statsp->xmit_cnt 	= cl->stats_.xmit_cnt;
	statsp->drop_cnt 	= cl->stats_.drop_cnt;
	statsp->over		= cl->stats_.over;
	statsp->borrows 	= cl->stats_.borrows;
	statsp->overactions 	= cl->stats_.overactions;
	statsp->delays 		= cl->stats_.delays;

	statsp->depth 		= cl->depth_;
	statsp->priority	= cl->pri_;
	statsp->maxidle		= cl->maxidle_;
	statsp->minidle		= cl->minidle_;
	statsp->offtime		= cl->offtime_;
	statsp->qmax		= qlimit(cl->q_);
	statsp->ns_per_byte	= cl->ns_per_byte_;
	statsp->wrr_allot	= cl->w_allotment_;
	statsp->qcnt		= qlen(cl->q_);
	statsp->avgidle		= cl->avgidle_;

	statsp->qtype		= qtype(cl->q_);
#ifdef ALTQ_RED
	if (q_is_red(cl->q_))
		red_getstats(cl->red_, &statsp->red[0]);
#endif
#ifdef ALTQ_RIO
	if (q_is_rio(cl->q_))
		rio_getstats((rio_t *)cl->red_, &statsp->red[0]);
#endif
}

static int
cbq_getstats(gsp)
	struct cbq_getstats *gsp;
{
	char		*ifacename;
	int		chandle, n, nclasses;
	cbq_state_t	*cbqp;
	struct rm_class	*cl;
	class_stats_t	stats, *usp;
	int error = 0;

	ifacename = gsp->iface.cbq_ifacename;
	nclasses = gsp->nclasses;
	usp = gsp->stats;

	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);
	if (nclasses <= 0)
		return (EINVAL);

	for (n = 0, chandle = 0; n < nclasses && chandle < CBQ_MAX_CLASSES;
	     n++) {
		switch(n) {
		case 0:
			cl = cbqp->ifnp.root_;
			stats.handle = ROOT_CLASS_HANDLE;
			break;
		case 1:
			cl = cbqp->ifnp.default_;
			stats.handle = DEFAULT_CLASS_HANDLE;
			break;
		case 2:
			cl = cbqp->ifnp.ctl_;
			stats.handle = CTL_CLASS_HANDLE;
			break;
		default:
			while ((cl = cbqp->cbq_class_tbl[chandle]) == NULL)
				if (++chandle >= CBQ_MAX_CLASSES)
					goto out;
			stats.handle = chandle++;
			break;
		}

		get_class_stats(&stats, cl);

		if ((error = copyout((caddr_t)&stats, (caddr_t)usp++,
				     sizeof(stats))) != 0)
			return (error);
	}

 out:
	gsp->nclasses = n;
	return (error);
}

static int
cbq_ifattach(ifacep)
	struct cbq_interface *ifacep;
{
	int		error = 0;
	char		*ifacename;
	cbq_state_t	*new_cbqp;
	struct ifnet 	*ifp;

	ifacename = ifacep->cbq_ifacename;
	if ((ifp = ifunit(ifacename)) == NULL)
		return (ENXIO);
	if (!ALTQ_IS_READY(&ifp->if_snd))
		return (ENXIO);

	/* allocate and initialize cbq_state_t */
	MALLOC(new_cbqp, cbq_state_t *, sizeof(cbq_state_t), M_DEVBUF, M_WAITOK);
	if (new_cbqp == NULL)
		return (ENOMEM);
	bzero(new_cbqp, sizeof(cbq_state_t));
 	CALLOUT_INIT(&new_cbqp->cbq_callout);
	MALLOC(new_cbqp->cbq_class_tbl, struct rm_class **,
	       sizeof(struct rm_class *) * CBQ_MAX_CLASSES, M_DEVBUF, M_WAITOK);
	if (new_cbqp->cbq_class_tbl == NULL) {
		FREE(new_cbqp, M_DEVBUF);
		return (ENOMEM);
	}
	bzero(new_cbqp->cbq_class_tbl, sizeof(struct rm_class *) * CBQ_MAX_CLASSES);
	new_cbqp->cbq_qlen = 0;
	new_cbqp->ifnp.ifq_ = &ifp->if_snd;	    /* keep the ifq */
       
	/*
	 * set CBQ to this ifnet structure.
	 */
	error = altq_attach(&ifp->if_snd, ALTQT_CBQ, new_cbqp,
			    cbq_enqueue, cbq_dequeue, cbq_request,
			    &new_cbqp->cbq_classifier, acc_classify);
	if (error) {
		FREE(new_cbqp->cbq_class_tbl, M_DEVBUF);
		FREE(new_cbqp, M_DEVBUF);
		return (error);
	}

	/* prepend to the list of cbq_state_t's. */
	new_cbqp->cbq_next = cbq_list;
	cbq_list = new_cbqp;

	return (0);
}

static int
cbq_ifdetach(ifacep)
	struct cbq_interface *ifacep;
{
	char		*ifacename;
	cbq_state_t 	*cbqp;

	ifacename = ifacep->cbq_ifacename;
	if ((cbqp = altq_lookup(ifacename, ALTQT_CBQ)) == NULL)
		return (EBADF);

	(void)cbq_set_enable(ifacep, DISABLE);

	cbq_clear_interface(cbqp);

	if (cbqp->ifnp.ctl_)
		cbq_class_destroy(cbqp, cbqp->ifnp.ctl_);
	if (cbqp->ifnp.default_)
		cbq_class_destroy(cbqp, cbqp->ifnp.default_);
	if (cbqp->ifnp.root_)
		cbq_class_destroy(cbqp, cbqp->ifnp.root_);

	/* remove CBQ from the ifnet structure. */
	(void)altq_detach(cbqp->ifnp.ifq_);

	/* remove from the list of cbq_state_t's. */
	if (cbq_list == cbqp)
		cbq_list = cbqp->cbq_next;
	else {
		cbq_state_t *cp;

		for (cp = cbq_list; cp != NULL; cp = cbqp->cbq_next)
			if (cp->cbq_next == cbqp) {
				cp->cbq_next = cbqp->cbq_next;
				break;
			}
		ASSERT(cp != NULL);
	}

	/* deallocate cbq_state_t */
	FREE(cbqp->cbq_class_tbl, M_DEVBUF);
	FREE(cbqp, M_DEVBUF);

	return (0);
}

/*
 * int
 * cbq_enqueue(struct ifaltq *ifq, struct mbuf *m, struct altq_pktattr *pattr)
 *		- Queue data packets.
 *
 *	cbq_enqueue is set to ifp->if_altqenqueue and called by an upper
 *	layer (e.g. ether_output).  cbq_enqueue queues the given packet
 *	to the cbq, then invokes the driver's start routine.
 *
 *	Assumptions:	called in splimp
 *	Returns:	0 if the queueing is successful.
 *			ENOBUFS if a packet dropping occured as a result of
 *			the queueing.
 */

static int
cbq_enqueue(ifq, m, pktattr)
	struct ifaltq *ifq;
	struct mbuf *m;
	struct altq_pktattr *pktattr;
{
	cbq_state_t *cbqp = (cbq_state_t *)ifq->altq_disc;
	struct rm_class *cl;
	int len;

	/* grab class set by classifier */
	if (pktattr == NULL || (cl = pktattr->pattr_class) == NULL)
		cl = cbqp->ifnp.default_;
	cl->pktattr_ = pktattr;  /* save proto hdr used by ECN */

	len = m_pktlen(m);
	if (rmc_queue_packet(cl, m) != 0) {
		/* drop occurred.  some mbuf was freed in rmc_queue_packet. */
		PKTCNTR_ADD(&cl->stats_.drop_cnt, len);
		return (ENOBUFS);
	}

	/* successfully queued. */
	++cbqp->cbq_qlen;
	IFQ_INC_LEN(ifq);
	return (0);
}

static struct mbuf *
cbq_dequeue(ifq, op)
	struct ifaltq *ifq;
	int op;
{
	cbq_state_t 	*cbqp = (cbq_state_t *)ifq->altq_disc;
	struct mbuf 	*m;

	m = rmc_dequeue_next(&cbqp->ifnp, op);

	if (m && op == ALTDQ_REMOVE) {
		--cbqp->cbq_qlen;  /* decrement # of packets in cbq */
		IFQ_DEC_LEN(ifq);

		/* Update the class. */
		rmc_update_class_util(&cbqp->ifnp);
	}
	return (m);
}

/*
 * void
 * cbqrestart(queue_t *) - Restart sending of data.
 * called from rmc_restart in splimp via timeout after waking up
 * a suspended class.
 *	Returns:	NONE
 */

static void
cbqrestart(ifq)
	struct ifaltq *ifq;
{
	cbq_state_t	*cbqp;
	struct ifnet	*ifp;

	if (!ALTQ_IS_ENABLED(ifq))
		/* cbq must have been detached */
		return;
	if ((cbqp = (cbq_state_t *)ifq->altq_disc) == NULL)
		/* should not happen */
		return;

	ifp = ifq->altq_ifp;
	if (ifp->if_start &&
	    cbqp->cbq_qlen > 0 && (ifp->if_flags & IFF_OACTIVE) == 0)
		(*ifp->if_start)(ifp);
}

static void cbq_purge(cbqp)
	cbq_state_t *cbqp;
{
	struct rm_class	*cl;
	int 		i;

	for (i = 0; i < CBQ_MAX_CLASSES; i++)
		if ((cl = cbqp->cbq_class_tbl[i]) != NULL)
			rmc_dropall(cl);
	if (ALTQ_IS_ENABLED(cbqp->ifnp.ifq_))
		cbqp->ifnp.ifq_->ifq_len = 0;
}

/*
 * cbq device interface
 */

altqdev_decl(cbq);

int
cbqopen(dev, flag, fmt, p)
	dev_t dev;
	int flag, fmt;
	struct proc *p;
{
	return (0);
}

int
cbqclose(dev, flag, fmt, p)
	dev_t dev;
	int flag, fmt;
	struct proc *p;
{
	struct ifnet *ifp;
	struct cbq_interface iface;
	int err, error = 0;

	while (cbq_list) {
		ifp = cbq_list->ifnp.ifq_->altq_ifp;
#if defined(__NetBSD__) || defined(__OpenBSD__)
		sprintf(iface.cbq_ifacename, "%s", ifp->if_xname);
#else
		sprintf(iface.cbq_ifacename,
			"%s%d", ifp->if_name, ifp->if_unit);
#endif
		err = cbq_ifdetach(&iface);
		if (err != 0 && error == 0)
			error = err;
	}

	return (error);
}

int
cbqioctl(dev, cmd, addr, flag, p)
	dev_t dev;
	ioctlcmd_t cmd;
	caddr_t addr;
	int flag;
	struct proc *p;
{
	int	error = 0;

	/* check cmd for superuser only */
	switch (cmd) {
	case CBQ_GETSTATS:
		/* currently only command that an ordinary user can call */
		break;
	default:
#if (__FreeBSD_version > 400000)
		error = suser(p);
#else
		error = suser(p->p_ucred, &p->p_acflag);
#endif
		if (error)
			return (error);
		break;
	}

	switch (cmd) {

	case CBQ_ENABLE:
		error = cbq_set_enable((struct cbq_interface *)addr, ENABLE);
		break;

	case CBQ_DISABLE:
		error = cbq_set_enable((struct cbq_interface *)addr, DISABLE);
		break;

	case CBQ_ADD_FILTER:
		error = cbq_add_filter((struct cbq_add_filter *)addr);
		break;

	case CBQ_DEL_FILTER:
		error = cbq_delete_filter((struct cbq_delete_filter *)addr);
		break;

	case CBQ_ADD_CLASS:
		error = cbq_add_class((struct cbq_add_class *)addr);
		break;

	case CBQ_DEL_CLASS:
		error = cbq_delete_class((struct cbq_delete_class *)addr);
		break;

	case CBQ_MODIFY_CLASS:
		error = cbq_modify_class((struct cbq_modify_class *)addr);
		break;

	case CBQ_CLEAR_HIERARCHY:
		error = cbq_clear_hierarchy((struct cbq_interface *)addr);
		break;

	case CBQ_IF_ATTACH:
		error = cbq_ifattach((struct cbq_interface *)addr);
		break;

	case CBQ_IF_DETACH:
		error = cbq_ifdetach((struct cbq_interface *)addr);
		break;

	case CBQ_GETSTATS:
		error = cbq_getstats((struct cbq_getstats *)addr);
		break;

	default:
		error = EINVAL;
		break;
	}

	return error;
}

#if 0
/* for debug */
static void cbq_class_dump(int);

static void cbq_class_dump(i)
	int i;
{
	struct rm_class *cl;
	rm_class_stats_t *s;
	struct _class_queue_ *q;

	if (cbq_list == NULL) {
		printf("cbq_class_dump: no cbq_state found\n");
		return;
	}
	cl = cbq_list->cbq_class_tbl[i];
    
	printf("class %d cl=%p\n", i, cl);
	if (cl != NULL) {
		s = &cl->stats_;
		q = cl->q_;

		printf("pri=%d, depth=%d, maxrate=%d, allotment=%d\n",
		       cl->pri_, cl->depth_, cl->maxrate_, cl->allotment_);
		printf("w_allotment=%d, bytes_alloc=%d, avgidle=%d, maxidle=%d\n",
		       cl->w_allotment_, cl->bytes_alloc_, cl->avgidle_,
		       cl->maxidle_);
		printf("minidle=%d, offtime=%d, sleeping=%d, leaf=%d\n",
		       cl->minidle_, cl->offtime_, cl->sleeping_, cl->leaf_);
		printf("handle=%d, depth=%d, packets=%d, bytes=%d\n",
		       s->handle, s->depth,
		       (int)s->xmit_cnt.packets, (int)s->xmit_cnt.bytes);
		printf("over=%d\n, borrows=%d, drops=%d, overactions=%d, delays=%d\n",
		       s->over, s->borrows, (int)s->drop_cnt.packets,
		       s->overactions, s->delays);
		printf("tail=%p, head=%p, qlen=%d, qlim=%d, qthresh=%d,qtype=%d\n",
		       q->tail_, q->head_, q->qlen_, q->qlim_,
		       q->qthresh_, q->qtype_);
	}
}
#endif /* 0 */

#ifdef KLD_MODULE

static struct altqsw cbq_sw =
	{"cbq", cbqopen, cbqclose, cbqioctl};

ALTQ_MODULE(altq_cbq, ALTQT_CBQ, &cbq_sw);

#endif /* KLD_MODULE */
