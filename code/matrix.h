///////////////////////////////////////////////////////////////////////////////
// CSPB 3753 — Lab 8: Markov Chains
// Basic dense matrix interface and operations, including matrix multiplication.
//
// Author: Cole Akers
// Date: Fall 2025
//
// Overview:
//   - Defines a Matrix type stored in row-major order.
//   - Supports creation, destruction, element access, A * B multiplication,
//     and pretty-printing.
//
// Formatting:
//   - Braces on same line, 4-space indent, no tabs.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>  // for size_t

// Matrix
// -----
// Simple dense matrix stored in row-major order.
// data[i * cols + j] is the element at row i, column j.
typedef struct {
    size_t rows;   // number of rows
    size_t cols;   // number of columns
    double *data;  // pointer to rows * cols doubles
} Matrix;

/**
 * matrix_create
 * -------------
 * Allocate a rows x cols matrix on the heap and initialize all entries to 0.0.
 *
 * rows: number of rows in the matrix.
 * cols: number of columns in the matrix.
 *
 * Returns:
 *   Pointer to the new Matrix on success, or NULL on allocation failure.
 */
Matrix *matrix_create(size_t rows, size_t cols);

/**
 * matrix_free
 * -----------
 * Free a Matrix previously created with matrix_create.
 *
 * m: matrix to free; safe to pass NULL.
 *
 * Returns:
 *   Nothing.
 */
void matrix_free(Matrix *m);

/**
 * matrix_get
 * ----------
 * Read the value at position (i, j) from matrix m.
 * This function does NOT perform bounds checking; caller must ensure
 * 0 <= i < rows and 0 <= j < cols.
 *
 * m: matrix to read from (must not be NULL).
 * i: row index.
 * j: column index.
 *
 * Returns:
 *   Value stored at (i, j).
 */
double matrix_get(const Matrix *m, size_t i, size_t j);

/**
 * matrix_set
 * ----------
 * Write a value into position (i, j) of matrix m.
 * This function does NOT perform bounds checking; caller must ensure
 * valid indices.
 *
 * m: matrix to modify (must not be NULL).
 * i: row index.
 * j: column index.
 * value: number to store at (i, j).
 *
 * Returns:
 *   Nothing.
 */
void matrix_set(Matrix *m, size_t i, size_t j, double value);

/**
 * matrix_multiply
 * ----------------
 * Compute the standard matrix product C = A * B.
 *
 * A: left matrix, size (A->rows x A->cols).
 * B: right matrix, size (B->rows x B->cols).
 *
 * Requires:
 *   A->cols == B->rows. If dimensions are incompatible, returns NULL.
 *
 * Returns:
 *   Pointer to newly allocated Matrix C on success, or NULL on failure.
 */
Matrix *matrix_multiply(const Matrix *A, const Matrix *B);

/**
 * matrix_print
 * ------------
 * Print a matrix to stdout in a human-readable form.
 *
 * label: string printed before the matrix (may be NULL).
 * m: matrix to print.
 *
 * Returns:
 *   Nothing.
 */
void matrix_print(const char *label, const Matrix *m);

#endif // MATRIX_H
