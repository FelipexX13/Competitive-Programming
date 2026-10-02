// <3
// Tema: Data Structures / Segment Tree con Lazy (Sumar a un Rango)
// Resumen: Sumar v a todo a[l..r] y preguntar suma o minimo de a[l..r], ambos en O(log n)
// O: (n) armar, (log n) cada operacion
// Uso: SegTree st(a); st.add(l,r,v); st.suma(l,r); st.minimo(l,r); todo 0-indexado, [l,r]
// Detalle: Cada nodo guarda la suma y el minimo de su tramo, mas un "pendiente" (lz) que
// todavia no bajo a los hijos. Sumar v a un tramo completo es O(1): suma += v * largo,
// minimo += v, lz += v. Solo cuando una operacion tiene que entrar a los hijos se baja el
// pendiente (push). Asi cada operacion toca O(log n) nodos.
// Para otra operacion se cambian tres cosas: lo que guarda el nodo, como se combinan dos
// hijos (pull) y como se aplica el pendiente (aplicar). Ejemplos:
//   asignar en rango (a[l..r] = v): lz guarda el valor y una bandera "hay pendiente";
//     aplicar hace suma = v * largo, minimo = v. Ojo: v = 0 tambien es pendiente.
//   maximo en vez de minimo: cambiar min por max en pull y el neutro LLONG_MAX por LLONG_MIN.
// Si NO hay actualizaciones por rango, alcanza con Fenwick (suma) o Sparse Table (min).

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree
{
    int n;
    vector<ll> sm, mn, lz;

    SegTree(const vector<ll> &a) : n(a.size()), sm(4 * n), mn(4 * n), lz(4 * n, 0)
    {
        build(1, 0, n - 1, a);
    }

    void pull(int p)
    {
        sm[p] = sm[2 * p] + sm[2 * p + 1];
        mn[p] = min(mn[2 * p], mn[2 * p + 1]);
    }

    void aplicar(int p, int l, int r, ll v)
    {
        sm[p] += v * (r - l + 1);
        mn[p] += v;
        lz[p] += v;
    }

    void push(int p, int l, int r)
    {
        if (lz[p] == 0) return;
        int m = (l + r) / 2;
        aplicar(2 * p, l, m, lz[p]);
        aplicar(2 * p + 1, m + 1, r, lz[p]);
        lz[p] = 0;
    }

    void build(int p, int l, int r, const vector<ll> &a)
    {
        if (l == r)
        {
            sm[p] = mn[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, a);
        build(2 * p + 1, m + 1, r, a);
        pull(p);
    }

    void add(int p, int l, int r, int i, int j, ll v)
    {
        if (j < l || r < i) return;
        if (i <= l && r <= j)
        {
            aplicar(p, l, r, v);
            return;
        }
        push(p, l, r);
        int m = (l + r) / 2;
        add(2 * p, l, m, i, j, v);
        add(2 * p + 1, m + 1, r, i, j, v);
        pull(p);
    }

    // devuelve {suma, minimo} de a[i..j]
    pair<ll, ll> query(int p, int l, int r, int i, int j)
    {
        if (j < l || r < i) return {0, LLONG_MAX};
        if (i <= l && r <= j) return {sm[p], mn[p]};
        push(p, l, r);
        int m = (l + r) / 2;
        auto a = query(2 * p, l, m, i, j), b = query(2 * p + 1, m + 1, r, i, j);
        return {a.first + b.first, min(a.second, b.second)};
    }

    void add(int l, int r, ll v) { add(1, 0, n - 1, l, r, v); }
    ll suma(int l, int r) { return query(1, 0, n - 1, l, r).first; }
    ll minimo(int l, int r) { return query(1, 0, n - 1, l, r).second; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
