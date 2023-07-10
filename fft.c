// Copyright (c) 2023 Zachary Todd Edwards
// MIT License

#include "fft.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int fourier_transform(double complex* X, long N, int aux) {
  assert((N & (N - 1)) == 0);  // Must be a power of two
  bit_reversal_permutation(X, N);
  double complex* omegas = gen_omegas(N, ((aux < 0) ? true : false));
  if (omegas == NULL) return 1;
  fft(omegas, X, N);
  if (aux < 0)
    for (int j = 0; j < N; j++) X[j] /= N;
  free(omegas);
  return 0;
}

unsigned int bit_length(unsigned long x) {
  unsigned int bits = 0;
  while (x) {
    bits++;
    x >>= 1;
  }
  return bits;
}

unsigned long bit_reverse(unsigned long x, unsigned int n) {
  unsigned long r = 0;
  for (unsigned int i = 0; i < n; ++i) {
    if (x & (1 << i)) r |= 1 << ((n - 1) - i);
  }
  return r;
}

void bit_reversal_permutation(double complex* x, long N) {
  // Don't forget bit_length is one indexed!
  int bl = bit_length(N) - 1;

  // We can skip the first and last index, they never need to be moved
  for (long i = 1; i < N - 1; i++) {
    long ri = bit_reverse(i, bl);
    if (i < ri) {
      double complex temp = x[i];
      x[i] = x[ri];
      x[ri] = temp;
    }
  }
}

double complex* gen_omegas(long N, bool inverse) {
  int Nth = (bit_length(N) - 1);  // Log2(N)
  double complex* omegas = malloc(sizeof(double complex) * Nth);
  if (omegas == NULL) return NULL;
  omegas[0] = CMPLX(-1, 0);
  omegas[1] = CMPLX(0, -1);
  for (int j = 2; j < Nth; j++) omegas[j] = csqrt(omegas[j - 1]);
  if (inverse)
    for (int j = 1; j < Nth; j++) omegas[j] = conj(omegas[j]);
  return omegas;
}

void fft(double complex omegas[], double complex X[], long N) {
  assert((N & (N - 1)) == 0);  // Must be a power of two
  for (long n = 2; n <= N; n *= 2) {
    double complex omega = omegas[bit_length(n) - 2];
    double complex root_of_unity = 1;
    for (long j = 0; j < n / 2; j++) {
      for (long k = 0; k < N; k += n) {
        double complex product = root_of_unity * X[k + j + n / 2];
        X[k + j + n / 2] = X[k + j] - product;
        X[k + j] = X[k + j] + product;
      }
      root_of_unity *= omega;
    }
  }
}