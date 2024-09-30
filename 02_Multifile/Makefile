.PHONY: clean distclean
GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so
TRASH = *.o *~ o.* *.out
CFLAGS = -Wall -fPIC

all:    prog prog-a prog-so

.SECONDARY:	fun.o const.o
.INTERMEDIATE:	liboutput_static.a(fun.o const.o)

liboutput_static.a:	liboutput_static.a(fun.o const.o)

liboutput.so:	fun.o const.o
	$(CC) -shared -o $@ $^

prog-a:	prog.o liboutput_static.a
	$(CC) $< -L. -loutput_static -o $@

prog-so:	prog.o liboutput.so
	$(CC) $< -L. -loutput -o $@

prog:	prog.o fun.o const.o

fun.o prog.o:  outlib.h

test-%: prog prog-a prog-so
	./prog `seq 1 $(subst test-,,$@)` > $@.out 2>&1
	./prog-a `seq 1 $(subst test-,,$@)` > $@.a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so `seq 1 $(subst test-,,$@)` > $@.so.out 2>&1
	@# replace program names in their output with just 'prog':
	ls $@*.out | xargs sed -i 's/.\/prog\S*/prog/g'
	cmp $@.out $@.a.out
	cmp $@.out $@.so.out

test:	test-0 test-1 test-3

clean:
	rm -rf $(TRASH) $(GENERATES)
