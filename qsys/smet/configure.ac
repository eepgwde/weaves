dnl weaves
dnl 
dnl Regular expression and string metrics for q/kdb
dnl we only need a QPROG to locate the qprogdir

dnl This uses gnulib

AC_INIT([q], [0.1.0], [walter.eaves@bigfoot.com], [qsys])
AC_PREREQ(2.59)
AC_CONFIG_SRCDIR([test/egexm.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([foreign])

AC_COPYRIGHT([README])

dnl create a config.h file (Automake will add -DHAVE_CONFIG_H)
AM_CONFIG_HEADER(config.h)
AC_CONFIG_FILES(lib/Makefile)

AC_SUBST(VERSION)

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)

AC_CANONICAL_HOST
AC_USE_SYSTEM_EXTENSIONS

dnl Checks for programs.
AM_PROG_LIBTOOL
AC_PROG_CC
AC_PROG_INSTALL
gl_EARLY

gl_INIT
AC_LN_S

AC_ARG_WITH([qhomedir],
              AC_HELP_STRING([--with-qhomedir],
               [If enabled, set the QHOME variable to be as given. Otherwise, $libdir/q.]),
              [qhomedir=$withval],
              [qhomedir=$prefix/q])

if test "x$build_cpu" = "xi386"; then
 qcpu=32
elif test "x$build_cpu" = "xi686"; then
 qcpu=32
elif test "x$build_cpu" = "xsparc"; then
 qcpu=32
else
 qcpu=64
fi

echo $host_os | grep linux > /dev/null 2>&1 
if test $? -eq 0; then
   qdirsuffix=l$qcpu
fi

echo $host_os | grep darwin > /dev/null 2>&1 
if test $? -eq 0; then
   qdirsuffix=m$qcpu
fi

echo $host_os | grep solaris > /dev/null 2>&1 
if test $? -eq 0; then
   qdirsuffix=s$qcpu
fi

AC_ARG_WITH([qprogdir],
              AC_HELP_STRING([--with-qprogdir],
               [If enabled, set the QPROG variable to be as given. Otherwise, $qhomedir/$qdirsuffix]),
              [qprogdir=$withval],
              [qprogdir=$qhomedir/$qdirsuffix])

AC_ARG_WITH([qprog],
              AC_HELP_STRING([--with-qprog],
               [If enabled, set the name of the Q executable to be as given. Otherwise, "q"]),
              [qprog=$withval],
              [qprog=q])

dnl Hopefully, we will have the q we want to use on the original PATH
dnl or we will have constructed a PATH using the OS

AC_PATH_PROG([QPROG], [$qprog], [$qprogdir/$qprog], [path = $PATH:$progdir])

if test -n "$QPROG"; then
   qprog=`basename $QPROG`
   qprogdir=`dirname $QPROG`
   qhomedir=`dirname $qprogdir`
fi

AC_SUBST([qhomedir],[$qhomedir])
AC_SUBST([qprogdir],[$qprogdir])
AC_SUBST([qprog],[$qprog])

dnl Checks for libraries.

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(unistd.h sys/param.h sys/time.h time.h sys/mkdev.h sys/sysmacros.h string.h memory.h fcntl.h dirent.h sys/ndir.h ndir.h alloca.h locale.h regex.h )

dnl Quirky thing for Solaris. We use a GCC compiler, but we don't have
dnl the GNU regular expression library. So check if the POSIX one is there and
dnl use that.
AC_CHECK_MEMBERS([regmatch_t.rm_sp],[],[],[[#include <regex.h>]])

dnl Checks for typedefs, structures, and compiler characteristics.
dnl Checks for library functions.

jm_CHECK_TYPE_STRUCT_UTIMBUF
AC_HEADER_MAJOR
AC_FUNC_ALLOCA
AC_STRUCT_TM
AC_STRUCT_ST_BLOCKS
AC_FUNC_CLOSEDIR_VOID
AC_CHECK_FUNCS(mkfifo)
AC_CHECK_FUNC(mknod)


AC_OUTPUT([Makefile
test/Makefile
time0/Makefile
mcast/Makefile
regex/Makefile
examples/Makefile
egex.lsm egex.spec])
