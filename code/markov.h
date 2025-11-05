///////////////////////////////////////////////////////////////////////////////
// CSPB 3753 — Lab 8: Markov Chains
// Interface for Markov-chain-related helpers built on top of the Matrix type.
//
// Author: Cole Akers
// Date: November 5, 2025.
//
// Overview:
//   - markov_is_chain: check if a matrix satisfies the Markov chain properties:
//       * all entries non-negative
//       * each row sums to ~1 within a given epsilon
//   - markov_power: compute M^k for a square matrix M using exponentiation
//     by squaring (efficient repeated multiplication).
//
// Formatting:
//   - Braces on same line, 4-space indent, no tabs.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MARKOV_H
#define MARKOV_H

#include "matrix.h"  // reuse the Matrix type and operations

/**
 * markov_is_chain
 * ---------------
 * Check whether the given matrix M is (approximately) a Markov chain:
 *   - All entries are >= 0 (within a small negative epsilon to allow rounding).
 *   - Each row sums to 1.0 within a tolerance eps.
 *
 * M:   matrix to test (interpreted as transition probabilities).
 * eps: allowed numeric tolerance for row sums and negative entries.
 *
 * Returns: 1 if M satisfies the Markov chain conditions, 0 otherwise.
 */
int markov_is_chain(const Matrix *M, double eps);

/**
 * markov_power
 * ------------
 * Compute the k-th power of M, i.e., M^k, using exponentiation by squaring.
 *
 * M:   square matrix to exponentiate (n x n).
 * k:   positive integer exponent (k >= 1). If k == 0, returns NULL.
 *
 * Requires: M is non-NULL and square (rows == cols).
 *
 * Returns: newly allocated matrix representing M^k, or NULL on error.
 */
Matrix *markov_power(const Matrix *M, unsigned int k);

#endif // MARKOV_H