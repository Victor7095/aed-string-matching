#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *x, *y;
int k, m, n, p, p1, p2, q, q1, q2, s;

/* Função utilizada para pesquisar o texto por x = [ 0, s ], [ s, |X| ] */
void search() {
    while (p <= n - m) {
        while (p + s + q < n && x[s + q] == y[p + s + q]) ++q;

        if (q == m - s && memcmp(x, y + p, s + 1) == 0) printf("%d\n", p);

        if (q == p1 + q1) {
            p += p1;
            q -= p1;
        }
        else {
            p += (q/k + 1);
            q = 0;
        }
    }
}

/* Função utilizada para incrementar a variável global s */
void parse() {
    while (1) {
        while (x[s + q1] == x[s + p1 + q1]) ++q1;

        while (p1 + q1 >= k * p1) {
            s += p1;
            q1 -= p1;
        }

        p1 += (q1 / k + 1);
        q1 = 0;

        if (p1 >= p2) break;
    }

    newP1();
}

/* Função utilizada para encontrar o segundo período de prefixo mais curto de [ s, |x| ]. */
void newP2() {
    while (x[s + q2] == x[s + p2 + q2] && p2 + q2 < k * p2) ++q2;

    if (p2 + q2 == k * p2) parse();
    else if (s + p2 + q2 == m) search();
    else {
        if (q2 == p1 + q1) {
            p2 += p1;
            q2 -= p1;
        }

        else {
            p2 += (q2 / k + 1);
            q2 = 0;
        }

        newP2();
    }
}

/* Função utilizada para encontrar o período de prefixo mais curto de [ s, |x| ]. */
void newP1() {
    while(x[s + q1] == x[s + p1 + q1]) ++q1;

    if(p1 + q1 >= k * p1) {
        p2 = q1;
        q2 = 0;
        newP2();
    }
    else {
        if(s + p1 + q1 == m) search();
        else {
            p1 += (q1/k + 1);
            q1 = 0;
            newP1();
        }
    }
}

/* Método inicial com a inicialização das variáveis globais e chamada do método newP1 */
void GS(char *argX, int argM, char *argY, int argN) {
    x = argX;
    m = argM;
    y = argY;
    n = argN;
    k = 4;
    p = q = s = q1 = p2 = q2 = 0;
    p1 = 1;
    newP1();
}

int main() {
    GS("GCAGAGAG", 8, "GCATCGCAGAGAGTATACAGTACG", 24);
    return 0;
}
