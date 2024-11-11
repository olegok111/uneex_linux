AM_CPPFLAGS= -D'LOCALEDIR="$(localedir)"'
SUBDIRS=po
bin_PROGRAMS=guess
pkgdata_DATA=ru/LC_MESSAGES/guess.mo

ru/LC_MESSAGES/guess.mo: po/ru.po
	mkdir --parents `dirname $@`
	msgfmt $< -o $@

po/ru.po:	po/messages.pot
	msgmerge -U $@ $<

po/messages.pot:	po/guess.pot guess.c
	xgettext -k_ -c guess.c -o po/messages.new.pot
	cp po/guess.pot messages.pot
	msgmerge -U messages.pot messages.new.pot
