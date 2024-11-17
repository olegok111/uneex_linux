CFLAGS=-Wall -g
GENERATES=maze maze1 maze1.c maze2 maze2.c maze3 maze3.c

%.c:
	[ -f $@.patch ] && patch -o $@ < $@.patch || true

run: maze maze1 maze2 maze3
	./maze
	./maze1 7
	./maze2 '.@' 8
	./maze3 1001 '.&' 9
	./maze3 8123 '.&' 9

clean:
	rm -f $(GENERATES)

all: run
