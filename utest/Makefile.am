AUTOMAKE_OPTIONS = foreign

noinst_PROGRAMS = unittest

unittest_SOURCES = ServiceTest.cc \
	ETFUtilsTest.cc \
	CRImplTest.cc \
	NSCCImplTest.cc \
	ETFManagerTest.cc \
	TxOptixPolicyTest.cc \
	UtilsTest.cc \
	ConfigTest.cc \
	LogTest.cc \
	VolumeDailyImplTest.cc \
	VolatilityDailyImplTest.cc


unittest_CPPFLAGS = -I$(top_srcdir) $(GTEST_CPPFLAGS) $(MYSQLPP_CPPFLAGS) $(TXOPTIX_CPPFLAGS) $(BOOST_CPPFLAGS) 

unittest_LDADD = $(GTEST_LIBADD) \
		../service/liboe.la \
		$(MYSQLPP_LIBADD) \
		$(BOOST_LIBADD) \
		$(TXOPTIX_LIBADD) 


unittest_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed  -pthread 

# header files
noinst_HEADERS = UtilsTest.hh

EXTRA_DIST = env.sh oe.cfg log.cfg
# dist-hook:
#         chmod u+w $(distdir)/env.sh $(distdir)/doc
#         echo "Distribution date: `date`" >> README
#         rm -f $(distdir)/doc/HACKING
