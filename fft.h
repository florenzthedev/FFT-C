// Copyright (c) 2023 Zachary Todd Edwards
// MIT License

#ifndef DFT_H_INCLUDED
#define DFT_H_INCLUDED

#include <complex.h>

/**
 * @brief Performs the Fourier transform. This interface is intended to be used
 * with dynamic loading. This function handles putting the input into
 * bit-reversal-permutation order.
 *
 * @param X Input dataset, will be overwritten by results.
 * @param N Size of input dataset, must be a power of two.
 * @param aux Auxillary information, unused in this implementation.
 *
 * @return  0 on success, this implementation will never reasonably fail.
 */
int fourier_transform(double complex* X, long N, int aux);

/**
 * @brief Reorders the input dataset into bit-reversal-permutation for use with
 * the FFT.
 *
 * @param x Input dataset.
 * @param N Size of input dataset.
 */
void bit_reversal_permutation(double complex* x, int N);

/**
 * @brief The fast Fourier transform. Input is expected to be in
 * bit-reversal-permutation order.
 *
 * @param X Input dataset, will be overwritten by results.
 * @param N Size of input dataset, must be a power of two.
 */
void fft(double complex* X, int N);

#endif