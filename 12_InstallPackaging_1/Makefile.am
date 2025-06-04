SUBDIRS=po src tests
pkgdata_DATA=ru/LC_MESSAGES/guess.mo

@DX_RULES@

all-local: doxygen-doc

doxygen-doc/man/man1/guess.1: doxygen-doc
	help2man -N src/guess > $@

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

po/Numberguessinggame.pot:	src/guess.c
	cd po; intltool-update ru
