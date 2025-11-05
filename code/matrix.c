///////////////////////////////////////////////////////////////////////////////
// CSPB 3753 — Lab 8: Markov Chains
// Implementation of basic dense matrix operations, including matrix multiply.
//
// Author: Cole Akers
// Date: November 5, 2025.
//
// Overview:
//   - matrix_create / matrix_free manage heap-allocated matrices.
//   - matrix_get / matrix_set provide element access in row-major order.
//   - matrix_multiply implements C = A * B using the standard triple loop.
//   - matrix_print displays a matrix for debugging or demonstration.
//
// Formatting:
//   - Braces on same line, 4-space indent, no tabs.
//
///////////////////////////////////////////////////////////////////////////////

#include "matrix.h"

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, calloc, free

// index_of
// --------
// Convert (i, j) into a linear index for row-major storage.
//
// m: matrix (for its number of columns).
// i: row index.
// j: column index.
//
// Returns: index into m->data for element (i, j).
static size_t index_of(const Matrix *m, size_t i, size_t j) {
    // Row-major layout: element (i, j) lives at i * cols + j.
    return i * m->cols + j;
}

/**
 * matrix_create
 * -------------
 * Allocate and zero-initialize a rows x cols matrix.
 */
Matrix *matrix_create(size_t rows, size_t cols) {
    // Allocate the Matrix struct itself.
    Matrix *m = malloc(sizeof(Matrix));
    if (!m) {
        // Allocation failed; return NULL to caller.
        return NULL;
    }

    // Store dimensions.
    m->rows = rows;
    m->cols = cols;

    // Allocate and zero out the backing array of doubles.
    // We allocate rows * cols elements.
    m->data = calloc(rows * cols, sizeof(double));
    if (!m->data) {
        // If allocation fails, free the struct and return NULL.
        free(m);
        return NULL;
    }

    return m;
}

/**
 * matrix_free
 * -----------
 * Free the backing array and the Matrix struct.
 */
void matrix_free(Matrix *m) {
    // Allow freeing a NULL pointer; nothing to do in that case.
    if (!m) {
        return;
    }

    // Free the underlying data array first.
    free(m->data);
    // Then free the struct itself.
    free(m);
}

/**
 * matrix_get
 * ----------
 * Return the value stored at (i, j).
 */
double matrix_get(const Matrix *m, size_t i, size_t j) {
    // Compute the linear index and read the value.
    return m->data[index_of(m, i, j)];
}

/**
 * matrix_set
 * ----------
 * Store value at (i, j).
 */
void matrix_set(Matrix *m, size_t i, size_t j, double value) {
    // Compute the linear index and write the value.
    m->data[index_of(m, i, j)] = value;
}

/**
 * matrix_multiply
 * ----------------
 * Standard matrix multiplication C = A * B.
 */
Matrix *matrix_multiply(const Matrix *A, const Matrix *B) {
    // If either pointer is NULL, we cannot multiply.
    if (!A || !B) {
        return NULL;
    }

    // Dimensions must satisfy A->cols == B->rows.
    if (A->cols != B->rows) {
        return NULL;
    }

    // Allocate result matrix C with shape (A->rows x B->cols).
    Matrix *C = matrix_create(A->rows, B->cols);
    if (!C) {
        return NULL;
    }

    // Triple loop:
    //   for each row i of A
    //     for each column j of B
    //       C[i,j] = sum over k of (A[i,k] * B[k,j])
    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < B->cols; ++j) {
            double sum = 0.0;  // accumulator for the dot product
            for (size_t k = 0; k < A->cols; ++k) {
                double a = matrix_get(A, i, k);
                double b = matrix_get(B, k, j);
                sum += a * b;
            }
            matrix_set(C, i, j, sum);
        }
    }

    return C;
}

/**
 * matrix_print
 * ------------
 * Print a label and the contents of m to stdout.
 */
void matrix_print(const char *label, const Matrix *m) {
    // Optional label before the matrix.
    if (label) {
        printf("%s (%zux%zu):\n", label, m->rows, m->cols);
    }

    // Print each row on its own line.
    for (size_t i = 0; i < m->rows; ++i) {
        for (size_t j = 0; j < m->cols; ++j) {
            // Print each value with fixed width/precision for alignment.
            printf("%8.4f ", matrix_get(m, i, j));
        }
        printf("\n");
    }
    printf("\n");
}