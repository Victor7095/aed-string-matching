#include <stdio.h>
#include <string.h>

/* Cálculo do sufixo máximo para <= */
int maxSuf(char *x, int m, int *p) {
  int ms, j, k;
  char a, b;

  ms = -1;
  j = 0;
  k = *p = 1;
  while (j + k < m) {
    a = x[j + k];
    b = x[ms + k];
    if (a < b) {
      j += k;
      k = 1;
      *p = j - ms;
    } else if (a == b)
      if (k != *p)
        ++k;
      else {
        j += *p;
        k = 1;
      }
    else { /* a > b */
      ms = j;
      j = ms + 1;
      k = *p = 1;
    }
  }
  return (ms);
}

/* Cálculo do sufixo máximo para >= */
int maxSufTilde(char *x, int m, int *p) {
  int ms, j, k;
  char a, b;

  ms = -1;
  j = 0;
  k = *p = 1;
  while (j + k < m) {
    a = x[j + k];
    b = x[ms + k];
    if (a > b) {
      j += k;
      k = 1;
      *p = j - ms;
    } else if (a == b)
      if (k != *p)
        ++k;
      else {
        j += *p;
        k = 1;
      }
    else { /* a < b */
      ms = j;
      j = ms + 1;
      k = *p = 1;
    }
  }
  return (ms);
}

/* Algoritmo de correspondência de strings Two Way. */
void TW(char *x, int m, char *y, int n) {
  int i, j, ell, memory, p, per, q;

  /* Pré-processamento */
  i = maxSuf(x, m, &p);
  j = maxSufTilde(x, m, &q);
  if (i > j) {
    ell = i;
    per = p;
  } else {
    ell = j;
    per = q;
  }

  /* Buscando */
  if (memcmp(x, x + per, ell + 1) == 0) {
    j = 0;
    memory = -1;
    while (j <= n - m) {
      int max = ell > memory ? ell : memory;
      i = max + 1;
      while (i < m && x[i] == y[i + j]) ++i;
      if (i >= m) {
        i = ell;
        while (i > memory && x[i] == y[i + j]) --i;
        if (i <= memory) printf("%d\n", j);
        j += per;
        memory = m - per - 1;
      } else {
        j += (i - ell);
        memory = -1;
      }
    }
  } else {
    int max = ell + 1 > m - ell - 1 ? ell + 1 : m - ell - 1;
    per = max + 1;
    j = 0;
    while (j <= n - m) {
      i = ell + 1;
      while (i < m && x[i] == y[i + j]) ++i;
      if (i >= m) {
        i = ell;
        while (i >= 0 && x[i] == y[i + j]) --i;
        if (i < 0) printf("%d\n", j);
        j += per;
      } else
        j += (i - ell);
    }
  }
}

int main() {
  char *source = "GCATCGCAGAGAGTATACAGTACG";
  char *pattern = "GCAGAGAG";
  TW(pattern, 8, source, 24);
  return 0;
}