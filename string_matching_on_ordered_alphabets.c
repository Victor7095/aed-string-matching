#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/* Função que calcula o próximo sufixo máximo */
void nextMaximalSuffix(char *x, int m,
                       int *i, int *j, int *k, int *p) {
    char a, b;
 
    while (*j + *k < m) {
        a = x[*i + *k];
        b = x[*j + *k];
        if (a == b)
            if (*k == *p) {
                (*j) += *p;
                *k = 1;
            }
        else
            ++(*k);
        else if (a > b) {
            (*j) += *k;
            *k = 1;
            *p = *j - *i;
        }
         else {
            *i = *j;
            ++(*j);
            *k = *p = 1;
         }
   }
}
 
 
/* String matching on ordered alphabets algorithm. */
void SMOA(char *x, int m, char *y, int n) {
   int i, ip, j, jp, k, p;
 
   /* Searching */
   ip = -1;
   i = j = jp = 0;
   k = p = 1;

   while (j <= n - m) {
      while (i + j < n && i < m && x[i] == y[i + j]) ++i;

      if (i == 0) {
         ++j;
         ip = -1;
         jp = 0;
         k = p = 1;
      }
      else {
         if (i >= m) printf("%d\n", j);

         nextMaximalSuffix(y + j, i+1, &ip, &jp, &k, &p);

         if (ip < 0 || (ip < p && memcmp(y + j, y + j + p, ip + 1) == 0)) {
            j += p;
            i -= p;

            if (i < 0) i = 0;

            if (jp - ip > p) jp -= p;
            else {
               ip = -1;
               jp = 0;
               k = p = 1;
            }
         }
         else {
            j += (MAX(ip + 1, MIN(i - ip - 1, jp + 1)) + 1);
            i = jp = 0;
            ip = -1;
            k = p = 1;
         }
      }
   }
}

int main() {
    SMOA("GCAGAGAG", 8, "GCATCGCAGAGAGTATACAGTACG", 24);
    return 0;
}
