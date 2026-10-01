// <3
// Tema: CSES / Segment Tree (Minimo)
// Resumen: Segment tree de minimos con actualizacion puntual, en O(log n) cada operacion
// O: (log n) update y query, (n) build
// Uso: st.build(1,1,n,a); st.update(1,1,n,pos,v); st.query(1,1,n,l,r)
// Detalle: Segment tree de minimos con actualizacion puntual, en O(log n) cada operacion. El
// nodo p cubre [l,r] y sus hijos son 2p y 2p+1; por eso el arreglo se reserva de tamano 4n, que
// es la cota segura para cualquier n (no solo potencias de 2). CUANDO USAR SEGMENT TREE Y NO
// OTRA COSA: la operacion es asociativa pero NO tiene inversa (min, max, gcd), asi que restar
// no es opcion y Fenwick queda descartado, y ADEMAS el arreglo cambia, lo que descarta la
// sparse table. Ese cruce es exactamente el nicho del segment tree. Es la plantilla de la que
// salen todas las variantes: cambiando el min por otra operacion asociativa sirve igual, y
// agregandole lazy se actualizan rangos completos.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<ll> tree;

    SegmentTree(int n) : n(n), tree(4 * n) {}

    void build(int node, int l, int r, vector<ll>& arr) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, arr);
        build(node * 2 + 1, mid + 1, r, arr);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, ll val) {
        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, val);
        else
            update(node * 2 + 1, mid + 1, r, pos, val);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;
        ll ans = LLONG_MAX;

        if (ql <= mid)
            ans = min(ans, query(node * 2, l, mid, ql, qr));

        if (qr > mid)
            ans = min(ans, query(node * 2 + 1, mid + 1, r, ql, qr));

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> arr(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    SegmentTree st(n);

    st.build(1, 1, n, arr);

    while (q--) {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        if (a == 1) {
            st.update(1, 1, n, b, c);
        } else {
            cout << st.query(1, 1, n, b, c) << '\n';
        }
    }
}
