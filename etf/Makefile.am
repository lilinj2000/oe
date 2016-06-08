AUTOMAKE_OPTIONS = foreign

noinst_LTLIBRARIES = libetf.la
libetf_la_CPPFLAGS = -I$(top_srcdir) $(MYSQLPP_CPPFLAGS)

libetf_la_SOURCES = ETFManager.cc \
		    ETFConnectionPool.cc \
		    NSCCImpl.cc \
		    CRImpl.cc \
		    ETFUtils.cc \
		    VolumeDailyImpl.cc \
		    VolatilityDailyImpl.cc


libetf_la_LIBADD = $(MYSQLPP_LIBADD)


# header files
noinst_HEADERS = ETFManager.hh \
		 ETFConnectionPool.hh \
		 NSCCInterface.hh \
		 NSCCImpl.hh \
		 CRInterface.hh \
		 CRImpl.hh \
		 ETFUtils.hh \
		 VolumeDailyInterface.hh \
		 VolumeDailyImpl.hh \
		 VolatilityDailyInterface.hh \
		 VolatilityDailyImpl.hh \
		 ETFDef.hh



