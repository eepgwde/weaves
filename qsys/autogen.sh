#!/bin/bash

# weaves
# This script is an example of how to run configure and build
# it takes arguments on the command-line like this
#  autogen.sh smet=yes
# By default smet is no
#  autogen.sh smet=no nodo=echo
# Is a no-do method

# If you enable smet=enable then it will invoke the smet autogen.sh which performs a
# gnulib-tool import that is where I specify the modules to import.

# It expects SHELL to be a BASH shell.

for i in $*
do
    eval "$i"
done

if [ -n "$clean" -a "$clean" = "yes" ]
then
    set +e
    test -f Makefile && $nodo make distclean
    $nodo rm -rf m4 config lib
    $nodo find . -type d -name autom4te.cache -exec rm -rf {} \; 
    $nodo find . -type f \( -name Makefile.in -o -name aclocal.m4 -o -name configure -o -name '*~' \) -delete
    exit 0
fi

: ${QHOME:=$HOME/q}
test -d "$QHOME" || exit 1
: ${QOSTYPE:=l32}
test -d "$QHOME/$QOSTYPE" || exit 2

: ${QPROG:=$QHOME/$QOSTYPE/q}

: ${QTRDR_HOST:=$HOSTNAME}

# Make sure the string metrics have been set correctly.
# This smet/autogen.sh only configures the gnulib-tool component.
: ${smet:="disable"}
if [ -n "${smet}" -a "$smet" = "enable" ]
then
    (   cd smet;
	$nodo $SHELL -e autogen.sh $*
    )
else
 smet="disable"
fi

## Force 32 bit

: ${BITS:=$(echo $QOSTYPE | cut -c2-)}

: ${BUILD_HOST:=""}
: ${CFLAGS:=-DKXVER=3}
: ${CXXFLAGS:=""}
: ${LDFLAGS:=""}

if [ "$BITS" = "32" ]
then
  BUILD_HOST=-host=i686-linux-gnu
  CFLAGS="-m32 $CFLAGS"
  CXXFLAGS="-m32 $CXXFLAGS"
  LDFLAGS="-m32 $LDFLAGS"
fi

# Not needed at this level
# $nodo libtoolize --force

# autoreconf doesn't add missing files

test -d config || mkdir config

$nodo aclocal
$nodo automake --add-missing --copy
$nodo autoconf --force

# We can override the Q progdir because we only have Linux 32 bit
# We also override the Q homedir because of my home directory layout quirk

# This is a nested configure generate so it can take ages.

$nodo ./configure CFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS" CXXFLAGS="$CXXFLAGS" QHOME=$QHOME PATH=$PATH:$QHOME/${QOSTYPE} --prefix=$HOME $BUILD_HOST \
 --${smet}-string-metrics \
 --with-qprog=$(basename $QPROG) \
 --with-qprogdir=$(dirname $QPROG) \
 --with-qtrdrhost=$QTRDR_HOST \
 --with-qtrdrport=15001 \
 --disable-dependency-tracking
