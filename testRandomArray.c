#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print_array(unsigned *array, short len);
void randomize_array(unsigned *array, short len, unsigned min, unsigned max);
double sort_array(const char *algorithm, unsigned *array, short len);

int compare_unsigned(const void *left, const void *right);

int main(int argc, char *argv[]) {
    /*
    Usage:
    $ testRandomArray (<length>) (<seed>)
        <length> (optional): length of the random array that will be tested. Default is 16;
        <seed> (optional): the seed for the pseudorandom number generator.
    */
    short len;
    unsigned *array;
    char *debug;
    double benchmarkTime;

    if (argc < 2) {
        len = 16;
    }
    else {
        len = (short) strtol(argv[1], &debug, 10);
        if (strcmp(debug, "\0") != 0) {
            printf("Invalid character in length: %s\n", debug);
            return 1;
        }
    }

    if (argc < 3) {
        srand((unsigned) time(NULL));
    }
    else {
        srand((unsigned) strtol(argv[2], &debug, 10));
        if (strcmp(debug, "\0") != 0) {
            printf("Invalid character in seed: %s\n", debug);
            return 2;
        }
    }

    array = (unsigned*) malloc(len * sizeof(unsigned));
    randomize_array(array, len, 0, 65535);

    printf("Unsorted Array: ");
    print_array(array, len);
    printf("\n");

    benchmarkTime = sort_array("benchmark", array, len);

    printf("Sorted Array: ");
    print_array(array, len);
    printf("\nBenchmark CPU Time: %lfs\n", benchmarkTime);

    free(array);
    return 0;
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

    for (unsigned short i = 0; i < len; ++i) {
        randFrac = (double) rand() / ((double) RAND_MAX + 1);
        offset = (unsigned) (randFrac * (max + 1 - min));
        array[i] = min + offset;
    }
}

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
