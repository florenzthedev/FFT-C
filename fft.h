// Copyright (c) 2023 Zachary Todd Edwards
// MIT License

#ifndef DFT_H_INCLUDED
#define DFT_H_INCLUDED

#include <complex.h>
#include <stdbool.h>

/**
 * @brief Performs the Fourier transform. This interface is intended to be used
 * with dynamic loading. This function handles putting the input into
 * bit-reversal-permutation order.
 *
 * @param X Input dataset, will be overwritten by results.
 * @param N Size of input dataset, must be a power of two.
 * @param aux Auxillary information, if less than 0 the inverse Fourier
 * transform will be performed instead.
 *
 * @return  0 on success, 1 on failure (usually a malloc failure).
 */
int fourier_transform(double complex* X, long N, int aux);

/**
 * @brief Reorders the input dataset into bit-reversal-permutation for use with
 * the FFT.
 *
 * @param x Input dataset.
 * @param N Size of input dataset.
 */
void bit_reversal_permutation(double complex* x, long N);

/**
 * @brief Generates the lookup table for first nontrivial roots of unity for
 * each stage.
 *
 * @param N Size of dataset that will be operated on, must be a power of two.
 * @param inverse If true the table will be generated for performing the inverse
 * FFT.
 * @return double* A dynamically allocated array of values, needs to be free'd.
 */
double complex* gen_omegas(long N, bool inverse);

/**
 * @brief The fast Fourier transform. Input is expected to be in
 * bit-reversal-permutation order.
 *
 * @param omegas Lookup table for first nontrivial roots of unity for each
 * butterfly stage.
 * @param X Input dataset, will be overwritten by results.
 * @param N Size of input dataset, must be a power of two.
 */
void fft(double complex* omegas, double complex* X, long N);

#endif