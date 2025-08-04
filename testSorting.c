#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sorting.h"

void print_array(unsigned *array, short len);
void randomize_array(unsigned *array, short len, unsigned min, unsigned max);

int main(int argc, char *argv[]) {
    /*
    Usage:
    $ ./testSorting.exe <algorithm> (<length>) (<seed>)
    where
        <algorithm> = sorting algorithm to be tested. Must be one of:
            benchmark (default implementation)
        <length> (optional) = length of the random array that will be tested. Default is 16;
        <seed> (optional) = the seed for the pseudorandom number generator.
    */
    int returnCode = 0;
    short len = 16;
    unsigned *unsorted, *sorted, *toSort;
    char *algorithm, *debug;
    double benchmarkTime, testTime;

    if (argc < 2) {
        printf("Missing algorithm argument. Abort.\n");
        return 1;
    } else {
        algorithm = argv[1];
    }

    if (argc >= 3) {
        len = (short) strtol(argv[2], &debug, 10);
        if (strcmp(debug, "\0") != 0) {
            printf("Invalid character in length: %s\n", debug);
            return 2;
        }
    }

    if (argc < 4) {
        srand((unsigned) time(NULL));
    }
    else {
        srand((unsigned) strtol(argv[3], &debug, 10));
        if (strcmp(debug, "\0") != 0) {
            printf("Invalid character in seed: %s\n", debug);
            return 3;
        }
    }

    unsorted = (unsigned*) malloc(len * sizeof(unsigned));
    randomize_array(unsorted, len, 0, 65535);

    printf("Unsorted Array: ");
    print_array(unsorted, len);
    printf("\n\n");

    sorted = (unsigned*) malloc(len * sizeof(unsigned));
    memcpy(sorted, unsorted, len * sizeof(unsigned));
    benchmarkTime = sort_array("benchmark", sorted, len);

    printf("Sorted Array: ");
    print_array(sorted, len);
    printf("\nBenchmark CPU Time: %lfs\n\n", benchmarkTime);

    toSort = (unsigned*) malloc(len * sizeof(unsigned));
    memcpy(toSort, unsorted, len * sizeof(unsigned));
    testTime = sort_array(algorithm, toSort, len);

    if (testTime < 0) {
        printf("Invalid algorithm: %s. Aborting.\n", algorithm);
        returnCode = 1;
    } else {
        if (memcmp(toSort, sorted, len * sizeof(unsigned)) != 0) {
            printf("SORTING FAILED. %s sort needs checking.\n", algorithm);
            returnCode = 10;
        }

        printf("%s sort array: ", algorithm);
        print_array(toSort, len);
        printf("\n%s sort CPU time: %lfs\n", algorithm, testTime);
    }

    free(unsorted);
    free(sorted);
    free(toSort);

    return returnCode;
}

void print_array(unsigned *array, short len) {
    (void) printf("[");
    for (short i = 0; i < len - 1; ++i)
        (void) printf("%u, ", array[i]);
    (void) printf("%u]", array[len - 1]);
}

void randomize_array(unsigned *array, short len, unsigned min, unsigned max) {
    double randFrac;
    unsigned offset;

    for (short i = 0; i < len; ++i) {
        randFrac = (double) rand() / ((double) RAND_MAX + 1);
        offset = (unsigned) (randFrac * (max + 1 - min));
        array[i] = min + offset;
    }
}
