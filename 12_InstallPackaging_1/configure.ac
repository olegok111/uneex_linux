#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Number guessing game],[0.4],[BUG-REPORT-ADDRESS],[guess])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([guess])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
ALL_LINGUAS="ru"
LT_INIT([disable-static])
PC_INIT([3.0])

# Joint pkgconfig library/include tests
PKG_CHECK_MODULES([CHECK],[check])

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL

# Variable definitions
AC_ARG_WITH([maxnum], AS_HELP_STRING([--with-maxnum=N],[Max number that can be picked (1-4999) [default=100]]), MAXNUM=$withval, MAXNUM=100)
if test $MAXNUM -lt 1; then
	AC_MSG_ERROR([maxnum is too low (<1)])
fi
if test $MAXNUM -gt 4999; then
	AC_MSG_ERROR([maxnum is too high; Roman numerals do not go that far...])
fi

AC_SUBST(MAXNUM)
AC_SUBST(CK_VERBOSITY, verbose)
AC_ARG_VAR(CK_VERBOSITY, [Default: "verbose", can be "silent", "minimal" or "normal")])

# Checks for libraries.
AC_SEARCH_LIBS([argp_parse], [argp], [], [
  AC_MSG_ERROR([argp_parse() not found])
])

# Checks for python modules.
PC_PYTHON_CHECK_PACKAGE([roman])

# Checks for header files.
AC_CHECK_HEADERS([libintl.h argp.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in Doxyfile src/Makefile tests/Makefile])
AC_OUTPUT
