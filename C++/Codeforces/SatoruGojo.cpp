// <3
// Tema: Math / Optimization
// Resumen: Dado S y M, halla el costo minimo de escoger k enteros positivos cuyo producto sea
// al menos S
// Detalle: Problema estilo Codeforces: dado S y M, halla el costo minimo de escoger k enteros
// positivos cuyo producto sea al menos S, donde usar mas de un factor (k>1) cuesta M por cada
// factor extra ((k-1)*M). Para cada k candidato calcula la suma minima de k factores con
// producto >= S usando la raiz k-esima entera de S (los factores optimos son r y r+1, ya que
// por AM-GM la suma se minimiza haciendolos lo mas parejos posible) y prueba todos los k de 1 a
// 62 para quedarse con el mejor total.

#include <bits/stdc++.h>
using namespace std;

long long S;

// Multiply acc by base, but cap at S+1 (i.e. "definitely enough") to avoid overflow;
// once acc exceeds S we no longer care about the exact value, only that it's >= S.
inline long long capMul(long long acc, long long base) {
    if (acc > S) return acc; // already known to be enough
    // check for overflow before multiplying: if acc * base would exceed a safe bound, cap
    if (base != 0 && acc > (S + 5) / base + 1) {
        return S + 5; // definitely exceeds S, safe sentinel
    }
    long long r = acc * base;
    if (r > S) r = S + 5; // cap
    return r;
}

// largest r (>=1) such that r^k <= S
long long integerKthRoot(int k) {
    long long lo = 1, hi = S;
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        long long val = 1;
        bool exceeds = false;
        for (int i = 0; i < k; i++) {
            val = capMul(val, mid);
            if (val > S) { exceeds = true; break; }
        }
        if (!exceeds) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// minimal sum of k positive integers with product >= S
long long minSumForK(int k) {
    long long r = integerKthRoot(k);
    // try j = 0..k bumps from r to r+1, find smallest j with r^(k-j)*(r+1)^j >= S
    for (int j = 0; j <= k; j++) {
        long long val = 1;
        for (int t = 0; t < k - j; t++) {
            val = capMul(val, r);
        }
        for (int t = 0; t < j; t++) {
            val = capMul(val, r + 1);
        }
        if (val >= S) {
            return (long long)k * r + j;
        }
    }
    // fallback (shouldn't happen): all r+1
    return (long long)k * (r + 1);
}

int main() {
    long long M;
    cin >> S >> M;

    long long best = LLONG_MAX;
    // k up to ~62 is more than enough: 2^62 far exceeds 1e12, and the natural optimum
    // (ignoring M) is around ln(S) <= ~28 for S<=1e12; checking generously up to 62
    // safely covers the region where increasing k could still help when M is small.
    int maxK = 62;
    for (int k = 1; k <= maxK; k++) {
        long long sum = minSumForK(k);
        long long total = sum + (long long)(k - 1) * M;
        if (total < best) best = total;
    }

    cout << best << "\n";
    return 0;
}