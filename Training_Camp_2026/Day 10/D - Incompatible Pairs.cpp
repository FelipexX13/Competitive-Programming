// <3
// Tema: Greedy / Prefijos sobre Secuencias Balanceadas
// Resuelve "Incompatible Pairs": una secuencia de N bailarines Yang ('(') y Yin (')')
// donde cada Yang debe emparejarse con un Yin posterior; un par (i, j) es incompatible
// si al formarlo los bailarines restantes ya no pueden emparejarse todos entre si (rompe
// el balance tipo parentesis). Usa el balance de prefijos prefix[k] (+1 por '(', -1 por
// ')'); para cada Yang en la posicion i, f[i] es la primera posicion k>=i donde el balance
// vuelve a 0 (fin del segmento balanceado que arranca en i): cualquier Yin ubicado despues
// de f[i] forma un par incompatible con ese Yang, porque deja un '(' suelto sin '(' extra
// donde absorberlo. Suma, para cada '(' en la posicion i, la cantidad de ')' que hay
// despues de f[i] (precomputada en suffixClose) para obtener el total de pares incompatibles.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
inline void readString(string &s, int expectedLen) {
    s.clear();
    s.reserve(expectedLen);
    int c = gc();
    while (c != '(' && c != ')') c = gc();
    while (c == '(' || c == ')') {
        s.push_back((char)c);
        c = gc();
    }
}

int main() {
    int N = readInt();
    string s;
    readString(s, N);
    // in case the read stopped early due to buffering edge cases, N is authoritative
    // for sizing arrays; s.size() should equal N given well-formed input.

    vector<int> prefix(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        prefix[i] = prefix[i - 1] + (s[i - 1] == '(' ? 1 : -1);
    }

    // f[i] = smallest k >= i with prefix[k] == 0, for i = 1..N (computed right to left).
    vector<int> f(N + 2, 0);
    f[N] = (prefix[N] == 0) ? N : N + 1;
    for (int i = N - 1; i >= 1; i--) {
        f[i] = (prefix[i] == 0) ? i : f[i + 1];
    }

    // suffixClose[k] = number of ')' at 1-indexed positions > k, for k = 0..N.
    vector<ll> suffixClose(N + 2, 0);
    for (int k = N - 1; k >= 0; k--) {
        suffixClose[k] = suffixClose[k + 1] + (s[k] == ')' ? 1 : 0);
    }

    ll total = 0;
    for (int i = 1; i <= N; i++) {
        if (s[i - 1] == '(') {
            total += suffixClose[f[i]];
        }
    }

    printf("%lld\n", total);
    return 0;
}