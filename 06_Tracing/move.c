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
        handle_err("stat() on input file");
    }
    size_t infilesize = (size_t) statbuf.st_size;

    int infd;
    if ((infd = open(infilename, O_RDONLY)) == -1) {
        handle_err("open() on input file");
    }

    char* infile_mapping = (char*) mmap(NULL, infilesize, PROT_READ, MAP_PRIVATE, infd, 0);
    if (infile_mapping == NULL) {
        handle_err("mmap() on input file");
    }

    char* outfilename = argv[2];
    FILE* outfile = fopen(outfilename, "wb");
    if (outfile == NULL) {
        handle_err("fopen() on output file");
    }

    if (fwrite(infile_mapping, sizeof(char), infilesize, outfile) != infilesize) {
        handle_err("fwrite()");
    }

    if (munmap(infile_mapping, infilesize) != 0) {
        handle_err("munmap() on input file");
    }

    if (unlink(infilename) != 0) {
        handle_err("unlink() on input file");
    }

    if (fclose(outfile) != 0) {
        handle_err("fclose() on output file");
    }

    return 0;
}
