#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomize_array(unsigned array[], short len, unsigned min, unsigned max);
void print_array(unsigned array[], short len);
int compare_unsigned(const void *left, const void *right);

int main(int argc, char *argv[]) {
    unsigned array[16];

    if (argc == 2) {
        srand(atoi(argv[1]));
    } else {
        srand((unsigned) time(NULL));
    }

    randomize_array(array, 16, 0, 65535);

    printf("Unsorted Array: ");
    print_array(array, 16);
    printf("\n");

    qsort(array, 16, sizeof(unsigned), compare_unsigned);

    printf("Sorted Array: ");
    print_array(array, 16);
    printf("\n");

    return 0;
}

int compare_unsigned(const void *left, const void *right) {
    return (*(unsigned *)left - *(unsigned *)right);
}

void randomize_array(unsigned array[], short len, unsigned min, unsigned max) {
    double randFrac;
    unsigned offset;

    for (unsigned short i = 0; i < len; ++i) {
        randFrac = (double) rand() / ((double) RAND_MAX + 1);
        offset = (unsigned) (randFrac * (max + 1 - min));
        array[i] = min + offset;
    }
}

void print_array(unsigned array[], short len) {
    (void) printf("[");
    for (short i = 0; i < len - 1; ++i)
        (void) printf("%u, ", array[i]);
    (void) printf("%u]", array[len - 1]);
}