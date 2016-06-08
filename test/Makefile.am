AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = oeTest

oeTest_SOURCES = OETest.cc


oeTest_CPPFLAGS = -I$(top_srcdir) $(GTEST_CPPFLAGS) 

oeTest_LDADD =  \
	../service/liboe.la \
	$(BOOST_LIBADD) \
	$(MYSQLPP_LIBADD) \
	$(TXOPTIX_LIBADD)


oeTest_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed  -pthread 

# header files
noinst_HEADERS = 

EXTRA_DIST = env.sh oe.cfg log.cfg

extradir = $(bindir)
extra_DATA = env.sh oe.cfg log.cfg

