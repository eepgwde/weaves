
q_files = darwin8.0.q linux-gnu.q help.q log.q site.q sys.q trdr.q dbmaint.q \
trdrc.q trader-cull.q commander.q \
fctry.q fctryc.q fctryc0.q fctrys.q csvguess.q memo0.q

bin_SCRIPTS = Qp Qr Qs qsys-config
sysconf_DATA = use-q q.rc
pkgdata_DATA = $(q_files)

CLEANFILES = $(bin_SCRIPTS) $(sysconf_DATA)

TESTS = test0.q

EXTRA_DIST = Qp.in Qr.in Qs.in use-q.in q.rc.in qsys-config $(q_files) $(TESTS)

do_subst = sed -e 's,[@]pkgdatadir[@],$(pkgdatadir),g' \
	       -e 's,[@]sysconfdir[@],$(sysconfdir),g' \
	       -e 's,[@]qhomedir[@],$(qhomedir),g' \
	       -e 's,[@]qprogdir[@],$(qprogdir),g' \
	       -e 's,[@]qtrdrhost[@],$(qtrdrhost),g' \
	       -e 's,[@]qtrdrport[@],$(qtrdrport),g' \
	       -e 's,[@]qprog[@],$(QPROG),g' \
               -e 's,[@]PERL[@],$(PERL),g' \
               -e 's,[@]PACKAGE[@],$(PACKAGE),g' \
               -e 's,[@]VERSION[@],$(VERSION),g'

TEST_EXTENSIONS = .q .sh
Q_LOG_COMPILER = tester
AM_PL_LOG_FLAGS = 
SH_LOG_COMPILER = $(SHELL)
AM_SH_LOG_FLAGS = 

LOG_COMPILER = ./tester
AM_LOG_FLAGS = -d

install-data-local:
	cd $(qhomedir); $(RM) q.q; $(LN_S) $(pkgdatadir)/site.q q.q

%: %.in
	$(do_subst) < $(srcdir)/$< > $@
	chmod +x $@
