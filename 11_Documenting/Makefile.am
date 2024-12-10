AM_CPPFLAGS= -D'LOCALEDIR="$(localedir)"' -D'MAXNUM=$(MAXNUM)'
SUBDIRS=po
bin_PROGRAMS=guess
pkgdata_DATA=ru/LC_MESSAGES/guess.mo

@DX_RULES@

all-local: doxygen-doc

doxygen-doc/man/man1/guess.1: doxygen-doc
	help2man -N ./guess > $@

man1_MANS=doxygen-doc/man/man1/guess.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http:	doxygen-doc
	python3 -m http.server --directory $</html 5000

ru/LC_MESSAGES/guess.mo: po/ru.po
	mkdir --parents `dirname $@`
	msgfmt $< -o $@

po/ru.po:	po/Numberguessinggame.pot
	msgmerge -U $@ $<

po/Numberguessinggame.pot:	guess.c
	cd po; intltool-update ru

guess.c: roman_table.h

roman_table.h: roman_gen.py
	python3 $< $(MAXNUM) > $@
