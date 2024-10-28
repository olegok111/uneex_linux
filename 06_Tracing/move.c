#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

_Noreturn void handle_err(const char what_failed[]) {
    perror(what_failed);
    exit(errno);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf(
"Usage: move FILE1 FILE2\n" \
"Move contents of FILE1 to FILE2 and delete FILE1 on success.\n" \
" On failure exit status is set to errno.\n"
);
        return 1;
    }

    char* infilename = argv[1];

    struct stat statbuf;
    if (stat(infilename, &statbuf) == -1) {
        handle_err("stat() input file");
    }
    size_t infilesize = (size_t) statbuf.st_size;

    int infd;
    if ((infd = open(infilename, O_RDONLY)) == -1) {
        handle_err("open() input file");
    }

    char* buf = (char*) calloc(infilesize, sizeof(char));
    if (buf == NULL) {
        handle_err("calloc()");
    }

    if (read(infd, buf, infilesize) == -1) {
        handle_err("read() from input file");
    }

    if (close(infd) != 0) {
        handle_err("close() input file");
    }

    char* outfilename = argv[2];
    int outfd;
    if ((outfd = open(outfilename, O_CREAT | O_TRUNC | O_WRONLY, 00664)) == -1) {
        handle_err("open() output file");
    }

    if (write(outfd, buf, infilesize) == -1) {
        handle_err("write() to output file");
    }

    if (close(outfd) != 0) {
        handle_err("close() output file");
    }

    if (unlink(infilename) != 0) {
        handle_err("unlink() input file");
    }

    free(buf);

    return 0;
}
