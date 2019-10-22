#!/bin/bash

# weaves
# This script is called by the autogen.sh from above.
# it takes arguments on the command-line like this
#  autogen.sh smet=1
# It expects SHELL to be a BASH shell.

set -e

test -d lib

$nodo gnulib-tool --libtool --import \
 crc error getopt long-options memchr memcpy sleep stdint strerror strftime strndup

$nodo libtoolize --force

$nodo aclocal 
$nodo automake --add-missing --copy
$nodo autoreconf --force --install
