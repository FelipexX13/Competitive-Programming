// <3
// Tema: Combinatorics / Euler's Formula
// Resuelve "Pizza Cutter": el abuelo Giuseppe corta una pizza rectangular con H cortes que
// entran por el lado izquierdo y salen por el derecho, y V cortes que entran por abajo y
// salen por arriba (cada corte es una curva continua, sin tres cortes concurrentes ni cortes
// tangentes); dado donde entra y sale cada corte, hay que contar en cuantas piezas queda
// dividida la pizza. Usa la formula de Euler para arreglos de curvas en el plano (piezas = 1 +
// #cortes + #cruces): cada par de cortes de tipos opuestos siempre se cruza una vez (aporta
// H*V cruces), y los cruces entre cortes del mismo tipo se cuentan como inversiones (hh, vv)
// del orden de sus extremos derecho/superior via countInversions (merge sort), sumando todo
// en "answer".

#include <bits/stdc++.h>
using namespace std;

static char buf_[1 << 22];
static int bufLen_, bufPos_;
inline int gc() {
    if (bufPos_ == bufLen_) { bufLen_ = fread(buf_, 1, sizeof(buf_), stdin); bufPos_ = 0; if (!bufLen_) return -1; }
    return buf_[bufPos_++];
}
inline long long readLL() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    bool neg = false; if (c == '-') { neg = true; c = gc(); }
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

// Counts inversions in `a` (pairs i<j with a[i] > a[j]) via merge sort. O(n log n).
long long countInversions(vector<long long>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0;
    vector<long long> buf(n);
    long long inv = 0;
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int mid = min(i + width, n);
            int end = min(i + 2 * width, n);
            int p = i, q = mid, k = i;
            while (p < mid && q < end) {
                if (a[p] <= a[q]) buf[k++] = a[p++];
                else { buf[k++] = a[q++]; inv += (mid - p); }
            }
            while (p < mid) buf[k++] = a[p++];
            while (q < end) buf[k++] = a[q++];
            for (int t = i; t < end; t++) a[t] = buf[t];
        }
    }
    return inv;
}

int main() {
    // X, Y (pizza dimensions) are read for input-format purposes only; the piece
    // count depends solely on H, V, and the relative order of cut endpoints.
    (void)readLL(); (void)readLL();
    long long H = readLL(), V = readLL();

    vector<pair<long long,long long>> hcuts(H), vcuts(V);
    for (auto& p : hcuts) { p.first = readLL(); p.second = readLL(); }
    for (auto& p : vcuts) { p.first = readLL(); p.second = readLL(); }

    sort(hcuts.begin(), hcuts.end());
    vector<long long> y2seq;
    y2seq.reserve(H);
    for (auto& p : hcuts) y2seq.push_back(p.second);
    long long hh = countInversions(y2seq);

    sort(vcuts.begin(), vcuts.end());
    vector<long long> x2seq;
    x2seq.reserve(V);
    for (auto& p : vcuts) x2seq.push_back(p.second);
    long long vv = countInversions(x2seq);

    long long answer = 1 + H + V + hh + vv + H * V;
    printf("%lld\n", answer);
    return 0;
}