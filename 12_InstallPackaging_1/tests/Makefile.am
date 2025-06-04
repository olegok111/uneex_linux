TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
TESTS = roman
check_PROGRAMS = roman

.ts.c:
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/src -D'MAXNUM=$(MAXNUM)' @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libroman.la @CHECK_LIBS@
