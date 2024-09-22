#include <curses.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define DX 3
#define ASCII_ESC 27
#define ASCII_SPACE 32

char* create_file_mapping(const char filename[], const size_t filesize) {
    int fd;
    char* mapping;

    if ((fd = open(filename, O_RDONLY)) == -1) {
        fprintf(stderr, "Failed to open the file.\n");
        return NULL;
    }

    if ((mapping = (char*) mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
        fprintf(stderr, "Failed to map the file to memory.\n");
        return NULL;
    }

    return mapping;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "Pass the filename as the first argument.\n");
        return 1;
    }

    char* filename = argv[1];
    struct stat statbuf;

    if (stat(filename, &statbuf) == -1) {
        fprintf(stderr, "Failed to get the file's stats.\n");
        return 1;
    }

    size_t filesize = (size_t) statbuf.st_size;
    char* file_mapping = create_file_mapping(filename, filesize);

    if (!file_mapping) {
        return 1;
    }

    initscr();
    noecho();
    cbreak();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // border
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK); // special chars
    printw("File: %s\nESC to exit, SPACE to scroll", filename);
    refresh();

    WINDOW* borderwin = newwin(LINES - DX*2, COLS - DX*2, DX, DX);
    WINDOW* textwin = newwin(LINES - DX*2 - 2, COLS - DX*2 - 2, DX + 1, DX + 1);

    wattron(borderwin, COLOR_PAIR(1));
    box(borderwin, 0, 0);
    wrefresh(borderwin);

    scrollok(textwin, TRUE);

    int maxy = LINES - DX*2 - 2;
    int maxx = COLS - DX*2 - 2;
    int c = 0;
    int y, x;

    for (size_t i = 0; i < filesize; ++i) {
        getyx(textwin, y, x);

        if (y == maxy - 1 && (file_mapping[i] == '\n' || x == maxx - 1)) {
            do {
                c = wgetch(textwin);
            } while (c != ASCII_ESC && c != ASCII_SPACE);
        }

        if (c == ASCII_ESC) {
            break;
        }

        if (file_mapping[i] == '\0') {
            wattron(textwin, COLOR_PAIR(2));
            waddch(textwin, '0');
            wattroff(textwin, COLOR_PAIR(2));
        } else {
            waddch(textwin, file_mapping[i]);
        }

        wrefresh(textwin);
    }

    while (c != ASCII_ESC) {
        c = wgetch(textwin);
    }
    
    endwin();
    return 0;
}
