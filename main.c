#include <stdio.h>

// include the implementation (see stb style library:
// https://github.com/nothings/stb)
#define CMAT_IMPL
#include "cmat.h"

// a function that print the test matrix and verify it match with expected
void test_example(const CMat *test, const CMat *expected) {
    assert(test->ncol == expected->ncol && "ncol don't match");
    assert(test->nrow == expected->nrow && "nrow don't match");

    CMat_print(test);                                 // print a matrix to stdout
    for (size_t row = 0; row < test->nrow; ++row) {
        for (size_t col = 0; col < test->ncol; ++col) {
            CMatType t = CMat_at(test, row, col);     // access test at row col
            CMatType e = CMat_at(expected, row, col); // expected test at row col
            if (t != e) {
                printf("error at arr[%d][%d], got '%lf', expected '%lf'\n", row, col, t, e);
                exit(1);
            }
        }
    }
}
void example_add() {
    // create a 3x2 matrix
    CMatType arr1[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    CMat     cmat1      = CMat_from_2darr(arr1);

    // create a 3x2 matrix
    CMatType arr2[3][2] = {{10, 11}, {20, 21}, {30, 31}};
    CMat     cmat2      = CMat_from_2darr(arr2);

    // create a 3x2 matrix
    CMatType arr_expected[3][2] = {{11, 13}, {23, 25}, {35, 37}};
    CMat     cmat_expected      = CMat_from_2darr(arr_expected);

    // add the matrix 2 to the matrix 1 element by element
    CMat_iterate2(&cmat1, &cmat2, row, col, val1, val2, *val1 += *val2;);
    test_example(&cmat1, &cmat_expected);
}
void example_dot() {
    // create a 2x3 matrix
    CMatType arr1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    CMat     cmat1      = CMat_from_2darr(arr1);

    // create a 3x2 matrix
    CMatType arr2[3][2] = {{10, 11}, {20, 21}, {30, 31}};
    CMat     cmat2      = CMat_from_2darr(arr2);

    // create an uninitialized 2x2 matrix
    CMatType arr3[2][2];
    CMat     cmat3 = CMat_from_2darr(arr3);

    // create a 2x2 matrix
    CMatType arr_expected[2][2] = {{140, 146}, {320, 335}};
    CMat     cmat_expected      = CMat_from_2darr(arr_expected);

    // do a dot product between matrix 1 and matrix 2 and store the result in 3
    CMat_dot(&cmat3, &cmat1, &cmat2);
    test_example(&cmat3, &cmat_expected);
}
void example_subarr() {
    CMatType arr[1][6] = {{1, 2, 3, 4, 5, 6}};
    // create a 2x2 matrix from an array by skiping the first column
    CMat subcmat = CMat_from_subarr(arr, 0, 1, 2, 2);
    // create a 1x2 matrix from a matrix by skiping the first row
    CMat subcmat2 = CMat_from_submat(&subcmat, 1, 0, 1, 2);

    // create a 1x2 matrix
    CMatType arr_expected[1][2] = {{5, 6}};
    CMat     cmat_expected      = CMat_from_2darr(arr_expected);

    test_example(&subcmat2, &cmat_expected);
}
void example_identity() {
    // create an uninitialized 2x2 matrix
    CMatType arr_identity[2][2];
    CMat     cmat_identity = CMat_from_2darr(arr_identity);
    // populate the matrix with a 2x2 identity matrix
    CMat_identity(&cmat_identity);

    // create a 2x2 matrix
    CMatType arr_expected[2][2] = {{1, 0}, {0, 1}};
    CMat     cmat_expected      = CMat_from_2darr(arr_expected);

    test_example(&cmat_identity, &cmat_expected);
}
void example_det() {
    // create a 4x4 matrix
    CMatType arr[4][4] = {{-1, 0, 0, -2}, {1, 0, 5, -5}, {0, 1, 4, 0}, {0, 0, -5, 0}};
    CMat     cmat      = CMat_from_2darr(arr);

    // calculate the determinant
    CMatType det      = CMat_det(&cmat);
    CMatType expected = -35;

    printf("det = %lf", det);
    if (det != expected) {
        printf(" (expected %f)\n", expected);
        exit(1);
    }
    printf("\n");
}
void example_inverse() {
    // create a 4x4 matrix
    CMatType arr[4][4] = {{-1, 0, 0, -2}, {1, 0, 5, -5}, {0, 1, 4, 0}, {0, 0, -5, 0}};
    CMat     cmat      = CMat_from_2darr(arr);

    // create an uninitialized 4x4 matrix
    CMatType arr_inverse[4][4];
    CMat     cmat_inverse = CMat_from_2darr(arr_inverse);
    // populate the matrix with the inverse of the previous matrix
    CMat_inverse(&cmat_inverse, &cmat);

    // create a 4x4 matrix
    CMatType arr_expected[4][4] = {{-5.0 / 7.0, 2.0 / 7.0, 0.0, 2.0 / 7.0},
                                   {0.0, 0.0, 1.0, 4.0 / 5.0},
                                   {0.0, 0.0, 0.0, -1.0 / 5.0},
                                   {-1.0 / 7.0, -1.0 / 7.0, 0.0, -1.0 / 7.0}};
    CMat     cmat_expected      = CMat_from_2darr(arr_expected);

    test_example(&cmat_inverse, &cmat_expected);
}

int main() {
    example_add();
    puts("=========================");
    example_dot();
    puts("=========================");
    example_subarr();
    puts("=========================");
    example_identity();
    puts("=========================");
    example_det();
    puts("=========================");
    example_inverse();
    return 0;
}
