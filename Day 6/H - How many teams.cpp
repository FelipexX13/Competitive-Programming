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