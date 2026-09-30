// <3
// Tema: Dynamic Programming / Interval Scheduling
// Resuelve "Yuyuan Market": una fila de 2N jianzhi con simbolos repetidos (cada simbolo
// aparece dos veces), donde solo se pueden comprar pares (posicion i, posicion j>i) del
// mismo simbolo, sin cruzar hacia atras una vez elegido un par. Hay que maximizar la
// cantidad de pares comprados y, entre los que logran el maximo, minimizar la suma de
// distancias j-i. Cada simbolo define un intervalo [L[v], R[v]] (primera y segunda
// aparicion); es DP de intervalos sobre la posicion p: cnt[p]/len[p] guardan el mejor
// (cantidad, costo) usando las primeras p posiciones, y endAtL[p] permite extender el
// DP tomando el intervalo que termina en p desde el estado anterior a su inicio.

#include <bits/stdc++.h>
using namespace std;

static char buf_[1 << 22];
static int bufLen_, bufPos_;
inline int gc() {
    if (bufPos_ == bufLen_) { bufLen_ = fread(buf_, 1, sizeof(buf_), stdin); bufPos_ = 0; if (!bufLen_) return -1; }
    return buf_[bufPos_++];
}
inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    bool neg = false; if (c == '-') { neg = true; c = gc(); }
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

int main() {
    int N = readInt();
    int M = 2 * N;
    vector<int> L(N + 1, 0), R(N + 1, 0);
    vector<bool> seen(N + 1, false);
    for (int pos = 1; pos <= M; pos++) {
        int v = readInt();
        if (!seen[v]) { L[v] = pos; seen[v] = true; }
        else R[v] = pos;
    }

    vector<int> endAtL(M + 1, -1); // endAtL[p] = L of the symbol whose R equals p, or -1
    for (int v = 1; v <= N; v++) endAtL[R[v]] = L[v];

    vector<int> cnt(M + 1, 0);
    vector<long long> len(M + 1, 0);
    for (int p = 1; p <= M; p++) {
        cnt[p] = cnt[p - 1];
        len[p] = len[p - 1];
        if (endAtL[p] != -1) {
            int Lv = endAtL[p];
            int candCnt = cnt[Lv - 1] + 1;
            long long candLen = len[Lv - 1] + (long long)(p - Lv);
            if (candCnt > cnt[p] || (candCnt == cnt[p] && candLen < len[p])) {
                cnt[p] = candCnt;
                len[p] = candLen;
            }
        }
    }

    printf("%d %lld\n", cnt[M], len[M]);
    return 0;
}