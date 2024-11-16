#include <stdio.h>
#include <stdlib.h>

#include "lib/convolve.h"

#define DEBUG 0
#define SIZE  10

void print_matrix(Matrix* m) {
    size_t w = Matrix_cols(m);
    size_t h = Matrix_rows(m);

    for (int y=0; y<h; ++y) {
        for (int x=0; x<w; ++x) {
            printf("\t%d", Matrix_get(m, x, y));
        }
        printf("\n");
    }
}

void set_pixels(Matrix* m) {
    size_t w = Matrix_cols(m);
    size_t h = Matrix_rows(m);

    for (int y=0; y<h; ++y) {
        for (int x=0; x<w; ++x) {
            Matrix_set(m, y, x, (rand() / (double) RAND_MAX) * 10);
        }
    }
}

int main() {

    Matrix* img = Matrix_new(10, 10);
    Matrix* msk = Matrix_new(5, 5);

    set_pixels(img);
    set_pixels(msk);
    print_matrix(img);
    printf("\n");
    Matrix* new = Matrix_convolve(img, msk);
    print_matrix(new);


    Matrix_free(img);

    return 0;

    Vector* base = Vector_new();
    Vector* mask = Vector_new();

    for (int i = 0; i < SIZE; ++i) {
        Vector_push(base, i);
        if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", base->size, base->capacity, base->data[base->size-1]);
        Vector_push(mask, i);
        if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", mask->size, mask->capacity, mask->data[mask->size-1]);
    }

    if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", base->size, base->capacity, base->data[base->size-1]);
    if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", mask->size, mask->capacity, mask->data[mask->size-1]);

    Vector* result = Vector_convolve(base, mask);

    if (1) {
        printf("[");
        for (int i = 0; i < Vector_size(result); ++i) {
            printf("%d", Vector_get(result, i));
            if (i+1 != Vector_size(result)) printf(",");
        }
        printf("]");
    }

    Vector_free(base);
    Vector_free(mask);
    Vector_free(result);

    return 0;
}
