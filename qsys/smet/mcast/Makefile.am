AM_CFLAGS ?= -DNDEBUG
CPPFLAGS = -I${top_srcdir}/lib -I.. -DNO_PYTHON

ACLOCAL_AMFLAGS = -I m4

# The build of the test program doesn't work under Solaris.

# noinst_PROGRAMS = egext
# egext_SOURCES = egext.c
# egext_LDADD = c.o libqmcast.la -lpthread -lm

BUILT_SOURCES = c.o

c.o:
	$(RM) $@
	$(LN_S) ${qprogdir}/c.o 

pkglib_LTLIBRARIES = libqmcast.la
libqmcast_la_LIBADD = $(LTLIBINTL) ${top_srcdir}/lib/libgnu.la
libqmcast_la_SOURCES = mcast0.c mcast01.c version-etc-fsf.c

libqmcast_la_FLAGS = -no-undefined -module

noinst_PROGRAMS = mcast0t multicast multicast1

mcast0t_LDADD = c.o libqmcast.la $(libqmcast_la_LIBADD) 
mcast0t_LDFLAGS = -static -lpthread 

multicast_LDADD = c.o libqmcast.la $(libqmcast_la_LIBADD) 
multicast_LDFLAGS = -static -lpthread 

multicast1_LDADD = c.o libqmcast.la $(libqmcast_la_LIBADD) 
multicast1_LDFLAGS = -static -lpthread 

noinst_HEADERS = mcast0.h 

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list

TESTS = mcast0.sh mcast01.sh
TESTS_ENVIRONMENT = $(SHELL) -x 

q_files_TEST = mcast01t.q mcast02t.q
q_files = mcast0.q.in

EXTRA_DIST = README $(TESTS) $(q_files_TEST) $(q_files)

CLEANFILES = mcast0.q

dist_pkgdata_DATA = mcast0.q

do_subst = sed -e 's,[@]pkgdatadir[@],$(pkgdatadir),g' \
	       -e 's,[@]sysconfdir[@],$(sysconfdir),g' \
	       -e 's,[@]pkglibdir[@],$(pkglibdir),g' \
	       -e 's,[@]qhomedir[@],$(qhomedir),g' \
	       -e 's,[@]qprogdir[@],$(qprogdir),g' \
	       -e 's,[@]qprog[@],$(qprog),g' \
               -e 's,[@]PERL[@],$(PERL),g' \
               -e 's,[@]PACKAGE[@],$(PACKAGE),g' \
               -e 's,[@]VERSION[@],$(VERSION),g'

install-data-local:
	true

#	cd $(qhomedir); $(RM) q.q; $(LN_S) $(pkgdatadir)/site.q q.q

%: %.in
	$(do_subst) < $(srcdir)/$< > $@
	chmod +x $@
