AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = liboe.la
liboe_la_CPPFLAGS = -I$(top_srcdir) $(BOOST_CPPFLAGS) $(TXOPTIX_CPPFLAGS)
liboe_la_SOURCES = ServiceImpl.cc Config.cc Log.cc
liboe_la_LIBADD = \
		../etf/libetf.la \
		../strategy/libstrategy.la  \
		$(BOOST_LIBADD)

liboe_la_LDFLAGS = \
	-no-undefined -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	-release $(LT_RELEASE) 

# header files
noinst_HEADERS = ServiceImpl.hh Config.hh


