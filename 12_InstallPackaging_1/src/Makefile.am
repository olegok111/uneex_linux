AM_CPPFLAGS= -D'LOCALEDIR="$(localedir)"' -D'MAXNUM=$(MAXNUM)'
bin_PROGRAMS=guess
guess_SOURCES=guess.c roman.h roman_table.h
BUILT_SOURCES=roman_table.h

lib_LTLIBRARIES = libroman.la
guess_LDADD = libroman.la

guess.c: roman.h roman_table.h

roman_table.h: roman_gen.py
	python3 $< $(MAXNUM) > $@
