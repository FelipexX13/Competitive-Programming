// <3
// Tema: Bitmask DP / SOS (Sum over Subsets) + Inclusion-Exclusion
// Resuelve "How many teams?" (Maratona SBC de Programacao 2025, Problem H): N estudiantes
// tienen cada uno un subconjunto de K habilidades (representado como bitmask), un equipo de 3
// estudiantes tiene como conjunto de habilidades la union de las de sus miembros, y se dan M
// subconjuntos especiales; para cada uno hay que contar cuantos equipos de 3 estudiantes
// distintos tienen union de habilidades exactamente igual a ese subconjunto. El codigo cuenta
// primero f[mask] = cantidad de estudiantes con esa mascara exacta, aplica SOS (sum over
// subsets) para que f[mask] pase a contar estudiantes cuya mascara es submascara de mask, calcula
// h[mask] = C(f[mask], 3) (tripletas cuya union esta contenida en mask), y luego aplica Mobius /
// inclusion-exclusion (SOS inverso) sobre h[] para recuperar el conteo exacto por union, de modo
// que cada consulta se responde en O(1).

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
// Reads a binary string of known length K, skipping any non-'0'/'1' characters first,
// and returns the mask with position 1 (first character) as bit 0 (matches problem's
// convention, verified against both worked examples).
inline int readMaskFixedLen(int K) {
    int c = gc();
    while (c != '0' && c != '1') c = gc();
    int mask = 0;
    for (int pos = 0; pos < K; pos++) {
        if (c == '1') mask |= (1 << pos);
        if (pos + 1 < K) c = gc();
    }
    return mask;
}

int main() {
    int N = readInt(), K = readInt();
    int full = 1 << K;
    vector<long long> f(full, 0); // will hold cnt[] then get turned into SOS sums

    for (int i = 0; i < N; i++) {
        int mask = readMaskFixedLen(K);
        f[mask]++;
    }

    // SOS: f[mask] = number of students whose mask is a submask of `mask`
    for (int bit = 0; bit < K; bit++) {
        int b = 1 << bit;
        for (int mask = 0; mask < full; mask++) {
            if (mask & b) f[mask] += f[mask ^ b];
        }
    }

    // g[mask] = C(f[mask], 3)
    vector<long long> h(full, 0);
    for (int mask = 0; mask < full; mask++) {
        long long v = f[mask];
        h[mask] = (v >= 3) ? (v * (v - 1) * (v - 2) / 6) : 0;
    }

    // Mobius inversion (inclusion-exclusion) to get exact-union counts
    for (int bit = 0; bit < K; bit++) {
        int b = 1 << bit;
        for (int mask = 0; mask < full; mask++) {
            if (mask & b) h[mask] -= h[mask ^ b];
        }
    }

    int M = readInt();
    string out;
    out.reserve((size_t)M * 8);
    char tmp[32];
    for (int q = 0; q < M; q++) {
        int mask = readMaskFixedLen(K);
        int len = sprintf(tmp, "%lld\n", h[mask]);
        out.append(tmp, len);
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}