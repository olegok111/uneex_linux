#include <stdio.h>
#include <stdlib.h>

typedef struct range {
    int start;
    int stop;
    int step;
    int cur;
} range;

void range_init(range *pr) {
    pr->cur = pr->start;
}

int range_run(range *pr) {
    return (pr->cur < pr->stop);
}

void range_next(range *pr) {
    pr->cur += pr->step;
}

int range_get(range *pr) {
    return pr->cur;
}

void argparse(int argc, char *argv[], int *pstart, int *pstop, int *pstep) {
    switch (argc) {
        case 4:
            *pstep = strtol(argv[3], NULL, 10);
            *pstop = strtol(argv[2], NULL, 10);
            *pstart = strtol(argv[1], NULL, 10);
            break;
        case 3:
            *pstep = 1;
            *pstop = strtol(argv[2], NULL, 10);
            *pstart = strtol(argv[1], NULL, 10);
            break;
        case 2:
            *pstep = 1;
            *pstop = strtol(argv[1], NULL, 10);
            *pstart = 0;
            break;
        default:
            printf(
"Usage: range STOP\n" \
"       range START STOP [STEP]\n" \
"Print out a range of integer numbers with given start, stop and step\n" \
" parameters, like in python's range(). If not given, START and STEP default\n" \
" to 0 and 1 respectively.\n"
            );
            *pstop = 0;
            *pstart = 0;
            break;
    }
}

int main(int argc, char *argv[]) {
        range I;
        argparse(argc, argv, &I.start, &I.stop, &I.step);
        for(range_init(&I); range_run(&I); range_next(&I))
                printf("%d\n", range_get(&I));
        return 0;
}
