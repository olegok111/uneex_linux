AM_CPPFLAGS= -D'LOCALEDIR="$(localedir)"'
SUBDIRS=po
bin_PROGRAMS=guess
pkgdata_DATA=ru/LC_MESSAGES/guess.mo

ru/LC_MESSAGES/guess.mo: po/ru.po
	mkdir --parents `dirname $@`
	msgfmt $< -o $@

po/ru.po:	po/guess.pot
	msgmerge -U $@ $<

po/guess.pot:	guess.c
	cd po; intltool-update ru
