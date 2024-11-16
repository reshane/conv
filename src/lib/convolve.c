#include "convolve.h"

Vector* Vector_new() {
    Vector* new = (Vector*) malloc(sizeof(Vector));
    if (!new) {
        printf("ERROR: Could initialize vector!");
        exit(1);
    }
    new->size = 0;
    new->capacity = 0;
    new->data = NULL;
    return new;
}

void Vector_push(Vector* v, int e) {
    if (v->capacity == 0) {
        v->capacity = 1;
        v->data = (int*) malloc(v->capacity * sizeof(int));
        if (!v->data) exit(1);
    }
    else if (v->size == v->capacity) {
        v->capacity *= 2;
        int* newMem = (int*) realloc(v->data, v->capacity * sizeof(int));
        if (!newMem) {
            // we have an error here... uh-oh!
            printf("ERROR: Could not increase the size of the vector");
            exit(1);
        }
        v->data = newMem;
    }
    v->data[v->size++] = e;
}

int Vector_get(Vector* v, size_t idx) {
    assert(idx < v->size);
    return v->data[idx];
}

size_t Vector_size(Vector* v) {
    return v->size;
}

size_t Vector_capacity(Vector* v) {
    return v->capacity;
}

void Vector_free(Vector* v) {
    free(v->data);
    free(v);
}

Vector* Vector_convolve(Vector* a, Vector* b) {
    Vector* result = Vector_new();
    // iterate b [Vector_size(b)-1..0]
    // iterate a [0..Vector_size(a)-1]
    int a_size = Vector_size(a);
    int b_size = Vector_size(b);

    // a[0] * b[0]
    // a[0] * b[1] + a[1] * b[0]
    // a[0] * b[2] + a[1] * b[1] + a[2] * b[0]
    // ...
    // a[1] * b[9] + a[2] * b[8] * a[3] * b[7]
    // a[2] * b[9] + a[3] * b[8] * a[4] * b[7]
    // one variable going from 0 -> a.size i
    // a indexed by a variable counting from 0->i
    // b indexed by a variable counting from i->0
    int a_start = 0, b_start = 0;
    for (int i=0; i<a_size+b_size; ++i) {
        int j=a_start,k=b_start,total=0;
        while (j<a_size && k>-1) {
            total += Vector_get(a, j) * Vector_get(b, k);
            j++;
            k--;
        }
        Vector_push(result, total);
        if (b_start == b_size-1) {
            a_start++;
        } else {
            b_start++;
        }
    }

    return result;
}

Matrix* Matrix_new(size_t cols, size_t rows) {
    Matrix* new = (Matrix*) malloc(sizeof(Matrix));
    if (!new) {
        printf("ERROR: Could not initialize matrix");
        exit(1);
    }
    new->rows = rows;
    new->cols = cols;
    new->data = (int*) malloc(rows*cols*sizeof(int));
    if (!new->data) {
        printf("ERROR: Could not initialize matrix data");
        exit(1);
    }
    return new;
}

size_t Matrix_rows(Matrix* m) {
    return m->rows;
}

size_t Matrix_cols(Matrix* m) {
    return m->cols;
}

void Matrix_set(Matrix* m, size_t x, size_t y, int e) {
    assert(x < m->cols);
    assert(y < m->rows);
    size_t idx = (m->rows * y) + x;
    m->data[idx] = e;
}

int Matrix_get(Matrix* m, size_t x, size_t y) {
    assert(x < m->cols);
    assert(y < m->rows);
    size_t idx = (m->rows * y) + x;
    return m->data[idx];
}

void Matrix_free(Matrix* m) {
    free(m->data);
    free(m);
}

Matrix* Matrix_convolve(Matrix* a, Matrix* b) {
    size_t a_w = Matrix_cols(a);
    size_t a_h = Matrix_rows(a);

    size_t b_w = Matrix_cols(b);
    size_t b_h = Matrix_rows(b);

    Matrix* result = Matrix_new(a_w, a_h);

    for (size_t y=0; y<a_h; ++y) {
        for (size_t x=0; x<a_w; ++x) {
            uint8_t bytes[4] = {0, 0, 0, 0};
            int weighted_sum = 0;
            for (size_t i=0; i<b_h; ++i) {
                for (size_t j=0; j<b_w; ++j) {
                    int c = Matrix_get(b,i,j);
                    int a_x = ((x+j)-(b_w/2));
                    int a_y = ((y+i)-(b_h/2));

                    if ((a_x>-1) && (a_x<a_w) && (a_y>-1) && (a_y<a_h)) {
                        weighted_sum += Matrix_get(a,a_x,a_y);
                    }
                }
            }
            Matrix_set(result,y,x, weighted_sum);
        }
    }
    return result;
}
