// <3
// Tema: CSES / Segment Tree de Maximo Subarreglo
// Resumen: El nodo compuesto clasico, con cuatro campos
// O: (log n) por operacion
// Uso: Node = {sum, pref, suff, best}; merge cruza suff izq con pref der
// Detalle: El nodo compuesto clasico, con cuatro campos: sum, pref (mejor prefijo), suff (mejor
// sufijo) y best (el mejor subarreglo de adentro). Es Kadane metido en un segment tree, y por
// eso aguanta actualizaciones que Kadane suelto no aguanta. EL MERGE, que es lo unico que hay
// que entender: sum = L.sum + R.sum pref = max(L.pref, L.sum + R.pref) el prefijo se queda o
// cruza suff = max(R.suff, R.sum + L.suff) el sufijo, simetrico best = max(L.best, R.best,
// L.suff + R.pref) o esta en una mitad, o CRUZA el corte Ese tercer caso del best es la razon
// de llevar suff y pref: el subarreglo que cruza es el mejor sufijo de la izquierda pegado al
// mejor prefijo de la derecha. El max(0, a[l]) en las hojas permite el subarreglo VACIO, o sea
// que la respuesta nunca es negativa. Si el problema exige al menos un elemento hay que sacar
// ese max y poner la hoja en a[l] pelado. CUANDO USAR: maximo subarreglo con actualizaciones.
// Sin actualizaciones basta Kadane en O(n).

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll sum, pref, suff, best;
};

Node merge(Node L, Node R) {
    Node res;

    res.sum = L.sum + R.sum;

    res.pref = max(L.pref, L.sum + R.pref);

    res.suff = max(R.suff, R.sum + L.suff);

    res.best = max({
        L.best,
        R.best,
        L.suff + R.pref
    });

    return res;
}

struct SegmentTree {
    int n;
    vector<Node> tree;

    SegmentTree(vector<ll>& a) {
        n = a.size() - 1;
        tree.resize(4 * n);
        build(1, 1, n, a);
    }

    void build(int node, int l, int r, vector<ll>& a) {
        if (l == r) {
            tree[node] = {
                a[l],
                max(0LL, a[l]),
                max(0LL, a[l]),
                max(0LL, a[l])
            };
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, ll value) {
        if (l == r) {
            tree[node] = {
                value,
                max(0LL, value),
                max(0LL, value),
                max(0LL, value)
            };
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, value);
        else
            update(node * 2 + 1, mid + 1, r, pos, value);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int pos, ll value) {
        update(1, 1, n, pos, value);
    }

    ll answer() {
        return tree[1].best;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    SegmentTree st(a);

    while (m--) {
        int k;
        ll x;

        cin >> k >> x;

        st.update(k, x);

        cout << st.answer() << '\n';
    }
}
