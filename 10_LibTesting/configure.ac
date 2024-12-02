#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([Libtoolized growable buffer library], [0.0.1], [na@example.com])
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/grobuf_const.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Joint pkgconfig library/include tests
PKG_CHECK_MODULES([CHECK],[check])

# Variable definitins
AC_SUBST(CK_VERBOSITY, verbose)
AC_ARG_VAR(CK_VERBOSITY, [Default: "verbose", can be "silent", "minimal" or "normal")])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gettimeofday strtoull])

AC_CONFIG_FILES([Makefile
		 		 src/Makefile
                 tests/Makefile])
AC_OUTPUT
