#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ommikomm], [2.0], [michael@neuendorf-online.de])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([src/config.h])

AM_GNU_GETTEXT([external])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CXX
AC_PROG_LN_S

AC_PATH_PROG(CXXTEST, cxxtestgen, no)
AM_CONDITIONAL(HAVE_CXXTEST, test "$CXXTEST" != "no")

# Checks for libraries.
PKG_CHECK_MODULES([LIBXMLXX], [libxml++-2.6])

# Checks for header files.
AC_CHECK_HEADERS([libintl.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in])
AC_OUTPUT
