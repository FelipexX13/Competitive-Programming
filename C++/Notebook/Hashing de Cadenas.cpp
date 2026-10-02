// <3
// Tema: String / Hashing de Cadenas (mod 2^61-1)
// Resumen: Comparar dos subcadenas en O(1) tras O(n) de preproceso, y LCP por binaria
// O: (n) construir, (1) cada get, (log n) cada lcp
// Uso: Hash H(s); H.get(l,r) es [l,r) 0-indexado; iguales si los get coinciden
// Detalle: Hash polinomial de prefijos: h[i] = s[0]*B^(i-1) + ... + s[i-1]. La subcadena
// [l,r) sale restando h[l] corrido: h[r] - h[l]*B^(r-l). Con eso cualquier par de subcadenas
// se compara en O(1), y el LCP de dos posiciones sale por binaria sobre el largo.
// Por que UN solo modulo 2^61-1 y no hashing doble: la probabilidad de choque por par es
// del orden de n/2^61, menor que la de dos modulos de 10^9 juntos, y es una sola cuenta.
// La multiplicacion pasa por __int128 y se reduce con dos sumas, sin el % lento.
// La BASE es global y aleatoria A PROPOSITO: (1) si cada Hash tuviera su propia base, los
// hashes de dos cadenas distintas no se podrian comparar entre si; (2) una base fija se
// puede atacar con un caso anti-hash (pasa en Codeforces con hacks, no en ICPC, pero no
// cuesta nada). Palindromos: armar otro Hash con la cadena invertida; s[l,r) es
// palindromo si H.get(l,r) == R.get(n-r, n-l).
// Ojo: get(l,r) depende SOLO del contenido y del largo, asi que sirve para comparar
// subcadenas de cadenas DISTINTAS (siempre que sea la misma BASE, que lo es).

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const ull MOD = (1ULL << 61) - 1;

ull mulmod(ull a, ull b)
{
    __uint128_t c = (__uint128_t)a * b;
    ull r = (ull)(c & MOD) + (ull)(c >> 61);
    return r >= MOD ? r - MOD : r;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const ull BASE = rng() % (MOD - 1000) + 500;   // la MISMA para todas las cadenas

struct Hash
{
    vector<ull> h, p;

    Hash(const string &s) : h(s.size() + 1, 0), p(s.size() + 1, 1)
    {
        for (int i = 0; i < (int)s.size(); i++)
        {
            h[i + 1] = (mulmod(h[i], BASE) + (unsigned char)s[i]) % MOD;
            p[i + 1] = mulmod(p[i], BASE);
        }
    }

    // hash de s[l, r), 0-indexado, r exclusivo
    ull get(int l, int r)
    {
        return (h[r] + MOD - mulmod(h[l], p[r - l])) % MOD;
    }
};

// Largo del prefijo comun mas largo de A[i..] y B[j..]
int lcp(Hash &A, int i, Hash &B, int j)
{
    int lo = 0, hi = min((int)A.h.size() - 1 - i, (int)B.h.size() - 1 - j);
    while (lo < hi)
    {
        int m = (lo + hi + 1) / 2;
        if (A.get(i, i + m) == B.get(j, j + m)) lo = m;
        else hi = m - 1;
    }
    return lo;
}

// Compara s[i..i+len) contra t[j..j+len) en orden alfabetico: -1, 0 o 1
int comparar(Hash &A, const string &s, int i, Hash &B, const string &t, int j, int len)
{
    int k = min(lcp(A, i, B, j), len);
    if (k == len) return 0;
    return s[i + k] < t[j + k] ? -1 : 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
