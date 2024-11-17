#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

static char** maze;
static size_t N;
static char wall, empty;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    N = 13;
    wall = '#';
    empty = '.';

    maze = (char**) malloc(N * sizeof(char*));
    for (size_t i = 0; i < N; ++i) {
        maze[i] = (char*) malloc(N * sizeof(char));
        memset(maze[i], wall, N * sizeof(char));
    }

    size_t group_start = 0;
    for (size_t i = 1; i < N-1; i += 2) {
        for (size_t j = 1; j < N-1; j += 2) {
            if (i == 1) {
                memset(maze[i] + 1, empty, N-2);
                continue;
            }

            maze[i][j] = empty;

            // if no group, make current cell the start of new group
            if (group_start == 0) {
                group_start = j;
            }

            if (rand() % 2 || j == N-2) {
                // smash wall over a random cell in the group
                maze[i-1][group_start + ((rand() % (j - group_start + 1)) & ~1)] = empty;
                // delete the group
                group_start = 0;
            } else {
                // smash wall to the right
                maze[i][j+1] = empty;
            }
        }
    }

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            putchar(maze[i][j]);
        }

        puts("");
        free(maze[i]);
    }
    free(maze);

    return 0;
}
