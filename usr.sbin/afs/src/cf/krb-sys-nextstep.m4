dnl $KTH: krb-sys-nextstep.m4,v 1.2 1999/05/16 13:44:46 assar Exp $
dnl
dnl
dnl NEXTSTEP is not posix compliant by default,
dnl you need a switch -posix to the compiler
dnl

AC_DEFUN(AC_KRB_SYS_NEXTSTEP, [
AC_MSG_CHECKING(for NEXTSTEP)
AC_CACHE_VAL(krb_cv_sys_nextstep,
AC_EGREP_CPP(yes, 
[#if defined(NeXT) && !defined(__APPLE__)
	yes
#endif 
], krb_cv_sys_nextstep=yes, krb_cv_sys_nextstep=no) )
if test "$krb_cv_sys_nextstep" = "yes"; then
  CFLAGS="$CFLAGS -posix"
  CPPFLAGS="$CPPFLAGS -posix"
  LIBS="$LIBS -posix"
fi
AC_MSG_RESULT($krb_cv_sys_nextstep)
])
