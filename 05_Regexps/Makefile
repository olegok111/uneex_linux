CC=cc
CFLAGS=-Wall -O0 -g
GENERATES=esub
TRASH=*.in *.out

test: esub
	echo abc | sed -E "s/.*/r/" > 0sed.out
	./esub ".*" r abc > 0prog.out
	cmp 0sed.out 0prog.out

	@# using /bin/echo to avoid the backslash problem
	/bin/echo 1234\\256789 | sed -E 's/([[:digit:]])(.*)\1/FOUND\2\1/' > 1sed.out
	./esub '([[:digit:]])(.*)\1' 'FOUND\2\1' 1234\\256789 > 1prog.out
	cmp 1sed.out 1prog.out

	date > date.in

	cat date.in | sed -E "s/([[:digit:]]+)(.*)([[:digit:]]+)/<1=\1><2=\2><3=\3>/" > 2sed.out
	./esub "([[:digit:]]+)(.*)([[:digit:]]+)" "<1=\1><2=\2><3=\3>" "`cat date.in`" > 2prog.out
	cmp 2sed.out 2prog.out

	cat date.in | sed -E "s/(([[:digit:]]+).*)([[:digit:]]+)/<1=\1><2=\2><3=\3>/" > 3sed.out
	./esub "(([[:digit:]]+).*)([[:digit:]]+)" "<1=\1><2=\2><3=\3>" "`cat date.in`" > 3prog.out
	cmp 3sed.out 3prog.out

check: test

all: esub

clean:
	rm -rf $(GENERATES) $(TRASH)
