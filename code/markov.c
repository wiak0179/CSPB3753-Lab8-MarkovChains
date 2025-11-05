///////////////////////////////////////////////////////////////////////////////
// CSPB 3753 — Lab 8: Markov Chains
// Implementation of Markov chain helpers built on top of Matrix operations.
//
// Author: Cole Akers
// Date: November 5 2025
//
// Overview:
//   - markov_is_chain: verify that a matrix is row-stochastic (rows sum to 1)
//     and non-negative, within a numeric tolerance.
//   - markov_power: compute M^k using exponentiation by squaring. The (i, j)
//     entry of M^k gives the probability of transitioning from state i to
//     state j in exactly k steps for a Markov chain.
//
// Formatting:
//   - Braces on same line, 4-space indent, no tabs.
//
///////////////////////////////////////////////////////////////////////////////

#include "markov.h"

#include <math.h>    // fabs
#include <stdlib.h>  // NULL

/**
 * matrix_copy
 * -----------
 * Helper: deep-copy a matrix so we can safely modify the copy.
 *
 * src: matrix to copy.
 *
 * Returns:
 *   Newly allocated copy of src, or NULL on failure.
 */
static Matrix *matrix_copy(const Matrix *src) {
    // Allocate a new matrix with the same dimensions.
    Matrix *dst = matrix_create(src->rows, src->cols);
    if (!dst) {
        return NULL;
    }

    // Copy each element from src to dst.
    for (size_t i = 0; i < src->rows; ++i) {
        for (size_t j = 0; j < src->cols; ++j) {
            double value = matrix_get(src, i, j);
            matrix_set(dst, i, j, value);
        }
    }

    return dst;
}

/**
 * markov_is_chain
 * ---------------
 * Return 1 if M is a valid Markov chain (within eps), 0 otherwise.
 */
int markov_is_chain(const Matrix *M, double eps) {
    if (!M) {
        return 0;
    }

    // Check each row of M.
    for (size_t i = 0; i < M->rows; ++i) {
        double row_sum = 0.0;  // accumulate the sum of row i

        for (size_t j = 0; j < M->cols; ++j) {
            double val = matrix_get(M, i, j);

            // Allow a tiny negative value due to rounding (e.g., -1e-12),
            // but reject anything beyond -eps.
            if (val < -eps) {
                return 0;
            }

            row_sum += val;
        }

        // Require row_sum to be within eps of 1.0.
        if (fabs(row_sum - 1.0) > eps) {
            return 0;
        }
    }

    return 1;
}

/**
 * markov_power
 * ------------
 * Compute M^k via exponentiation by squaring.
 *
 * Idea:
 *   - Maintain "result" as the running product (starts as identity).
 *   - Maintain "base" as the current power of M.
 *   - While k > 0:
 *       * If k is odd, multiply result by base.
 *       * Square base (base = base * base).
 *       * Halve k (shift right).
 *
 * This runs in O(log k) matrix multiplications instead of O(k).
 */
Matrix *markov_power(const Matrix *M, unsigned int k) {
    // Guard against NULL or exponent 0.
    if (!M || k == 0) {
        return NULL;
    }

    // Markov chains are square matrices; enforce that here.
    if (M->rows != M->cols) {
        return NULL;
    }

    // Create an identity matrix for "result".
    Matrix *result = matrix_create(M->rows, M->cols);
    if (!result) {
        return NULL;
    }

    // Initialize result as the identity matrix I.
    for (size_t i = 0; i < M->rows; ++i) {
        for (size_t j = 0; j < M->cols; ++j) {
            double value = (i == j) ? 1.0 : 0.0;
            matrix_set(result, i, j, value);
        }
    }

    // Make a mutable copy of M to use as our "base" matrix.
    Matrix *base = matrix_copy(M);
    if (!base) {
        matrix_free(result);
        return NULL;
    }

    // Work with a local copy of k so we can shift it.
    unsigned int exp = k;

    // Core exponentiation-by-squaring loop.
    while (exp > 0) {
        // If the current bit of exp is 1, multiply result by base.
        if (exp & 1U) {
            Matrix *tmp = matrix_multiply(result, base);
            if (!tmp) {
                matrix_free(result);
                matrix_free(base);
                return NULL;
            }

            // Replace result with the new product.
            matrix_free(result);
            result = tmp;
        }

        // Shift exponent right by one bit (divide by 2).
        exp >>= 1U;

        // If there are still bits left, square the base (base = base * base).
        if (exp > 0) {
            Matrix *tmp = matrix_multiply(base, base);
            if (!tmp) {
                matrix_free(result);
                matrix_free(base);
                return NULL;
            }

            matrix_free(base);
            base = tmp;
        }
    }

    // We no longer need base.
    matrix_free(base);

    // result now holds M^k.
    return result;
}
