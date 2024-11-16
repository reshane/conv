#include <unistd.h>

#ifndef NO_STD_LIB
#include <stdlib.h>
#endif

#ifndef NO_STD_IO
#include <stdio.h>
#endif

#ifndef NO_ASSERT
#include <assert.h>
#endif

#ifndef NO_STD_INT
#include <stdint.h>
#endif

// convolution

// vector

typedef struct {
    size_t size;
    size_t capacity;
    int* data;
} Vector;

Vector* Vector_new();

size_t Vector_size(Vector* v);

void Vector_push(Vector* v, int e);

int Vector_get(Vector* v, size_t idx);

void Vector_free(Vector* v);

Vector* Vector_convolve(Vector* a, Vector* b);

// matrix

typedef struct {
    size_t rows;
    size_t cols;
    int* data;
} Matrix;

Matrix* Matrix_new(size_t rows, size_t cols);

size_t Matrix_rows(Matrix* m);

size_t Matrix_cols(Matrix* m);

void Matrix_set(Matrix* m, size_t x, size_t y, int e);

int Matrix_get(Matrix* m, size_t x, size_t y);

void Matrix_free(Matrix* m);

Matrix* Matrix_convolve(Matrix* a, Matrix* b);
