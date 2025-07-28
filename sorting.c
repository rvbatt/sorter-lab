#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare_unsigned(const void *left, const void *right);

double sort_array(const char *algorithm, unsigned *array, short len) {
    clock_t startTick, endTick;

    if (strcmp(algorithm, "benchmark") == 0) {
        startTick = clock();
        qsort(array, len, sizeof(unsigned), compare_unsigned);
        endTick = clock();
    } else {
        printf("Unknown sorting algorithm: %s\n", algorithm);
        return -1;
    }

    return (double)(endTick - startTick) / CLOCKS_PER_SEC;
}

int compare_unsigned(const void *left, const void *right) {
    return (*(unsigned *)left - *(unsigned *)right);
}
