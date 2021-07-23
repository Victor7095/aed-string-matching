

#include <stdio.h>
#include <string.h>
#define ASIZE 100000
#define XSIZE 100000

typedef struct patternScanOrder {
  int loc;
  char c;
} pattern;

int freq[ASIZE];

// Constrói a tabela de troca de bad character
void preQsBc(char *x, int m, int qsBc[]) {
  int i;

  for (i = 0; i < ASIZE; ++i) qsBc[i] = m + 1;
  for (i = 0; i < m; ++i) qsBc[x[i]] = m - i;
}

/* Constrói um pattern ordenado a partir de uma string. */
void orderPattern(char *x, int m, int (*pcmp)(), pattern *pat) {
  int i;

  for (i = 0; i <= m; ++i) {
    pat[i].loc = i;
    pat[i].c = x[i];
  }
  qsort(pat, m, sizeof(pattern), pcmp);
}

/* função de comparação de patterns do Optimal Mismatch. */
int optimalPcmp(pattern *pat1, pattern *pat2) {
  float fx;

  fx = freq[pat1->c] - freq[pat2->c];
  return (fx ? (fx > 0 ? 1 : -1) : (pat2->loc - pat1->loc));
}

/* Encontrar o próximo deslocamento para a esquerda
   para os primeiros elementos do padrão ploc após
   uma troca atual(shift) ou lshift */
int matchShift(char *x, int m, int ploc, int lshift, pattern *pat) {
  int i, j;

  for (; lshift < m; ++lshift) {
    i = ploc;
    while (--i >= 0) {
      if ((j = (pat[i].loc - lshift)) < 0) continue;
      if (pat[i].c != x[j]) break;
    }
    if (i < 0) break;
  }
  return (lshift);
}

/* Constrói a tabela de troca de bons sufixos
   a partir de uma string ordenada. */
void preAdaptedGs(char *x, int m, int adaptedGs[], pattern *pat) {
  int lshift, i, ploc;

  adaptedGs[0] = lshift = 1;
  for (ploc = 1; ploc <= m; ++ploc) {
    lshift = matchShift(x, m, ploc, lshift, pat);
    adaptedGs[ploc] = lshift;
  }
  for (ploc = 0; ploc <= m; ++ploc) {
    lshift = adaptedGs[ploc];
    while (lshift < m) {
      i = pat[ploc].loc - lshift;
      if (i < 0 || pat[ploc].c != x[i]) break;
      ++lshift;
      lshift = matchShift(x, m, ploc, lshift, pat);
    }
    adaptedGs[ploc] = lshift;
  }
}

/* Algortimo de correspondência de strings Optimal Mismatch. */
void OM(char *x, int m, char *y, int n) {
  int i, j, adaptedGs[XSIZE], qsBc[ASIZE];
  pattern pat[XSIZE];
  /* Preprocessing */
  orderPattern(x, m, optimalPcmp, pat);
  preQsBc(x, m, qsBc);
  preAdaptedGs(x, m, adaptedGs, pat);
  /* Searching */
  j = 0;
  while (j <= n - m) {
    i = 0;
    while (i < m && pat[i].c == y[j + pat[i].loc]) ++i;
    if (i >= m) printf("%d\n", j);
    int max = adaptedGs[i] > qsBc[y[j + m]] ? adaptedGs[i] : qsBc[y[j + m]];
    j += max;
  }
}

int main() {
  char *source = "GCATCGCAGAGAGTATACAGTACG";
  char *pattern = "GCAGAGAG";
  OM(pattern, 8, source, 24);
  return 0;
}