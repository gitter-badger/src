#!/bin/sh
#
# This file was produced by running the Configure script. It holds all the
# definitions figured out by Configure. Should you modify one of these values,
# do not forget to propagate your changes by running "Configure -der". You may
# instead choose to run each of the .SH files by yourself, or "Configure -S".
#

# Package name      : perl5
# Source directory  : .
# Configuration time: Fri Jul 19 01:55:41 EET DST 2002
# Configured by     : jhi
# Target system     : osf1 alpha.hut.fi v4.0 878 alpha 

Author=''
Date='$Date'
Header=''
Id='$Id'
Locker=''
Log='$Log'
Mcc='Mcc'
RCSfile='$RCSfile'
Revision='$Revision'
Source=''
State=''
_a='.a'
_exe=''
_o='.o'
afs='false'
afsroot='/afs'
alignbytes='8'
ansi2knr=''
aphostname=''
api_revision='5'
api_subversion='0'
api_version='8'
api_versionstring='5.8.0'
ar='ar'
archlib='/opt/perl/lib/5.8.0/alpha-dec_osf'
archlibexp='/opt/perl/lib/5.8.0/alpha-dec_osf'
archname64=''
archname='alpha-dec_osf'
archobjs=''
asctime_r_proto='0'
awk='awk'
baserev='5.0'
bash=''
bin='/opt/perl/bin'
binexp='/opt/perl/bin'
bison='bison'
byacc='byacc'
byteorder='12345678'
c='\c'
castflags='0'
cat='cat'
cc='cc'
cccdlflags=' '
ccdlflags='  -Wl,-rpath,/opt/perl/lib/5.8.0/alpha-dec_osf/CORE'
ccflags='-std -D_INTRINSICS -fprm d -ieee -DLANGUAGE_C'
ccflags_uselargefiles=''
ccname='cc'
ccsymbols='__alpha=1 __LANGUAGE_C__=1 __osf__=1 __unix__=1 _LONGLONG=1 _SYSTYPE_BSD=1 SYSTYPE_BSD=1 unix=1'
ccversion='V5.6-082'
cf_by='jhi'
cf_email='yourname@yourhost.yourplace.com'
cf_time='Fri Jul 19 01:55:41 EET DST 2002'
charsize='1'
chgrp=''
chmod='chmod'
chown=''
clocktype='clock_t'
comm='comm'
compress=''
contains='grep'
cp='cp'
cpio=''
cpp='cpp'
cpp_stuff='42'
cppccsymbols='LANGUAGE_C=1'
cppflags='-std -D_INTRINSICS -ieee -DLANGUAGE_C'
cpplast=''
cppminus=''
cpprun='/usr/local/bin/cpp'
cppstdin='cppstdin'
cppsymbols='_AES_SOURCE=1 __alpha=1 __ALPHA=1 _ANSI_C_SOURCE=1 _INTRINSICS=1 __LANGUAGE_C__=1 _LONGLONG=1 __osf__=1 _OSF_SOURCE=1 _POSIX_C_SOURCE=199506 _POSIX_SOURCE=1 __STDC__=1 _SYSTYPE_BSD=1 __unix__=1 _XOPEN_SOURCE=1'
crypt_r_proto='0'
cryptlib=''
csh='csh'
ctermid_r_proto='0'
ctime_r_proto='0'
d_Gconvert='sprintf((b),"%.*g",(n),(x))'
d_PRIEUldbl='define'
d_PRIFUldbl='define'
d_PRIGUldbl='define'
d_PRIXU64='define'
d_PRId64='define'
d_PRIeldbl='define'
d_PRIfldbl='define'
d_PRIgldbl='define'
d_PRIi64='define'
d_PRIo64='define'
d_PRIu64='define'
d_PRIx64='define'
d_SCNfldbl='define'
d__fwalk='undef'
d_access='define'
d_accessx='undef'
d_alarm='define'
d_archlib='define'
d_asctime_r='undef'
d_atolf='undef'
d_atoll='undef'
d_attribut='undef'
d_bcmp='define'
d_bcopy='define'
d_bsd='undef'
d_bsdgetpgrp='undef'
d_bsdsetpgrp='define'
d_bzero='define'
d_casti32='undef'
d_castneg='define'
d_charvspr='undef'
d_chown='define'
d_chroot='define'
d_chsize='undef'
d_class='undef'
d_closedir='define'
d_cmsghdr_s='define'
d_const='define'
d_crypt='define'
d_crypt_r='undef'
d_csh='define'
d_ctermid_r='undef'
d_ctime_r='undef'
d_cuserid='define'
d_dbl_dig='define'
d_dbminitproto='undef'
d_difftime='define'
d_dirfd='define'
d_dirnamlen='define'
d_dlerror='define'
d_dlopen='define'
d_dlsymun='undef'
d_dosuid='undef'
d_drand48_r='undef'
d_drand48proto='define'
d_dup2='define'
d_eaccess='undef'
d_endgrent='define'
d_endgrent_r='undef'
d_endhent='define'
d_endhostent_r='undef'
d_endnent='define'
d_endnetent_r='undef'
d_endpent='define'
d_endprotoent_r='undef'
d_endpwent='define'
d_endpwent_r='undef'
d_endsent='define'
d_endservent_r='undef'
d_eofnblk='define'
d_eunice='undef'
d_fchdir='define'
d_fchmod='define'
d_fchown='define'
d_fcntl='define'
d_fcntl_can_lock='define'
d_fd_macros='define'
d_fd_set='define'
d_fds_bits='define'
d_fgetpos='define'
d_finite='define'
d_finitel='define'
d_flexfnam='define'
d_flock='define'
d_flockproto='undef'
d_fork='define'
d_fp_class='define'
d_fpathconf='define'
d_fpclass='undef'
d_fpclassify='undef'
d_fpclassl='undef'
d_fpos64_t='undef'
d_frexpl='define'
d_fs_data_s='undef'
d_fseeko='undef'
d_fsetpos='define'
d_fstatfs='define'
d_fstatvfs='define'
d_fsync='define'
d_ftello='undef'
d_ftime='undef'
d_getcwd='define'
d_getespwnam='undef'
d_getfsstat='define'
d_getgrent='define'
d_getgrent_r='undef'
d_getgrgid_r='undef'
d_getgrnam_r='undef'
d_getgrps='define'
d_gethbyaddr='define'
d_gethbyname='define'
d_gethent='define'
d_gethname='define'
d_gethostbyaddr_r='undef'
d_gethostbyname_r='undef'
d_gethostent_r='undef'
d_gethostprotos='define'
d_getitimer='define'
d_getlogin='define'
d_getlogin_r='undef'
d_getmnt='undef'
d_getmntent='undef'
d_getnbyaddr='define'
d_getnbyname='define'
d_getnent='define'
d_getnetbyaddr_r='undef'
d_getnetbyname_r='undef'
d_getnetent_r='undef'
d_getnetprotos='define'
d_getpagsz='define'
d_getpbyname='define'
d_getpbynumber='define'
d_getpent='define'
d_getpgid='define'
d_getpgrp2='undef'
d_getpgrp='define'
d_getppid='define'
d_getprior='define'
d_getprotobyname_r='undef'
d_getprotobynumber_r='undef'
d_getprotoent_r='undef'
d_getprotoprotos='define'
d_getprpwnam='undef'
d_getpwent='define'
d_getpwent_r='undef'
d_getpwnam_r='undef'
d_getpwuid_r='undef'
d_getsbyname='define'
d_getsbyport='define'
d_getsent='define'
d_getservbyname_r='undef'
d_getservbyport_r='undef'
d_getservent_r='undef'
d_getservprotos='define'
d_getspnam='undef'
d_getspnam_r='undef'
d_gettimeod='define'
d_gmtime_r='undef'
d_gnulibc='undef'
d_grpasswd='define'
d_hasmntopt='undef'
d_htonl='define'
d_index='undef'
d_inetaton='define'
d_int64_t='undef'
d_isascii='define'
d_isfinite='undef'
d_isinf='undef'
d_isnan='define'
d_isnanl='define'
d_killpg='define'
d_lchown='define'
d_ldbl_dig='define'
d_link='define'
d_localtime_r='undef'
d_locconv='define'
d_lockf='define'
d_longdbl='define'
d_longlong='define'
d_lseekproto='define'
d_lstat='define'
d_madvise='define'
d_mblen='define'
d_mbstowcs='define'
d_mbtowc='define'
d_memchr='define'
d_memcmp='define'
d_memcpy='define'
d_memmove='define'
d_memset='define'
d_mkdir='define'
d_mkdtemp='undef'
d_mkfifo='define'
d_mkstemp='define'
d_mkstemps='undef'
d_mktime='define'
d_mmap='define'
d_modfl='undef'
d_modfl_pow32_bug='undef'
d_mprotect='define'
d_msg='define'
d_msg_ctrunc='define'
d_msg_dontroute='define'
d_msg_oob='define'
d_msg_peek='define'
d_msg_proxy='undef'
d_msgctl='define'
d_msgget='define'
d_msghdr_s='define'
d_msgrcv='define'
d_msgsnd='define'
d_msync='define'
d_munmap='define'
d_mymalloc='undef'
d_nice='define'
d_nl_langinfo='define'
d_nv_preserves_uv='undef'
d_off64_t='undef'
d_old_pthread_create_joinable='undef'
d_oldpthreads='undef'
d_oldsock='undef'
d_open3='define'
d_pathconf='define'
d_pause='define'
d_perl_otherlibdirs='undef'
d_phostname='undef'
d_pipe='define'
d_poll='define'
d_portable='define'
d_procselfexe='undef'
d_pthread_atfork='define'
d_pthread_yield='undef'
d_pwage='undef'
d_pwchange='undef'
d_pwclass='undef'
d_pwcomment='define'
d_pwexpire='undef'
d_pwgecos='define'
d_pwpasswd='define'
d_pwquota='define'
d_qgcvt='undef'
d_quad='define'
d_random_r='undef'
d_readdir64_r='undef'
d_readdir='define'
d_readdir_r='undef'
d_readlink='define'
d_readv='define'
d_recvmsg='define'
d_rename='define'
d_rewinddir='define'
d_rmdir='define'
d_safebcpy='undef'
d_safemcpy='undef'
d_sanemcmp='define'
d_sbrkproto='define'
d_sched_yield='define'
d_scm_rights='define'
d_seekdir='define'
d_select='define'
d_sem='define'
d_semctl='define'
d_semctl_semid_ds='define'
d_semctl_semun='define'
d_semget='define'
d_semop='define'
d_sendmsg='define'
d_setegid='define'
d_seteuid='define'
d_setgrent='define'
d_setgrent_r='undef'
d_setgrps='define'
d_sethent='define'
d_sethostent_r='undef'
d_setitimer='define'
d_setlinebuf='define'
d_setlocale='define'
d_setlocale_r='undef'
d_setnent='define'
d_setnetent_r='undef'
d_setpent='define'
d_setpgid='define'
d_setpgrp2='undef'
d_setpgrp='define'
d_setprior='define'
d_setproctitle='undef'
d_setprotoent_r='undef'
d_setpwent='define'
d_setpwent_r='undef'
d_setregid='define'
d_setresgid='undef'
d_setresuid='undef'
d_setreuid='define'
d_setrgid='define'
d_setruid='define'
d_setsent='define'
d_setservent_r='undef'
d_setsid='define'
d_setvbuf='define'
d_sfio='undef'
d_shm='define'
d_shmat='define'
d_shmatprototype='define'
d_shmctl='define'
d_shmdt='define'
d_shmget='define'
d_sigaction='define'
d_sigprocmask='define'
d_sigsetjmp='define'
d_sockatmark='undef'
d_sockatmarkproto='undef'
d_socket='define'
d_socklen_t='undef'
d_sockpair='define'
d_socks5_init='undef'
d_sqrtl='define'
d_srand48_r='undef'
d_srandom_r='undef'
d_sresgproto='undef'
d_sresuproto='undef'
d_statblks='define'
d_statfs_f_flags='define'
d_statfs_s='define'
d_statvfs='define'
d_stdio_cnt_lval='define'
d_stdio_ptr_lval='define'
d_stdio_ptr_lval_nochange_cnt='define'
d_stdio_ptr_lval_sets_cnt='undef'
d_stdio_stream_array='define'
d_stdiobase='define'
d_stdstdio='define'
d_strchr='define'
d_strcoll='define'
d_strctcpy='define'
d_strerrm='strerror(e)'
d_strerror='define'
d_strerror_r='undef'
d_strftime='define'
d_strtod='define'
d_strtol='define'
d_strtold='undef'
d_strtoll='undef'
d_strtoq='undef'
d_strtoul='define'
d_strtoull='undef'
d_strtouq='undef'
d_strxfrm='define'
d_suidsafe='undef'
d_symlink='define'
d_syscall='define'
d_syscallproto='undef'
d_sysconf='define'
d_sysernlst=''
d_syserrlst='define'
d_system='define'
d_tcgetpgrp='define'
d_tcsetpgrp='define'
d_telldir='define'
d_telldirproto='define'
d_time='define'
d_times='define'
d_tm_tm_gmtoff='define'
d_tm_tm_zone='define'
d_tmpnam_r='undef'
d_truncate='define'
d_ttyname_r='undef'
d_tzname='define'
d_u32align='define'
d_ualarm='define'
d_umask='define'
d_uname='define'
d_union_semun='undef'
d_unordered='define'
d_usleep='define'
d_usleepproto='undef'
d_ustat='define'
d_vendorarch='undef'
d_vendorbin='undef'
d_vendorlib='undef'
d_vfork='undef'
d_void_closedir='undef'
d_voidsig='define'
d_voidtty=''
d_volatile='define'
d_vprintf='define'
d_wait4='define'
d_waitpid='define'
d_wcstombs='define'
d_wctomb='define'
d_writev='define'
d_xenix='undef'
date='date'
db_hashtype='u_int32_t'
db_prefixtype='size_t'
db_version_major='1'
db_version_minor='0'
db_version_patch='0'
defvoidused='15'
direntrytype='struct dirent'
dlext='so'
dlsrc='dl_dlopen.xs'
doublesize='8'
drand01='drand48()'
drand48_r_proto='0'
dynamic_ext='B ByteLoader Cwd DB_File Data/Dumper Devel/DProf Devel/PPPort Devel/Peek Digest/MD5 Encode Fcntl File/Glob Filter/Util/Call I18N/Langinfo IO IPC/SysV List/Util MIME/Base64 NDBM_File ODBM_File Opcode POSIX PerlIO/encoding PerlIO/scalar PerlIO/via SDBM_File Socket Storable Sys/Hostname Sys/Syslog Time/HiRes Unicode/Normalize XS/APItest XS/Typemap attrs re threads threads/shared'
eagain='EAGAIN'
ebcdic='undef'
echo='echo'
egrep='egrep'
emacs=''
endgrent_r_proto='0'
endhostent_r_proto='0'
endnetent_r_proto='0'
endprotoent_r_proto='0'
endpwent_r_proto='0'
endservent_r_proto='0'
eunicefix=':'
exe_ext=''
expr='expr'
extensions='B ByteLoader Cwd DB_File Data/Dumper Devel/DProf Devel/PPPort Devel/Peek Digest/MD5 Encode Fcntl File/Glob Filter/Util/Call I18N/Langinfo IO IPC/SysV List/Util MIME/Base64 NDBM_File ODBM_File Opcode POSIX PerlIO/encoding PerlIO/scalar PerlIO/via SDBM_File Socket Storable Sys/Hostname Sys/Syslog Time/HiRes Unicode/Normalize XS/APItest XS/Typemap attrs re threads threads/shared Errno'
extras=''
fflushNULL='define'
fflushall='undef'
find=''
firstmakefile='makefile'
flex=''
fpossize='8'
fpostype='fpos_t'
freetype='void'
from=':'
full_ar='/usr/bin/ar'
full_csh='/usr/bin/csh'
full_sed='/usr/local/bin/sed'
gccosandvers=''
gccversion=''
getgrent_r_proto='0'
getgrgid_r_proto='0'
getgrnam_r_proto='0'
gethostbyaddr_r_proto='0'
gethostbyname_r_proto='0'
gethostent_r_proto='0'
getlogin_r_proto='0'
getnetbyaddr_r_proto='0'
getnetbyname_r_proto='0'
getnetent_r_proto='0'
getprotobyname_r_proto='0'
getprotobynumber_r_proto='0'
getprotoent_r_proto='0'
getpwent_r_proto='0'
getpwnam_r_proto='0'
getpwuid_r_proto='0'
getservbyname_r_proto='0'
getservbyport_r_proto='0'
getservent_r_proto='0'
getspnam_r_proto='0'
gidformat='"u"'
gidsign='1'
gidsize='4'
gidtype='gid_t'
glibpth='/usr/shlib /usr/ccs/lib /usr/lib/cmplrs/cc /usr/lib /usr/local/lib /var/shlib'
gmake='gmake'
gmtime_r_proto='0'
gnulibc_version=''
grep='grep'
groupcat='cat /etc/group'
groupstype='gid_t'
gzip='gzip'
h_fcntl='false'
h_sysfile='true'
hint='recommended'
hostcat='cat /etc/hosts'
i16size='2'
i16type='short'
i32size='4'
i32type='int'
i64size='8'
i64type='long'
i8size='1'
i8type='char'
i_arpainet='define'
i_bsdioctl=''
i_crypt='define'
i_db='define'
i_dbm='define'
i_dirent='define'
i_dld='undef'
i_dlfcn='define'
i_fcntl='undef'
i_float='define'
i_fp='define'
i_fp_class='define'
i_gdbm='undef'
i_grp='define'
i_ieeefp='undef'
i_inttypes='undef'
i_langinfo='define'
i_libutil='undef'
i_limits='define'
i_locale='define'
i_machcthr='undef'
i_malloc='define'
i_math='define'
i_memory='undef'
i_mntent='undef'
i_ndbm='define'
i_netdb='define'
i_neterrno='undef'
i_netinettcp='define'
i_niin='define'
i_poll='define'
i_prot='define'
i_pthread='define'
i_pwd='define'
i_rpcsvcdbm='undef'
i_sfio='undef'
i_sgtty='undef'
i_shadow='undef'
i_socks='undef'
i_stdarg='define'
i_stddef='define'
i_stdlib='define'
i_string='define'
i_sunmath='undef'
i_sysaccess='define'
i_sysdir='define'
i_sysfile='define'
i_sysfilio='undef'
i_sysin='undef'
i_sysioctl='define'
i_syslog='define'
i_sysmman='define'
i_sysmode='define'
i_sysmount='define'
i_sysndir='undef'
i_sysparam='define'
i_sysresrc='define'
i_syssecrt='define'
i_sysselct='define'
i_syssockio='undef'
i_sysstat='define'
i_sysstatfs='undef'
i_sysstatvfs='define'
i_systime='define'
i_systimek='undef'
i_systimes='define'
i_systypes='define'
i_sysuio='define'
i_sysun='define'
i_sysutsname='define'
i_sysvfs='undef'
i_syswait='define'
i_termio='undef'
i_termios='define'
i_time='undef'
i_unistd='define'
i_ustat='define'
i_utime='define'
i_values='define'
i_varargs='undef'
i_varhdr='stdarg.h'
i_vfork='undef'
ignore_versioned_solibs=''
inc_version_list=' '
inc_version_list_init='0'
incpath=''
inews=''
installarchlib='/opt/perl/lib/5.8.0/alpha-dec_osf'
installbin='/opt/perl/bin'
installman1dir='/opt/perl/man/man1'
installman3dir='/opt/perl/man/man3'
installprefix='/opt/perl'
installprefixexp='/opt/perl'
installprivlib='/opt/perl/lib/5.8.0'
installscript='/opt/perl/bin'
installsitearch='/opt/perl/lib/site_perl/5.8.0/alpha-dec_osf'
installsitebin='/opt/perl/bin'
installsitelib='/opt/perl/lib/site_perl/5.8.0'
installstyle='lib'
installusrbinperl='define'
installvendorarch=''
installvendorbin=''
installvendorlib=''
intsize='4'
issymlink='test -h'
ivdformat='"ld"'
ivsize='8'
ivtype='long'
known_extensions='B ByteLoader Cwd DB_File Data/Dumper Devel/DProf Devel/PPPort Devel/Peek Digest/MD5 Encode Fcntl File/Glob Filter/Util/Call GDBM_File I18N/Langinfo IO IPC/SysV List/Util MIME/Base64 NDBM_File ODBM_File Opcode POSIX PerlIO/encoding PerlIO/scalar PerlIO/via SDBM_File Socket Storable Sys/Hostname Sys/Syslog Thread Time/HiRes Unicode/Normalize XS/APItest XS/Typemap attrs re threads threads/shared'
ksh=''
ld='ld'
lddlflags='-shared -expect_unresolved "*" -msym -std -s'
ldflags=''
ldflags_uselargefiles=''
ldlibpthname='LD_LIBRARY_PATH'
less='less'
lib_ext='.a'
libc='/usr/shlib/libc.so'
libperl='libperl.so'
libpth='/usr/shlib /usr/ccs/lib /usr/lib/cmplrs/cc /usr/lib /var/shlib'
libs='-ldbm -ldb -lm -lutil'
libsdirs=' /usr/ccs/lib /usr/shlib'
libsfiles=' libdbm.a libdb.so libm.so libutil.a'
libsfound=' /usr/ccs/lib/libdbm.a /usr/shlib/libdb.so /usr/shlib/libm.so /usr/ccs/lib/libutil.a'
libspath=' /usr/shlib /usr/ccs/lib /usr/lib/cmplrs/cc /usr/lib /var/shlib'
libswanted='sfio socket bind inet nsl nm gdbm dbm db malloc dld ld sun m cposix posix ndir dir crypt sec ucb BSD x util'
libswanted_uselargefiles=''
line=''
lint=''
lkflags=''
ln='ln'
lns='/usr/bin/ln -s'
localtime_r_proto='0'
locincpth='/usr/local/include /opt/local/include /usr/gnu/include /opt/gnu/include /usr/GNU/include /opt/GNU/include'
loclibpth='/usr/local/lib /opt/local/lib /usr/gnu/lib /opt/gnu/lib /usr/GNU/lib /opt/GNU/lib'
longdblsize='8'
longlongsize='8'
longsize='8'
lp=''
lpr=''
ls='ls'
lseeksize='8'
lseektype='off_t'
mail=''
mailx=''
make='make'
make_set_make='#'
mallocobj=''
mallocsrc=''
malloctype='void *'
man1dir='/opt/perl/man/man1'
man1direxp='/opt/perl/man/man1'
man1ext='1'
man3dir='/opt/perl/man/man3'
man3direxp='/opt/perl/man/man3'
man3ext='3'
mips_type=''
mkdir='mkdir'
mmaptype='void *'
modetype='mode_t'
more='more'
multiarch='undef'
mv=''
myarchname='alpha-dec_osf'
mydomain='.yourplace.com'
myhostname='yourhost'
myuname='osf1 alpha.hut.fi v4.0 878 alpha '
n=''
need_va_copy='undef'
netdb_hlen_type='int'
netdb_host_type='const char *'
netdb_name_type='const char *'
netdb_net_type='int'
nm='nm'
nm_opt='-p'
nm_so_opt=''
nonxs_ext='Errno'
nroff='nroff'
nvEUformat='"E"'
nvFUformat='"F"'
nvGUformat='"G"'
nv_preserves_uv_bits='53'
nveformat='"e"'
nvfformat='"f"'
nvgformat='"g"'
nvsize='8'
nvtype='double'
o_nonblock='O_NONBLOCK'
obj_ext='.o'
old_pthread_create_joinable=''
optimize='-O4'
orderlib='false'
osname='dec_osf'
osvers='4.0d'
otherlibdirs=' '
package='perl5'
pager='/usr/local/bin/less'
passcat='cat /etc/passwd'
patchlevel='8'
path_sep=':'
perl5='perl'
perl=''
perl_patchlevel='17634'
perladmin='yourname@yourhost.yourplace.com'
perllibs='-lm -lutil'
perlpath='/opt/perl/bin/perl'
pg='pg'
phostname=''
pidtype='pid_t'
plibpth=''
pm_apiversion='5.005'
pmake=''
pr=''
prefix='/opt/perl'
prefixexp='/opt/perl'
privlib='/opt/perl/lib/5.8.0'
privlibexp='/opt/perl/lib/5.8.0'
procselfexe=''
prototype='define'
ptrsize='8'
quadkind='2'
quadtype='long'
randbits='48'
randfunc='drand48'
random_r_proto='0'
randseedtype='long'
ranlib=':'
rd_nodata='-1'
readdir64_r_proto='0'
readdir_r_proto='0'
revision='5'
rm='rm'
rmail=''
run=''
runnm='true'
sPRIEUldbl='"E"'
sPRIFUldbl='"F"'
sPRIGUldbl='"G"'
sPRIXU64='"lX"'
sPRId64='"ld"'
sPRIeldbl='"e"'
sPRIfldbl='"f"'
sPRIgldbl='"g"'
sPRIi64='"li"'
sPRIo64='"lo"'
sPRIu64='"lu"'
sPRIx64='"lx"'
sSCNfldbl='"f"'
sched_yield='sched_yield()'
scriptdir='/opt/perl/bin'
scriptdirexp='/opt/perl/bin'
sed='sed'
seedfunc='srand48'
selectminbits='32'
selecttype='fd_set *'
sendmail=''
setgrent_r_proto='0'
sethostent_r_proto='0'
setlocale_r_proto='0'
setnetent_r_proto='0'
setprotoent_r_proto='0'
setpwent_r_proto='0'
setservent_r_proto='0'
sh='/bin/sh'
shar=''
sharpbang='#!'
shmattype='void *'
shortsize='2'
shrpenv=''
shsharp='true'
sig_count='49'
sig_name='ZERO HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV SYS PIPE ALRM TERM IOINT STOP TSTP CONT CHLD TTIN TTOU AIO XCPU XFSZ VTALRM PROF WINCH INFO USR1 USR2 RESV RTMIN NUM34 NUM35 NUM36 NUM37 NUM38 NUM39 NUM40 NUM41 NUM42 NUM43 NUM44 NUM45 NUM46 NUM47 MAX IOT LOST URG CLD IO POLL PTY PWR RTMAX '
sig_name_init='"ZERO", "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "EMT", "FPE", "KILL", "BUS", "SEGV", "SYS", "PIPE", "ALRM", "TERM", "IOINT", "STOP", "TSTP", "CONT", "CHLD", "TTIN", "TTOU", "AIO", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH", "INFO", "USR1", "USR2", "RESV", "RTMIN", "NUM34", "NUM35", "NUM36", "NUM37", "NUM38", "NUM39", "NUM40", "NUM41", "NUM42", "NUM43", "NUM44", "NUM45", "NUM46", "NUM47", "MAX", "IOT", "LOST", "URG", "CLD", "IO", "POLL", "PTY", "PWR", "RTMAX", 0'
sig_num='0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 6 6 16 20 23 23 23 29 48 '
sig_num_init='0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 6, 6, 16, 20, 23, 23, 23, 29, 48, 0'
sig_size='58'
signal_t='void'
sitearch='/opt/perl/lib/site_perl/5.8.0/alpha-dec_osf'
sitearchexp='/opt/perl/lib/site_perl/5.8.0/alpha-dec_osf'
sitebin='/opt/perl/bin'
sitebinexp='/opt/perl/bin'
sitelib='/opt/perl/lib/site_perl/5.8.0'
sitelib_stem='/opt/perl/lib/site_perl'
sitelibexp='/opt/perl/lib/site_perl/5.8.0'
siteprefix='/opt/perl'
siteprefixexp='/opt/perl'
sizesize='8'
sizetype='size_t'
sleep=''
smail=''
so='so'
sockethdr=''
socketlib=''
socksizetype='int'
sort='sort'
spackage='Perl5'
spitshell='cat'
srand48_r_proto='0'
srandom_r_proto='0'
src='.'
ssizetype='ssize_t'
startperl='#!/opt/perl/bin/perl'
startsh='#!/bin/sh'
static_ext=' '
stdchar='unsigned char'
stdio_base='((fp)->_base)'
stdio_bufsiz='((fp)->_cnt + (fp)->_ptr - (fp)->_base)'
stdio_cnt='((fp)->_cnt)'
stdio_filbuf=''
stdio_ptr='((fp)->_ptr)'
stdio_stream_array='_iob'
strerror_r_proto='0'
strings='/usr/include/string.h'
submit=''
subversion='0'
sysman='/usr/share/man/man1'
tail=''
tar=''
targetarch=''
tbl=''
tee=''
test='test'
timeincl='/usr/include/sys/time.h '
timetype='time_t'
tmpnam_r_proto='0'
to=':'
touch='touch'
tr='tr'
trnl='\n'
troff=''
ttyname_r_proto='0'
u16size='2'
u16type='unsigned short'
u32size='4'
u32type='unsigned int'
u64size='8'
u64type='unsigned long'
u8size='1'
u8type='unsigned char'
uidformat='"u"'
uidsign='1'
uidsize='4'
uidtype='uid_t'
uname='uname'
uniq='uniq'
uquadtype='unsigned long'
use5005threads='undef'
use64bitall='define'
use64bitint='define'
usecrosscompile='undef'
usedl='define'
useithreads='undef'
uselargefiles='define'
uselongdouble='undef'
usemorebits='undef'
usemultiplicity='undef'
usemymalloc='n'
usenm='true'
useopcode='true'
useperlio='define'
useposix='true'
usereentrant='undef'
usesfio='false'
useshrplib='true'
usesocks='undef'
usethreads='undef'
usevendorprefix='undef'
usevfork='false'
usrinc='/usr/include'
uuname=''
uvXUformat='"lX"'
uvoformat='"lo"'
uvsize='8'
uvtype='unsigned long'
uvuformat='"lu"'
uvxformat='"lx"'
vendorarch=''
vendorarchexp=''
vendorbin=''
vendorbinexp=''
vendorlib=''
vendorlib_stem=''
vendorlibexp=''
vendorprefix=''
vendorprefixexp=''
version='5.8.0'
version_patchlevel_string='version 8 subversion 0 patch 17634'
versiononly='undef'
vi=''
voidflags='15'
xlibpth='/usr/lib/386 /lib/386'
xs_apiversion='5.8.0'
perl5='yacc'
yaccflags=''
zcat=''
zip='zip'
# Configure command line arguments.
config_arg0='./Configure'
config_args='-Dprefix=/opt/perl -Duse64bitint -Duselargefiles -Dcf_by=yourname -Dcf_email=yourname@yourhost.yourplace.com -Dperladmin=yourname@yourhost.yourplace.com -Dmydomain=.yourplace.com -Dmyhostname=yourhost -dE'
config_argc=9
config_arg1='-Dprefix=/opt/perl'
config_arg2='-Duse64bitint'
config_arg3='-Duselargefiles'
config_arg4='-Dcf_by=yourname'
config_arg5='-Dcf_email=yourname@yourhost.yourplace.com'
config_arg6='-Dperladmin=yourname@yourhost.yourplace.com'
config_arg7='-Dmydomain=.yourplace.com'
config_arg8='-Dmyhostname=yourhost'
config_arg9='-dE'
PERL_REVISION=5
PERL_VERSION=8
PERL_SUBVERSION=0
PERL_API_REVISION=5
PERL_API_VERSION=8
PERL_API_SUBVERSION=0
PERL_PATCHLEVEL=17634
PERL_CONFIG_SH=true
# Variables propagated from previous config.sh file.
pp_sys_cflags='ccflags="$ccflags -DNO_EFF_ONLY_OK"'
