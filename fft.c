// Copyright (c) 2023 Zachary Todd Edwards
// MIT License

#include "fft.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int fourier_transform(double complex* X, long N) {
  bit_reversal_permutation(X, N);
  fft(X, N);
  return 0;
}

unsigned int bit_length(unsigned int x) {
  unsigned int bits = 0;
  while (x) {
    bits++;
    x >>= 1;
  }
  return bits;
}

unsigned int bit_reverse(unsigned int x, unsigned int n) {
  unsigned int r = 0;
  for (unsigned int i = 0; i < n; ++i) {
    if (x & (1 << i)) r |= 1 << ((n - 1) - i);
  }
  return r;
}

void bit_reversal_permutation(double complex* x, int N) {
  // Don't forget bit_length is one indexed!
  int bl = bit_length(N) - 1;

  // We can skip the first and last index, they never need to be moved
  for (int i = 1; i < N - 1; i++) {
    int ri = bit_reverse(i, bl);
    if (i < ri) {
      double complex temp = x[i];
      x[i] = x[ri];
      x[ri] = temp;
    }
  }
}

void fft(double complex* X, int N) {
  assert((N & (N - 1)) == 0);  // Must be a power of two
  double complex omega = CMPLX(-1, 0);
  for (int n = 2; n <= N; n *= 2) {
    double complex root_of_unity = omega;
    for (int j = 0; j < n / 2; j++) {
      for (int k = 0; k < N; k += n) {
        double complex product = root_of_unity * X[k + j + n / 2];
        X[k + j + n / 2] = X[k + j] - product;
        X[k + j] = X[k + j] + product;
      }
      root_of_unity *= omega;
    }
    omega = csqrt(omega);
  }
}