#include <string.h>

// tests

#include "lib/convolve.h"

// test helpers
int failed = 0;
#define TEST(name) void name()
#define RUN_TEST(name) printf("\n\033[1m%s\n\033[0m", #name); name()
#define ASSERT(expr) if (!(expr)) { \
    failed = 1; \
    printf("\033[0;31mFAIL: %s\n\033[0m", #expr); \
} else { \
    printf("\033[0;32mPASS: %s\n\033[0m", #expr); \
}
#define ASSERT_STR_EQ(str1, str2) ASSERT(strcmp(str1, str2) == 0)

TEST(test_Vector_i) {
    Vector_i* my_vec = Vector_i_new();
    Vector_i_push(my_vec, 3);
    ASSERT(Vector_i_get(my_vec, 3) == 0);
    Vector_i_free(my_vec);
}

TEST(test_Vector_f) {
    Vector_f* my_vec = Vector_f_new();
    Vector_f_push(my_vec, 0.7);
    ASSERT(Vector_f_get(my_vec, 0.7) == 0);
    Vector_f_free(my_vec);
}

TEST(test_Matrix_i) {
    Matrix_i* mat = Matrix_i_new(10, 10);
    Matrix_i_set(mat, 4, 4, 10);
    ASSERT(Matrix_i_get(mat, 4, 4) == 10);
    Matrix_i_free(mat);
}

TEST(test_Matrix_f) {
    Matrix_f* mat = Matrix_f_new(10, 10);
    Matrix_f_set(mat, 4, 4, 1.7);
    ASSERT(Matrix_f_get(mat, 4, 4) == 1.7);
    Matrix_f_free(mat);
}

TEST(test_Matrix_u32) {
    Matrix_u32* mat = Matrix_u32_new(10, 0xFF00FF18);
    Matrix_u32_set(mat, 4, 4, 10);
    ASSERT(Matrix_u32_get(mat, 4, 4) == 0xFF00FF18);
    Matrix_u32_free(mat);
}

int main() {
    RUN_TEST(test_Vector_i);
    RUN_TEST(test_Vector_f);
    RUN_TEST(test_Matrix_i);
    RUN_TEST(test_Matrix_f);
    RUN_TEST(test_Matrix_u32);
    return 0;
}
