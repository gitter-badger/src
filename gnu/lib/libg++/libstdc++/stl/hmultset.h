/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef HMULTISET_H
#define HMULTISET_H

#ifdef MULTISET_H
#undef MULTISET_H
#undef TREE_H
#define __MULTISET_WAS_DEFINED
#endif

#define Allocator huge_allocator
#define multiset huge_multiset
#define rb_tree huge_rb_tree
#include <hugalloc.h>
#include <multiset.h>

#undef MULTISET_H
#undef TREE_H

#ifdef __MULTISET_WAS_DEFINED
#define MULTISET_H
#define TREE_H
#undef  __MULTISET_WAS_DEFINED
#endif

#undef Allocator
#undef multiset
#undef rb_tree

#endif
