#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "lib/convolve.h"

#define DEBUG 0
#define SIZE  10

void print_matrix(Matrix_i* m) {
    size_t w = Matrix_i_cols(m);
    size_t h = Matrix_i_rows(m);

    for (int y=0; y<h; ++y) {
        for (int x=0; x<w; ++x) {
            printf("\t%d", Matrix_i_get(m, x, y));
        }
        printf("\n");
    }
}

void set_pixels(Matrix_i* m) {
    size_t w = Matrix_i_cols(m);
    size_t h = Matrix_i_rows(m);

    for (int y=0; y<h; ++y) {
        for (int x=0; x<w; ++x) {
            Matrix_i_set(m, y, x, (rand() / (double) RAND_MAX) * 10);
        }
    }
}

void convolve_vector_i() {
    Vector_i* base = Vector_i_new();
    Vector_i* mask = Vector_i_new();

    for (int i = 0; i < SIZE; ++i) {
        Vector_i_push(base, i);
        if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", base->size, base->capacity, base->data[base->size-1]);
        Vector_i_push(mask, i);
        if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", mask->size, mask->capacity, mask->data[mask->size-1]);
    }

    if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", base->size, base->capacity, base->data[base->size-1]);
    if (DEBUG) printf("vector contents\n\tsize: %d\n\tcap: %d\n\tlast: %d\n", mask->size, mask->capacity, mask->data[mask->size-1]);

    Vector_i* result = Vector_i_convolve(base, mask);

    if (1) {
        printf("[");
        for (int i = 0; i < Vector_i_size(result); ++i) {
            printf("%d", Vector_i_get(result, i));
            if (i+1 != Vector_i_size(result)) printf(",");
        }
        printf("]");
    }

    Vector_i_free(base);
    Vector_i_free(mask);
    Vector_i_free(result);

}

void convolve_matrix_i() {
    Matrix_i* img = Matrix_i_new(10, 10);
    Matrix_i* msk = Matrix_i_new(5, 5);

    set_pixels(img);
    set_pixels(msk);
    print_matrix(img);
    printf("\n");
    Matrix_i* new = Matrix_i_convolve(img, msk);
    print_matrix(new);


    Matrix_i_free(img);

}

void tv_static(Matrix_u32* img) {
    size_t w = Matrix_u32_cols(img);
    size_t h = Matrix_u32_rows(img);

    for (int y=0; y<h; ++y) {
        for (int x=0; x<w; ++x) {
            uint32_t pixel = 0xFF000000;
            if ((int)((rand()/(float)RAND_MAX) + 0.5)) {
                pixel = 0xFFFFFF;
            }
            Matrix_u32_set(img,x,y,pixel);
        }
    }
}

void flat_blur_matrix(Matrix_f* msk) {
    size_t msk_w = Matrix_f_cols(msk);
    size_t msk_h = Matrix_f_rows(msk);
    for (int y=0; y<msk_h; ++y) {
        for (int x=0; x<msk_w; ++x) {
            Matrix_f_set(msk,y,x,1.0/(msk_w*msk_h));
        }
    }
}

void save_img_as_ppm(Matrix_u32* img, const char *file_path) {
    FILE* f = fopen(file_path, "wb");
    if (f == NULL) {
        fprintf(stderr, "ERROR: could not write into file %s: %s\n", file_path, strerror(errno));
        exit(1);
    }
    size_t img_w = Matrix_u32_cols(img);
    size_t img_h = Matrix_u32_rows(img);
    fprintf(f, "P6\n%d %d 255\n", img_w, img_h);
    for (size_t y=0; y<img_h; ++y) {
        for (size_t x=0; x<img_w; ++x) {
            uint32_t pixel = Matrix_u32_get(img,x,y);
            uint8_t bytes[3] = {
                (pixel&0x0000FF)>>8*0,
                (pixel&0x00FF00)>>8*1,
                (pixel&0xFF0000)>>8*2
            };
            fwrite(bytes, sizeof(bytes), 1, f);
            assert(!ferror(f));
        }
    }
    fclose(f);
}

void create_images() {
    Matrix_u32* img = Matrix_u32_new(200, 200);
    Matrix_f* msk = Matrix_f_new(4, 4);
    tv_static(img);
    flat_blur_matrix(msk);
    save_img_as_ppm(img, "original.ppm");
    Matrix_u32* blr = Matrix_u32_f_convolve(img, msk);
    save_img_as_ppm(blr, "blurred.ppm");
}

int main() {
    srand(time(NULL));
    create_images();
    return 0;
}


