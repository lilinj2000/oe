#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(oe, 1.0, lilinj2000@gmail.com)
AC_CONFIG_SRCDIR([])
#AC_CONFIG_HEADERS([config.h])


AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
LT_INIT
AC_PROG_RANLIB

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# libtool versioning
LT_RELEASE=1.0
LT_CURRENT=1
LT_REVISION=0
LT_AGE=0
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

dnl mysql++ api
MYSQLPP_CPPFLAGS="-I/usr/include/mysql++ -I/usr/include/mysql"
MYSQLPP_LIBADD="/usr/lib/libmysqlpp.so \
		/usr/lib/x86_64-linux-gnu/libmysqlclient_r.so"
AC_SUBST(MYSQLPP_CPPFLAGS)
AC_SUBST(MYSQLPP_LIBADD)

dnl TxOptix api
TXOPTIX_CPPFLAGS="-I$HOME/txsched/include -fpermissive"
TXOPTIX_LIBADD="$HOME/txsched/lib/libTxOptimizer.so \
		$HOME/txsched/lib/libHxLsGrgAdaptor.so \
		$HOME/txsched/lib/libHxNumerix.so \
		$HOME/txsched/lib/libHxLsGRG.so"

AC_SUBST(TXOPTIX_CPPFLAGS)
AC_SUBST(TXOPTIX_LIBADD)

dnl boost lib
BOOST_CPPFLAGS="-I$HOME/3rd/boost/include -DBOOST_ALL_DYN_LINK"
BOOST_LIBADD="$HOME/3rd/boost/lib/libboost_log.so \
              $HOME/3rd/boost/lib/libboost_log_setup.so \
	      $HOME/3rd/boost/lib/libboost_program_options.so \
	      $HOME/3rd/boost/lib/libboost_regex.so \
	      $HOME/3rd/boost/lib/libboost_filesystem.so \
	      $HOME/3rd/boost/lib/libboost_thread.so \
	      $HOME/3rd/boost/lib/libboost_system.so"
AC_SUBST(BOOST_CPPFLAGS)
AC_SUBST(BOOST_LIBADD)

dnl gtest lib
GTEST_CPPFLAGS=-I$HOME/3rd/gtest/include
GTEST_LIBADD="$HOME/3rd/gtest/lib/libgtest.a \
	      $HOME/3rd/gtest/lib/libgtest_main.a"
AC_SUBST(GTEST_CPPFLAGS)
AC_SUBST(GTEST_LIBADD)

dnl CXXFLAGS="$CXXFLAGS -Wl,--no-as-needed"

AC_OUTPUT([
	Makefile
	interface/Makefile
	service/Makefile
	etf/Makefile
	strategy/Makefile
	utest/Makefile
	test/Makefile
	example/Makefile])
