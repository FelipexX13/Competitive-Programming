// <3
// Tema: CSES / Segment Tree con Nodo Compuesto
// Resumen: Segment tree donde cada nodo guarda DOS cosas: la suma del rango y el mejor prefijo
// del rango
// O: (log n) por operacion; el Node guarda suma y mejor prefijo
// Uso: SegmentTree st(a); st.update(1,1,n,pos,v); st.query(1,1,n,l,r)
// Detalle: Segment tree donde cada nodo guarda DOS cosas: la suma del rango y el mejor prefijo
// del rango. Es el ejemplo mas chico de la tecnica que hace al segment tree util de verdad: si
// la respuesta sola no se puede combinar, se guarda tambien lo que haga falta para poder
// combinarla. EL MERGE ES TODO: el mejor prefijo de la union es o el mejor prefijo de la
// izquierda, o toda la izquierda mas el mejor prefijo de la derecha. max(a.pref, a.sum +
// b.pref). Sin llevar la suma no habria forma de escribir esa segunda opcion, y por eso van
// juntas. COMO SE DISENA UN NODO ASI: se escribe a mano como seria la respuesta de la union en
// funcion de las dos mitades, y cada cosa que aparece en esa formula y no se tiene, se agrega
// al nodo. Se repite hasta que cierre. Es un proceso mecanico, no hay que adivinar. CUANDO
// USAR: la pregunta del rango no es una operacion asociativa simple pero SI se puede componer
// con un poco mas de informacion. Maximo prefijo, maximo subarreglo, cantidad de parentesis sin
// cerrar, la subsecuencia creciente mas larga por bloques.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll sum, pref;
};

Node merge(Node a, Node b) {
    return {
        a.sum + b.sum,
        max(a.pref, a.sum + b.pref)
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
            tree[node] = {a[l], max(0LL, a[l])};
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, ll value) {
        if (l == r) {
            tree[node] = {value, max(0LL, value)};
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, value);
        else
            update(node * 2 + 1, mid + 1, r, pos, value);

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

        return merge(
            query(node * 2, l, mid, ql, qr),
            query(node * 2 + 1, mid + 1, r, ql, qr)
        );
    }

    void update(int pos, ll value) {
        update(1, 1, n, pos, value);
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
        int type, a, b;
        cin >> type >> a >> b;

        if (type == 1) {
            st.update(a, b);
        } else {
            cout << st.query(a, b).pref << '\n';
        }
    }
}
