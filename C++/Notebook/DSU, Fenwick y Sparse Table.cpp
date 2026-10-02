// <3
// Tema: Data Structures / DSU, Fenwick y Sparse Table
// Resumen: Las tres estructuras de todos los dias, genericas y listas para pegar
// O: DSU casi (1); Fenwick (log n); Sparse Table (n log n) armar, (1) consultar
// Uso: TODO 0-indexado: DSU d(n); d.unir(a,b); Fenwick f(n); f.add(i,v); f.sum(l,r)
// Detalle: DSU con compresion de camino y union por tamano; unir devuelve false si ya
// estaban juntos (asi se detecta un ciclo, o se arma Kruskal: ordenar aristas por peso y
// quedarse con las que unen). d.sz[d.find(x)] es el tamano del grupo de x.
// Fenwick: la interfaz es 0-indexada y por dentro corre 1-indexada, para no caer en la
// trampa de i & -i con i = 0 (no avanza nunca). sum(i) es a[0..i]; sum(l,r) es a[l..r].
// lowerBound(k): menor i con a[0..i] >= k, valido si todos los a son >= 0 (sirve para
// "el k-esimo elemento" guardando conteos). Rango-suma con actualizacion por rango: dos
// Fenwick, o el segment tree con lazy.
// contarInversiones: pares i < j con a[i] > a[j], comprimiendo valores. Salio dos veces:
// SkyLine (Maraton 2024) y cruces de cuerdas en Lonely Creatures (Regional 2025).
// Sparse Table: minimo de cualquier rango [l,r] en O(1) cuando el arreglo NO cambia.
// Sirve para min, max y gcd (operaciones donde repetir un elemento no altera); para suma
// no: ahi van prefijos.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct DSU
{
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unir(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

struct Fenwick
{
    int n;
    vector<ll> t;
    Fenwick(int n) : n(n), t(n + 1, 0) {}
    void add(int i, ll v)
    {
        for (i++; i <= n; i += i & -i) t[i] += v;
    }
    ll sum(int i)                             // a[0..i]
    {
        ll s = 0;
        for (i++; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    ll sum(int l, int r) { return l > r ? 0 : sum(r) - (l ? sum(l - 1) : 0); }
    int lowerBound(ll k)                      // menor i con a[0..i] >= k; n si no hay
    {
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)  // cubre n hasta 6*10^7
        {
            if (pos + pw <= n && t[pos + pw] < k)
            {
                pos += pw;
                k -= t[pos];
            }
        }
        return pos;
    }
};

ll contarInversiones(const vector<ll> &a)
{
    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    Fenwick f(v.size());
    ll inv = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--)
    {
        int c = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
        inv += f.sum(c - 1);                  // menores a la derecha
        f.add(c, 1);
    }
    return inv;
}

struct SparseMin
{
    vector<vector<ll>> t;
    SparseMin(const vector<ll> &a)
    {
        int n = a.size(), K = 1;
        while ((1 << K) <= n) K++;
        t.assign(K, a);
        for (int k = 1; k < K; k++)
        {
            for (int i = 0; i + (1 << k) <= n; i++)
            {
                t[k][i] = min(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    ll query(int l, int r)                    // minimo de a[l..r]
    {
        int k = __lg(r - l + 1);
        return min(t[k][l], t[k][r - (1 << k) + 1]);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
