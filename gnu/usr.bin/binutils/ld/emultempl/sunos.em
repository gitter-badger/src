# This shell script emits a C file. -*- C -*-
# It does some substitutions.
cat >e${EMULATION_NAME}.c <<EOF
/* This file is is generated by a shell script.  DO NOT EDIT! */

/* SunOS emulation code for ${EMULATION_NAME}
   Copyright 1991, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000
   Free Software Foundation, Inc.
   Written by Steve Chamberlain <sac@cygnus.com>
   SunOS shared library support by Ian Lance Taylor <ian@cygnus.com>

This file is part of GLD, the Gnu Linker.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#define TARGET_IS_${EMULATION_NAME}

#include <ctype.h>

#include "bfd.h"
#include "sysdep.h"
#include "bfdlink.h"
#include "libiberty.h"

#include "ld.h"
#include "ldmain.h"
#include "ldmisc.h"
#include "ldexp.h"
#include "ldlang.h"
#include "ldfile.h"
#include "ldemul.h"

#ifdef HAVE_DIRENT_H
# include <dirent.h>
#else
# define dirent direct
# ifdef HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif
# ifdef HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif
# ifdef HAVE_NDIR_H
#  include <ndir.h>
# endif
#endif

static void gld${EMULATION_NAME}_before_parse PARAMS ((void));
static void gld${EMULATION_NAME}_set_symbols PARAMS ((void));
static void gld${EMULATION_NAME}_create_output_section_statements
  PARAMS ((void));
static void gld${EMULATION_NAME}_find_so
  PARAMS ((lang_input_statement_type *));
static char *gld${EMULATION_NAME}_search_dir
  PARAMS ((const char *, const char *, boolean *));
static void gld${EMULATION_NAME}_after_open PARAMS ((void));
static void gld${EMULATION_NAME}_check_needed
  PARAMS ((lang_input_statement_type *));
static boolean gld${EMULATION_NAME}_search_needed
  PARAMS ((const char *, const char *));
static boolean gld${EMULATION_NAME}_try_needed
  PARAMS ((const char *, const char *));
static void gld${EMULATION_NAME}_before_allocation PARAMS ((void));
static void gld${EMULATION_NAME}_find_assignment
  PARAMS ((lang_statement_union_type *));
static void gld${EMULATION_NAME}_find_exp_assignment PARAMS ((etree_type *));
static void gld${EMULATION_NAME}_count_need
  PARAMS ((lang_input_statement_type *));
static void gld${EMULATION_NAME}_set_need
  PARAMS ((lang_input_statement_type *));
static char *gld${EMULATION_NAME}_get_script PARAMS ((int *isfile));

static void
gld${EMULATION_NAME}_before_parse()
{
  ldfile_output_architecture = bfd_arch_${ARCH};
  config.dynamic_link = true;
  config.has_shared = true;
}

/* This is called after the command line arguments have been parsed,
   but before the linker script has been read.  If this is a native
   linker, we add the directories in LD_LIBRARY_PATH to the search
   list.  */

static void
gld${EMULATION_NAME}_set_symbols ()
{
EOF
if [ "x${host}" = "x${target}" ] ; then
  case " ${EMULATION_LIBPATH} " in
  *" ${EMULATION_NAME} "*)
cat >>e${EMULATION_NAME}.c <<EOF
  const char *env;

  env = (const char *) getenv ("LD_LIBRARY_PATH");
  if (env != NULL)
    {
      char *l;

      l = xstrdup (env);
      while (1)
	{
	  char *c;

	  c = strchr (l, ':');
	  if (c != NULL)
	    *c++ = '\0';
	  if (*l != '\0')
	    ldfile_add_library_path (l, false);
	  if (c == NULL)
	    break;
	  l = c;
	}
    }
EOF
  ;;
  esac
fi
cat >>e${EMULATION_NAME}.c <<EOF
}

/* Despite the name, we use this routine to search for dynamic
   libraries.  On SunOS this requires a directory search.  We need to
   find the .so file with the highest version number.  The user may
   restrict the major version by saying, e.g., -lc.1.  Also, if we
   find a .so file, we need to look for a the same file after
   replacing .so with .sa; if it exists, it will be an archive which
   provide some initializations for data symbols, and we need to
   search it after including the .so file.  */

static void
gld${EMULATION_NAME}_create_output_section_statements ()
{
  lang_for_each_input_file (gld${EMULATION_NAME}_find_so);
}

/* Search the directory for a .so file for each library search.  */

static void
gld${EMULATION_NAME}_find_so (inp)
     lang_input_statement_type *inp;
{
  search_dirs_type *search;
  char *found = NULL;
  char *alc;
  struct stat st;

  if (! inp->search_dirs_flag
      || ! inp->is_archive
      || ! inp->dynamic)
    return;

  ASSERT (strncmp (inp->local_sym_name, "-l", 2) == 0);

  for (search = search_head; search != NULL; search = search->next)
    {
      boolean found_static;

      found = gld${EMULATION_NAME}_search_dir (search->name, inp->filename,
					       &found_static);
      if (found != NULL || found_static)
	break;
    }

  if (found == NULL)
    {
      /* We did not find a matching .so file.  This isn't an error,
	 since there might still be a matching .a file, which will be
	 found by the usual search.  */
      return;
    }

  /* Replace the filename with the one we have found.  */
  alc = (char *) xmalloc (strlen (search->name) + strlen (found) + 2);
  sprintf (alc, "%s/%s", search->name, found);
  inp->filename = alc;

  /* Turn off the search_dirs_flag to prevent ldfile_open_file from
     searching for this file again.  */
  inp->search_dirs_flag = false;

  free (found);

  /* Now look for the same file name, but with .sa instead of .so.  If
     found, add it to the list of input files.  */
  alc = (char *) xmalloc (strlen (inp->filename) + 1);
  strcpy (alc, inp->filename);
  strstr (alc + strlen (search->name), ".so")[2] = 'a';
  if (stat (alc, &st) != 0)
    free (alc);
  else
    {
      lang_input_statement_type *sa;

      /* Add the .sa file to the statement list just before the .so
	 file.  This is really a hack.  */
      sa = ((lang_input_statement_type *)
	    xmalloc (sizeof (lang_input_statement_type)));
      *sa = *inp;

      inp->filename = alc;
      inp->local_sym_name = alc;

      inp->header.next = (lang_statement_union_type *) sa;
      inp->next_real_file = (lang_statement_union_type *) sa;
    }
}

/* Search a directory for a .so file.  */

static char *
gld${EMULATION_NAME}_search_dir (dirname, filename, found_static)
     const char *dirname;
     const char *filename;
     boolean *found_static;
{
  int force_maj, force_min;
  const char *dot;
  unsigned int len;
  char *alc;
  char *found;
  int max_maj, max_min;
  DIR *dir;
  struct dirent *entry;
  unsigned int dirnamelen;
  char *full_path;
  int statval;
  struct stat st;

  *found_static = false;

  force_maj = -1;
  force_min = -1;
  dot = strchr (filename, '.');
  if (dot == NULL)
    {
      len = strlen (filename);
      alc = NULL;
    }
  else
    {
      force_maj = atoi (dot + 1);

      len = dot - filename;
      alc = (char *) xmalloc (len + 1);
      strncpy (alc, filename, len);
      alc[len] = '\0';
      filename = alc;

      dot = strchr (dot + 1, '.');
      if (dot != NULL)
	force_min = atoi (dot + 1);
    }

  found = NULL;
  max_maj = max_min = 0;

  dir = opendir (dirname);
  if (dir == NULL)
    return NULL;
  dirnamelen = strlen (dirname);
  
  while ((entry = readdir (dir)) != NULL)
    {
      const char *s;
      int found_maj, found_min;

      if (strncmp (entry->d_name, "lib", 3) != 0
	  || strncmp (entry->d_name + 3, filename, len) != 0)
	continue;

      if (dot == NULL
	  && strcmp (entry->d_name + 3 + len, ".a") == 0)
	{
	  *found_static = true;
	  continue;
	}

      /* We accept libfoo.so without a version number, even though the
         native linker does not.  This is more convenient for packages
         which just generate .so files for shared libraries, as on ELF
         systems.  */
      if (strncmp (entry->d_name + 3 + len, ".so", 3) != 0)
	continue;
      if (entry->d_name[6 + len] == '\0')
	;
      else if (entry->d_name[6 + len] == '.'
	       && isdigit ((unsigned char) entry->d_name[7 + len]))
	;
      else
	continue;

      for (s = entry->d_name + 6 + len; *s != '\0'; s++)
	if (*s != '.' && ! isdigit ((unsigned char) *s))
	  break;
      if (*s != '\0')
	continue;

      /* We've found a .so file.  Work out the major and minor
	 version numbers.  */
      found_maj = 0;
      found_min = 0;
      sscanf (entry->d_name + 3 + len, ".so.%d.%d",
	      &found_maj, &found_min);

      if ((force_maj != -1 && force_maj != found_maj)
	  || (force_min != -1 && force_min != found_min))
	continue;

      /* Make sure the file really exists (ignore broken symlinks).  */
      full_path = xmalloc (dirnamelen + 1 + strlen (entry->d_name) + 1);
      sprintf (full_path, "%s/%s", dirname, entry->d_name);
      statval = stat (full_path, &st);
      free (full_path);
      if (statval != 0)
	continue;

      /* We've found a match for the name we are searching for.  See
	 if this is the version we should use.  If the major and minor
	 versions match, we use the last entry in alphabetical order;
	 I don't know if this is how SunOS distinguishes libc.so.1.8
	 from libc.so.1.8.1, but it ought to suffice.  */
      if (found == NULL
	  || (found_maj > max_maj)
	  || (found_maj == max_maj
	      && (found_min > max_min
		  || (found_min == max_min
		      && strcmp (entry->d_name, found) > 0))))
	{
	  if (found != NULL)
	    free (found);
	  found = (char *) xmalloc (strlen (entry->d_name) + 1);
	  strcpy (found, entry->d_name);
	  max_maj = found_maj;
	  max_min = found_min;
	}
    }

  closedir (dir);

  if (alc != NULL)
    free (alc);

  return found;
}

/* These variables are required to pass information back and forth
   between after_open and check_needed.  */

static struct bfd_link_needed_list *global_needed;
static boolean global_found;

/* This is called after all the input files have been opened.  */

static void
gld${EMULATION_NAME}_after_open ()
{
  struct bfd_link_needed_list *needed, *l;

  /* We only need to worry about this when doing a final link.  */
  if (link_info.relocateable || link_info.shared)
    return;

  /* Get the list of files which appear in ld_need entries in dynamic
     objects included in the link.  For each such file, we want to
     track down the corresponding library, and include the symbol
     table in the link.  This is what the runtime dynamic linker will
     do.  Tracking the files down here permits one dynamic object to
     include another without requiring special action by the person
     doing the link.  Note that the needed list can actually grow
     while we are stepping through this loop.  */
  needed = bfd_sunos_get_needed_list (output_bfd, &link_info);
  for (l = needed; l != NULL; l = l->next)
    {
      struct bfd_link_needed_list *ll;
      const char *lname;
      search_dirs_type *search;

      lname = l->name;

      /* If we've already seen this file, skip it.  */
      for (ll = needed; ll != l; ll = ll->next)
	if (strcmp (ll->name, lname) == 0)
	  break;
      if (ll != l)
	continue;

      /* See if this file was included in the link explicitly.  */
      global_needed = l;
      global_found = false;
      lang_for_each_input_file (gld${EMULATION_NAME}_check_needed);
      if (global_found)
	continue;

      if (strncmp (lname, "-l", 2) != 0)
	{
	  bfd *abfd;

	  abfd = bfd_openr (lname, bfd_get_target (output_bfd));
	  if (abfd != NULL)
	    {
	      if (! bfd_check_format (abfd, bfd_object))
		{
		  (void) bfd_close (abfd);
		  abfd = NULL;
		}
	    }
	  if (abfd != NULL)
	    {
	      if ((bfd_get_file_flags (abfd) & DYNAMIC) == 0)
		{
		  (void) bfd_close (abfd);
		  abfd = NULL;
		}
	    }
	  if (abfd != NULL)
	    {
	      /* We've found the needed dynamic object.  */
	      if (! bfd_link_add_symbols (abfd, &link_info))
		einfo ("%F%B: could not read symbols: %E\n", abfd);
	    }
	  else
	    {
	      einfo ("%P: warning: %s, needed by %B, not found\n",
		     lname, l->by);
	    }

	  continue;
	}

      lname += 2;

      /* We want to search for the file in the same way that the
	 dynamic linker will search.  That means that we want to use
	 rpath_link, rpath or -L, then the environment variable
	 LD_LIBRARY_PATH (native only), then (if rpath was used) the
	 linker script LIB_SEARCH_DIRS.  */
      if (gld${EMULATION_NAME}_search_needed (command_line.rpath_link,
					      lname))
	continue;
      if (command_line.rpath != NULL)
	{
	  if (gld${EMULATION_NAME}_search_needed (command_line.rpath, lname))
	    continue;
	}
      else
	{
	  for (search = search_head; search != NULL; search = search->next)
	    if (gld${EMULATION_NAME}_try_needed (search->name, lname))
	      break;
	  if (search != NULL)
	    continue;
	}
EOF
if [ "x${host}" = "x${target}" ] ; then
  case " ${EMULATION_LIBPATH} " in
  *" ${EMULATION_NAME} "*)
cat >>e${EMULATION_NAME}.c <<EOF
      {
	const char *lib_path;

	lib_path = (const char *) getenv ("LD_LIBRARY_PATH");
	if (gld${EMULATION_NAME}_search_needed (lib_path, lname))
	  continue;
      }
EOF
  ;;
  esac
fi
cat >>e${EMULATION_NAME}.c <<EOF
      if (command_line.rpath != NULL)
	{
	  for (search = search_head; search != NULL; search = search->next)
	    {
	      if (search->cmdline)
		continue;
	      if (gld${EMULATION_NAME}_try_needed (search->name, lname))
		break;
	    }
	  if (search != NULL)
	    continue;
	}

      einfo ("%P: warning: %s, needed by %B, not found\n",
	     l->name, l->by);
    }
}

/* Search for a needed file in a path.  */

static boolean
gld${EMULATION_NAME}_search_needed (path, name)
     const char *path;
     const char *name;
{
  const char *s;

  if (path == NULL || *path == '\0')
    return false;
  while (1)
    {
      const char *dir;
      char *dircopy;

      s = strchr (path, ':');
      if (s == NULL)
	{
	  dircopy = NULL;
	  dir = path;
	}
      else
	{
	  dircopy = (char *) xmalloc (s - path + 1);
	  memcpy (dircopy, path, s - path);
	  dircopy[s - path] = '\0';
	  dir = dircopy;
	}

      if (gld${EMULATION_NAME}_try_needed (dir, name))
	return true;

      if (dircopy != NULL)
	free (dircopy);

      if (s == NULL)
	break;
      path = s + 1;
    }

  return false;	  
}

/* This function is called for each possible directory for a needed
   dynamic object.  */

static boolean
gld${EMULATION_NAME}_try_needed (dir, name)
     const char *dir;
     const char *name;
{
  char *file;
  char *alc;
  boolean ignore;
  bfd *abfd;

  file = gld${EMULATION_NAME}_search_dir (dir, name, &ignore);
  if (file == NULL)
    return false;

  alc = (char *) xmalloc (strlen (dir) + strlen (file) + 2);
  sprintf (alc, "%s/%s", dir, file);
  free (file);
  abfd = bfd_openr (alc, bfd_get_target (output_bfd));
  if (abfd == NULL)
    return false;
  if (! bfd_check_format (abfd, bfd_object))
    {
      (void) bfd_close (abfd);
      return false;
    }
  if ((bfd_get_file_flags (abfd) & DYNAMIC) == 0)
    {
      (void) bfd_close (abfd);
      return false;
    }

  /* We've found the needed dynamic object.  */

  /* Add this file into the symbol table.  */
  if (! bfd_link_add_symbols (abfd, &link_info))
    einfo ("%F%B: could not read symbols: %E\n", abfd);

  return true;
}

/* See if we have already included a needed object in the link.  This
   does not have to be precise, as it does no harm to include a
   dynamic object more than once.  */

static void
gld${EMULATION_NAME}_check_needed (s)
     lang_input_statement_type *s;
{
  if (s->filename == NULL)
    return;
  if (strncmp (global_needed->name, "-l", 2) != 0)
    {
      if (strcmp (s->filename, global_needed->name) == 0)
	global_found = true;
    }
  else
    {
      const char *sname, *lname;
      const char *sdot, *ldot;
      int lmaj, lmin, smaj, smin;

      lname = global_needed->name + 2;

      sname = strrchr (s->filename, '/');
      if (sname == NULL)
	sname = s->filename;
      else
	++sname;

      if (strncmp (sname, "lib", 3) != 0)
	return;
      sname += 3;

      ldot = strchr (lname, '.');
      if (ldot == NULL)
	ldot = lname + strlen (lname);

      sdot = strstr (sname, ".so.");
      if (sdot == NULL)
	return;

      if (sdot - sname != ldot - lname
	  || strncmp (lname, sname, sdot - sname) != 0)
	return;

      lmaj = lmin = -1;
      sscanf (ldot, ".%d.%d", &lmaj, &lmin);
      smaj = smin = -1;
      sscanf (sdot, ".so.%d.%d", &smaj, &smin);
      if ((smaj != lmaj && smaj != -1 && lmaj != -1)
	  || (smin != lmin && smin != -1 && lmin != -1))
	return;

      global_found = true;
    }
}

/* We need to use static variables to pass information around the call
   to lang_for_each_statement.  Ick.  */

static const char *find_assign;
static boolean found_assign;

/* We need to use static variables to pass information around the call
   to lang_for_each_input_file.  Ick.  */

static bfd_size_type need_size;
static bfd_size_type need_entries;
static bfd_byte *need_contents;
static bfd_byte *need_pinfo;
static bfd_byte *need_pnames;

/* The size of one entry in the .need section, not including the file
   name.  */

#define NEED_ENTRY_SIZE (16)

/* This is called after the sections have been attached to output
   sections, but before any sizes or addresses have been set.  */

static void
gld${EMULATION_NAME}_before_allocation ()
{
  struct bfd_link_hash_entry *hdyn = NULL;
  asection *sneed;
  asection *srules;
  asection *sdyn;

  /* The SunOS native linker creates a shared library whenever there
     are any undefined symbols in a link, unless -e is used.  This is
     pretty weird, but we are compatible.  */
  if (! link_info.shared && ! link_info.relocateable && ! entry_from_cmdline)
    {
      struct bfd_link_hash_entry *h;
      
      for (h = link_info.hash->undefs; h != NULL; h = h->next)
	{
	  if (h->type == bfd_link_hash_undefined
	      && h->u.undef.abfd != NULL
	      && (h->u.undef.abfd->flags & DYNAMIC) == 0
	      && strcmp (h->root.string, "__DYNAMIC") != 0
	      && strcmp (h->root.string, "__GLOBAL_OFFSET_TABLE_") != 0)
	    {
	      find_assign = h->root.string;
	      found_assign = false;
	      lang_for_each_statement (gld${EMULATION_NAME}_find_assignment);
	      if (! found_assign)
		{
		  link_info.shared = true;
		  break;
		}
	    }
	}
    }

  if (link_info.shared)
    {
      lang_output_section_statement_type *os;

      /* Set the .text section to start at 0x20, not 0x2020.  FIXME:
         This is too magical.  */
      os = lang_output_section_statement_lookup (".text");
      if (os->addr_tree == NULL)
	os->addr_tree = exp_intop (0x20);
    }

  /* We need to create a __DYNAMIC symbol.  We don't do this in the
     linker script because we want to set the value to the start of
     the dynamic section if there is one, or to zero if there isn't
     one.  We need to create the symbol before calling
     size_dynamic_sections, although we can't set the value until
     afterward.  */
  if (! link_info.relocateable)
    {
      hdyn = bfd_link_hash_lookup (link_info.hash, "__DYNAMIC", true, false,
				   false);
      if (hdyn == NULL)
	einfo ("%P%F: bfd_link_hash_lookup: %E\n");
      if (! bfd_sunos_record_link_assignment (output_bfd, &link_info,
					      "__DYNAMIC"))
	einfo ("%P%F: failed to record assignment to __DYNAMIC: %E\n");
    }

  /* If we are going to make any variable assignments, we need to let
     the backend linker know about them in case the variables are
     referred to by dynamic objects.  */
  lang_for_each_statement (gld${EMULATION_NAME}_find_assignment);

  /* Let the backend linker work out the sizes of any sections
     required by dynamic linking.  */
  if (! bfd_sunos_size_dynamic_sections (output_bfd, &link_info, &sdyn,
					 &sneed, &srules))
    einfo ("%P%F: failed to set dynamic section sizes: %E\n");

  if (sneed != NULL)
    {
      /* Set up the .need section.  See the description of the ld_need
	 field in include/aout/sun4.h.  */

      need_entries = 0;
      need_size = 0;

      lang_for_each_input_file (gld${EMULATION_NAME}_count_need);

      /* We should only have a .need section if we have at least one
	 dynamic object.  */
      ASSERT (need_entries != 0);

      sneed->_raw_size = need_size;
      sneed->contents = (bfd_byte *) xmalloc (need_size);

      need_contents = sneed->contents;
      need_pinfo = sneed->contents;
      need_pnames = sneed->contents + need_entries * 16;

      lang_for_each_input_file (gld${EMULATION_NAME}_set_need);

      ASSERT ((bfd_size_type) (need_pnames - sneed->contents) == need_size);
    }

  if (srules != NULL)
    {
      /* Set up the .rules section.  This is just a PATH like string
	 of the -L arguments given on the command line.  We permit the
	 user to specify the directories using the -rpath command line
	 option.  */
      if (command_line.rpath)
	{
	  srules->_raw_size = strlen (command_line.rpath);
	  srules->contents = (bfd_byte *) command_line.rpath;
	}
      else
	{
	  unsigned int size;
	  search_dirs_type *search;

	  size = 0;
	  for (search = search_head; search != NULL; search = search->next)
	    if (search->cmdline)
	      size += strlen (search->name) + 1;
	  srules->_raw_size = size;
	  if (size > 0)
	    {
	      char *p;

	      srules->contents = (bfd_byte *) xmalloc (size);
	      p = (char *) srules->contents;
	      *p = '\0';
	      for (search = search_head; search != NULL; search = search->next)
		{
		  if (search->cmdline)
		    {
		      if (p != (char *) srules->contents)
			*p++ = ':';
		      strcpy (p, search->name);
		      p += strlen (p);
		    }
		}
	    }
	}
    }

  /* We must assign a value to __DYNAMIC.  It should be zero if we are
     not doing a dynamic link, or the start of the .dynamic section if
     we are doing one.  */
  if (! link_info.relocateable)
    {
      hdyn->type = bfd_link_hash_defined;
      hdyn->u.def.value = 0;
      if (sdyn != NULL)
	hdyn->u.def.section = sdyn;
      else
	hdyn->u.def.section = bfd_abs_section_ptr;
    }
}

/* This is called by the before_allocation routine via
   lang_for_each_statement.  It does one of two things: if the
   variable find_assign is set, it sets found_assign if it finds an
   assignment to that variable; otherwise it tells the backend linker
   about all assignment statements, in case they are assignments to
   symbols which are referred to by dynamic objects.  */

static void
gld${EMULATION_NAME}_find_assignment (s)
     lang_statement_union_type *s;
{
  if (s->header.type == lang_assignment_statement_enum
      && (find_assign == NULL || ! found_assign))
    gld${EMULATION_NAME}_find_exp_assignment (s->assignment_statement.exp);
}

/* Look through an expression for an assignment statement.  */

static void
gld${EMULATION_NAME}_find_exp_assignment (exp)
     etree_type *exp;
{
  switch (exp->type.node_class)
    {
    case etree_assign:
      if (find_assign != NULL)
	{
	  if (strcmp (find_assign, exp->assign.dst) == 0)
	    found_assign = true;
	  return;
	}

      if (strcmp (exp->assign.dst, ".") != 0)
	{
	  if (! bfd_sunos_record_link_assignment (output_bfd, &link_info,
						  exp->assign.dst))
	    einfo ("%P%F: failed to record assignment to %s: %E\n",
		   exp->assign.dst);
	}
      gld${EMULATION_NAME}_find_exp_assignment (exp->assign.src);
      break;

    case etree_binary:
      gld${EMULATION_NAME}_find_exp_assignment (exp->binary.lhs);
      gld${EMULATION_NAME}_find_exp_assignment (exp->binary.rhs);
      break;

    case etree_trinary:
      gld${EMULATION_NAME}_find_exp_assignment (exp->trinary.cond);
      gld${EMULATION_NAME}_find_exp_assignment (exp->trinary.lhs);
      gld${EMULATION_NAME}_find_exp_assignment (exp->trinary.rhs);
      break;

    case etree_unary:
      gld${EMULATION_NAME}_find_exp_assignment (exp->unary.child);
      break;

    default:
      break;
    }
}

/* Work out the size of the .need section, and the number of entries.
   The backend will set the ld_need field of the dynamic linking
   information to point to the .need section.  See include/aout/sun4.h
   for more information.  */

static void
gld${EMULATION_NAME}_count_need (inp)
     lang_input_statement_type *inp;
{
  if (inp->the_bfd != NULL
      && (inp->the_bfd->flags & DYNAMIC) != 0)
    {
      ++need_entries;
      need_size += NEED_ENTRY_SIZE;
      if (! inp->is_archive)
	need_size += strlen (inp->filename) + 1;
      else
	{
	  ASSERT (inp->local_sym_name[0] == '-'
		  && inp->local_sym_name[1] == 'l');
	  need_size += strlen (inp->local_sym_name + 2) + 1;
	}
    }
}

/* Fill in the contents of the .need section.  */

static void
gld${EMULATION_NAME}_set_need (inp)
     lang_input_statement_type *inp;
{
  if (inp->the_bfd != NULL
      && (inp->the_bfd->flags & DYNAMIC) != 0)
    {
      bfd_size_type c;

      /* To really fill in the .need section contents, we need to know
	 the final file position of the section, but we don't.
	 Instead, we use offsets, and rely on the BFD backend to
	 finish the section up correctly.  FIXME: Talk about lack of
	 referential locality.  */
      bfd_put_32 (output_bfd, need_pnames - need_contents, need_pinfo);
      if (! inp->is_archive)
	{
	  bfd_put_32 (output_bfd, (bfd_vma) 0, need_pinfo + 4);
	  bfd_put_16 (output_bfd, (bfd_vma) 0, need_pinfo + 8);
	  bfd_put_16 (output_bfd, (bfd_vma) 0, need_pinfo + 10);
	  strcpy (need_pnames, inp->filename);
	}
      else
	{
	  char *verstr;
	  int maj, min;

	  bfd_put_32 (output_bfd, (bfd_vma) 0x80000000, need_pinfo + 4);
	  maj = 0;
	  min = 0;
	  verstr = strstr (inp->filename, ".so.");
	  if (verstr != NULL)
	    sscanf (verstr, ".so.%d.%d", &maj, &min);
	  bfd_put_16 (output_bfd, (bfd_vma) maj, need_pinfo + 8);
	  bfd_put_16 (output_bfd, (bfd_vma) min, need_pinfo + 10);
	  strcpy (need_pnames, inp->local_sym_name + 2);
	}

      c = (need_pinfo - need_contents) / NEED_ENTRY_SIZE;
      if (c + 1 >= need_entries)
	bfd_put_32 (output_bfd, (bfd_vma) 0, need_pinfo + 12);
      else
	bfd_put_32 (output_bfd, (bfd_vma) (c + 1) * NEED_ENTRY_SIZE,
		    need_pinfo + 12);

      need_pinfo += NEED_ENTRY_SIZE;
      need_pnames += strlen (need_pnames) + 1;
    }
}

static char *
gld${EMULATION_NAME}_get_script(isfile)
     int *isfile;
EOF

if test -n "$COMPILE_IN"
then
# Scripts compiled in.

# sed commands to quote an ld script as a C string.
sc="-f stringify.sed"

cat >>e${EMULATION_NAME}.c <<EOF
{			     
  *isfile = 0;

  if (link_info.relocateable == true && config.build_constructors == true)
    return
EOF
sed $sc ldscripts/${EMULATION_NAME}.xu                     >> e${EMULATION_NAME}.c
echo '  ; else if (link_info.relocateable == true) return' >> e${EMULATION_NAME}.c
sed $sc ldscripts/${EMULATION_NAME}.xr                     >> e${EMULATION_NAME}.c
echo '  ; else if (!config.text_read_only) return'         >> e${EMULATION_NAME}.c
sed $sc ldscripts/${EMULATION_NAME}.xbn                    >> e${EMULATION_NAME}.c
echo '  ; else if (!config.magic_demand_paged) return'     >> e${EMULATION_NAME}.c
sed $sc ldscripts/${EMULATION_NAME}.xn                     >> e${EMULATION_NAME}.c
echo '  ; else return'                                     >> e${EMULATION_NAME}.c
sed $sc ldscripts/${EMULATION_NAME}.x                      >> e${EMULATION_NAME}.c
echo '; }'                                                 >> e${EMULATION_NAME}.c

else
# Scripts read from the filesystem.

cat >>e${EMULATION_NAME}.c <<EOF
{			     
  *isfile = 1;

  if (link_info.relocateable == true && config.build_constructors == true)
    return "ldscripts/${EMULATION_NAME}.xu";
  else if (link_info.relocateable == true)
    return "ldscripts/${EMULATION_NAME}.xr";
  else if (!config.text_read_only)
    return "ldscripts/${EMULATION_NAME}.xbn";
  else if (!config.magic_demand_paged)
    return "ldscripts/${EMULATION_NAME}.xn";
  else
    return "ldscripts/${EMULATION_NAME}.x";
}
EOF

fi

cat >>e${EMULATION_NAME}.c <<EOF

struct ld_emulation_xfer_struct ld_${EMULATION_NAME}_emulation = 
{
  gld${EMULATION_NAME}_before_parse,
  syslib_default,
  hll_default,
  after_parse_default,
  gld${EMULATION_NAME}_after_open,
  after_allocation_default,
  set_output_arch_default,
  ldemul_default_target,
  gld${EMULATION_NAME}_before_allocation,
  gld${EMULATION_NAME}_get_script,
  "${EMULATION_NAME}",
  "${OUTPUT_FORMAT}",
  NULL,	/* finish */
  gld${EMULATION_NAME}_create_output_section_statements,
  NULL,	/* open dynamic archive */
  NULL,	/* place orphan */
  gld${EMULATION_NAME}_set_symbols,
  NULL,	/* parse args */
  NULL,	/* unrecognized file */
  NULL,	/* list options */
  NULL,	/* recognized file */
  NULL 	/* find_potential_libraries */
};
EOF
