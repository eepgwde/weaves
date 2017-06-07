# weaves

## Regular expressions and string metrics for q/kdb

# These test programs check that the regular expression library is available.

ACLOCAL_AMFLAGS = -I $(top_builddir)/m4

CPPFLAGS = -I $(top_builddir)/lib

LDADD = $(LTLIBINTL) $(top_builddir)/lib/libgnu.la

BUILT_SOURCES = README

## Do this instead.
AM_TESTS_ENVIRONMENT = 
LOG_COMPILER = $(SHELL)
AM_LOG_FLAGS = -x
TESTS = egex.sh mygrep.sh regexpr.sh

noinst_PROGRAMS = egex mygrep regexpr
egex_SOURCES = egexm.c egex.1 xmalloc.c

mygrep_SOURCES = mygrep.c 
regexpr_SOURCES = regexpr.c


EXTRA_DIST = $(TESTS) README

#  build and install the .info pages
info_TEXINFOS = egex.texinfo

#  install the man pages
man_MANS=egex.1

clean-local:
	$(SHELL) -c "rm -f cscope.*"
	rm -f make.log
