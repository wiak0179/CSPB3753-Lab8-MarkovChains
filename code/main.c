///////////////////////////////////////////////////////////////////////////////
// CSPB 3753 — Lab 8: Markov Chains
// Demo program for Lab 8: tests matrix multiplication and Markov chain powers.
//
// Author: Cole Akers
// Date: November 5, 2025.
//
// Overview:
//   - demo_basic_multiply:
//       * Builds two small matrices A (2x3) and B (3x2).
//       * Computes C = A * B and prints all three.
//   - demo_markov:
//       * Builds a simple 2-state Markov transition matrix M.
//       * Checks whether M is a valid Markov chain.
//       * Computes M^2 and M^3 and prints them.
//   - main:
//       * Runs both demos to illustrate how matrix multiplication underlies
//         Markov chain behavior and multi-step transition probabilities.
//
// Formatting:
//   - Braces on same line, 4-space indent, no tabs.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>    // printf, fprintf
#include "matrix.h"   // Matrix and matrix_* functions
#include "markov.h"   // Markov helpers

/**
 * demo_basic_multiply
 * -------------------
 * Construct example matrices A and B, multiply them, and print the result.
 *
 * This corresponds directly to the "Matrix Multiplication" section of the lab.
 */
static void demo_basic_multiply(void) {
    // Create A (2 x 3) and B (3 x 2).
    Matrix *A = matrix_create(2, 3);
    Matrix *B = matrix_create(3, 2);

    // If either allocation fails, print an error and clean up.
    if (!A || !B) {
        fprintf(stderr, "Failed to allocate matrices A or B\n");
        matrix_free(A);
        matrix_free(B);
        return;
    }

    // Fill A with:
    // [1 2 3]
    // [4 5 6]
    double a_vals[2][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            matrix_set(A, i, j, a_vals[i][j]);
        }
    }

    // Fill B with:
    // [ 7  8]
    // [ 9 10]
    // [11 12]
    double b_vals[3][2] = {
        {7.0,  8.0},
        {9.0, 10.0},
        {11.0, 12.0}
    };

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            matrix_set(B, i, j, b_vals[i][j]);
        }
    }

    // Print A and B to show their contents.
    matrix_print("A", A);
    matrix_print("B", B);

    // Compute C = A * B.
    Matrix *C = matrix_multiply(A, B);
    if (!C) {
        fprintf(stderr, "Failed to multiply A and B\n");
        matrix_free(A);
        matrix_free(B);
        return;
    }

    // Print the result matrix C.
    matrix_print("C = A * B", C);

    // Free all allocated matrices for this demo.
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
}

/**
 * demo_markov
 * -----------
 * Build a small Markov chain matrix M, check its validity, and print M^2 and M^3.
 *
 * This corresponds to the "Markov Chains" and "Walks and Matrix Multiplication"
 * parts of the lab.
 */
static void demo_markov(void) {
    // Create a 2x2 matrix M.
    Matrix *M = matrix_create(2, 2);
    if (!M) {
        fprintf(stderr, "Failed to allocate Markov matrix M\n");
        return;
    }

    // Example transition probabilities:
    //
    // State 0 -> stays in 0 with probability 0.9, goes to 1 with probability 0.1
    // State 1 -> goes to 0 with probability 0.5, stays in 1 with probability 0.5
    //
    // So M =
    // [0.9 0.1]
    // [0.5 0.5]
    matrix_set(M, 0, 0, 0.9);
    matrix_set(M, 0, 1, 0.1);
    matrix_set(M, 1, 0, 0.5);
    matrix_set(M, 1, 1, 0.5);

    // Print the Markov transition matrix M.
    matrix_print("Markov chain M", M);

    // Check whether M is a valid Markov chain within a small numeric tolerance.
    double eps = 1e-9;
    int is_markov = markov_is_chain(M, eps);
    printf("Is M a Markov chain (eps = %.1e)? %s\n\n", eps,
           is_markov ? "yes" : "no");

    // Compute M^2 and M^3 using markov_power.
    Matrix *M2 = markov_power(M, 2);
    Matrix *M3 = markov_power(M, 3);

    if (!M2 || !M3) {
        fprintf(stderr, "Failed to compute powers of M\n");
        matrix_free(M);
        matrix_free(M2);
        matrix_free(M3);
        return;
    }

    // Print M^2 and M^3 to illustrate multi-step transition probabilities.
    matrix_print("M^2", M2);
    matrix_print("M^3", M3);

    // Free all matrices used in this demo.
    matrix_free(M);
    matrix_free(M2);
    matrix_free(M3);
}

/**
 * main
 * ----
 * Entry point for the Lab 8 demo program.
 *
 * Returns: 0 on success, non-zero on failure.
 */
int main(void) {
    printf("=== Lab 8: Matrix Multiplication Demo ===\n\n");
    demo_basic_multiply();

    printf("=== Lab 8: Markov Chain Demo ===\n\n");
    demo_markov();

    return 0;
}