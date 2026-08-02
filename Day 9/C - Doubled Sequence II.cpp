// <3
// Tema: Constructive Algorithms / Secuencias de Langford
// Resuelve "Doubled Sequence II": para un n dado, construir una secuencia de
// longitud 2n donde cada valor de 1 a n aparece exactamente dos veces y, para
// cada i, la distancia entre sus dos ocurrencias es exactamente i+1 (esto es
// una variante de las secuencias de Langford/Skolem). Solo existe solucion
// cuando n % 4 es 0 o 3; en otro caso imprime -1. Cuando existe, usa la
// construccion explicita de Davies (1959) (funciones build4m y
// build4mMinus1) que arma la secuencia por bloques crecientes/decrecientes de
// paridad fija (appendRange) segun n sea 4m o 4m-1, con casos base para
// n=3 y n=4.

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

string out;

inline void appendInt(int v) {
    char tmp[12];
    int len = 0;
    if (v == 0) { tmp[len++] = '0'; }
    else {
        int x = v;
        while (x > 0) { tmp[len++] = char('0' + x % 10); x /= 10; }
    }
    for (int i = len - 1; i >= 0; i--) out += tmp[i];
    out += ' ';
}

// Appends consecutive even/odd terms from a to b inclusive (a,b same parity),
// increasing if a<=b, decreasing if a>b.
inline void appendRange(int a, int b) {
    if (a <= b) {
        for (int v = a; v <= b; v += 2) appendInt(v);
    } else {
        for (int v = a; v >= b; v -= 2) appendInt(v);
    }
}

// Davies (1959) construction for n = 4m, m >= 2.
void build4m(int m) {
    appendRange(4*m-4, 2*m);
    appendInt(4*m-2);
    appendRange(2*m-3, 1);
    appendInt(4*m-1);
    appendRange(1, 2*m-3);
    appendRange(2*m, 4*m-4);
    appendInt(4*m);
    appendRange(4*m-3, 2*m+1);
    appendInt(4*m-2);
    appendRange(2*m-2, 2);
    appendInt(2*m-1);
    appendInt(4*m-1);
    appendRange(2, 2*m-2);
    appendRange(2*m+1, 4*m-3);
    appendInt(2*m-1);
    appendInt(4*m);
}

// Davies (1959) construction for n = 4m-1, m >= 2.
void build4mMinus1(int m) {
    appendRange(4*m-4, 2*m);
    appendInt(4*m-2);
    appendRange(2*m-3, 1);
    appendInt(4*m-1);
    appendRange(1, 2*m-3);
    appendRange(2*m, 4*m-4);
    appendInt(2*m-1);
    appendRange(4*m-3, 2*m+1);
    appendInt(4*m-2);
    appendRange(2*m-2, 2);
    appendInt(2*m-1);
    appendInt(4*m-1);
    appendRange(2, 2*m-2);
    appendRange(2*m+1, 4*m-3);
}

int main() {
    int t = readInt();
    out.reserve(1 << 22);
    while (t--) {
        int n = readInt();
        int r = n % 4;
        if (r != 0 && r != 3) {
            out += "-1\n";
            continue;
        }
        if (n == 3) {
            out += "2 3 1 2 1 3\n";
        } else if (n == 4) {
            out += "2 3 4 2 1 3 1 4\n";
        } else if (r == 0) {
            build4m(n / 4);
            out.back() = '\n';
        } else { // r == 3, n = 4m-1 with m = (n+1)/4
            build4mMinus1((n + 1) / 4);
            out.back() = '\n';
        }
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}