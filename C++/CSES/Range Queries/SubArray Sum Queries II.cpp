// <3
// Tema: CSES / Maximo Subarreglo en un Rango
// Resumen: El MISMO nodo de cuatro campos que "SubArray Sum Queries", con el merge identico
// O: (log n) por operacion
// Uso: mismo Node de la I; aqui el merge se usa tambien en la consulta
// Detalle: El MISMO nodo de cuatro campos que "SubArray Sum Queries", con el merge identico,
// pero respondiendo otra pregunta: alla se actualiza una posicion y se pide el mejor subarreglo
// de TODO el arreglo (se lee la raiz), y aqui no hay actualizaciones y se pide el mejor
// subarreglo DENTRO de un rango [a,b] (se combinan los nodos que cubren el rango). POR ESO VALE
// LA PENA TENER LOS DOS JUNTOS: es la misma estructura sirviendo para dos problemas distintos,
// y lo unico que cambia es de donde se lee la respuesta. Si el merge esta bien escrito, que la
// consulta sea global o de rango no le importa a la estructura. La leccion practica: cuando se
// disena un nodo compuesto, conviene escribir la consulta de rango aunque el problema solo pida
// la raiz. Cuesta cinco lineas mas y cubre las dos variantes.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll sum, pref, suff, best;
};

Node merge(Node L, Node R) {
    return {
        L.sum + R.sum,
        max(L.pref, L.sum + R.pref),
        max(R.suff, R.sum + L.suff),
        max({
            L.best,
            R.best,
            L.suff + R.pref
        })
    };
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

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(node * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(node * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    Node query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    SegmentTree st(a);

    while (q--) {
        int a, b;
        cin >> a >> b;

        cout << st.query(a, b).best << '\n';
    }
}
