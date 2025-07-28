#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void randomize_array(unsigned *array, short len, unsigned min, unsigned max);
void print_array(unsigned *array, short len);
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

    clock_t startTick = clock();
    qsort(array, len, sizeof(unsigned), compare_unsigned);
    clock_t endTick = clock();
    double timeDelta = (double)(endTick - startTick) / CLOCKS_PER_SEC;

    printf("Sorted Array: ");
    print_array(array, len);
    printf("\nCPU Time: %lfs\n", timeDelta);

    free(array);
    return 0;
}

int compare_unsigned(const void *left, const void *right) {
    return (*(unsigned *)left - *(unsigned *)right);
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

void print_array(unsigned *array, short len) {
    (void) printf("[");
    for (short i = 0; i < len - 1; ++i)
        (void) printf("%u, ", array[i]);
    (void) printf("%u]", array[len - 1]);
}