// <3
// Tema: CSES / Truco de p[i] mas y menos i
// Resumen: Hay que minimizar p[j] + |i - j| sobre todo j, con actualizaciones
// O: (log n) por operacion, dos segment trees de minimo
// Uso: un arbol para a[i]+i y otro para a[i]-i; la respuesta es el menor
// Detalle: Hay que minimizar p[j] + |i - j| sobre todo j, con actualizaciones. El valor
// absoluto es lo que estorba, y el truco es partirlo en los dos casos y meter el indice DENTRO
// del valor guardado: si j <= i: p[j] + i - j = (p[j] - j) + i si j >= i: p[j] + j - i = (p[j]
// + j) - i Como i es fijo durante la consulta, minimizar cada caso es minimizar (p[j] - j) a la
// izquierda y (p[j] + j) a la derecha. O sea DOS segment trees de minimos, uno sobre p[j]-j y
// otro sobre p[j]+j, y la respuesta es el menor de los dos resultados sumandole o restandole i.
// CUANDO USAR ESTE TRUCO: cada vez que aparece un |i - j| junto a algo que depende de j. Sale
// en problemas de "la tienda mas cercana con su costo", en DP con costos de distancia, y en
// cualquier minimizacion sobre una recta. La regla es partir en j <= i y j >= i y absorber el
// indice en el valor que se guarda; lo que quedaba dependiendo de i sale del minimo como
// constante.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<ll> tree;

    SegmentTree(vector<ll>& a) {
        n = a.size() - 1;
        tree.resize(4 * n);
        build(1, 1, n, a);
    }

    void build(int node, int l, int r, vector<ll>& a) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, ll value) {
        if (l == r) {
            tree[node] = value;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, value);
        else
            update(node * 2 + 1, mid + 1, r, pos, value);

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

    void update(int pos, ll value) {
        update(1, 1, n, pos, value);
    }

    ll query(int l, int r) {
        if (l > r)
            return LLONG_MAX;

        return query(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> p(n + 1);
    vector<ll> a(n + 1), b(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> p[i];

        a[i] = p[i] - i;
        b[i] = p[i] + i;
    }

    SegmentTree leftTree(a);
    SegmentTree rightTree(b);

    while (q--) {
        int type, k;
        ll x;

        cin >> type >> k;

        if (type == 1) {
            cin >> x;

            p[k] = x;

            leftTree.update(k, x - k);
            rightTree.update(k, x + k);
        }
        else {
            ll left = leftTree.query(1, k) + k;
            ll right = rightTree.query(k, n) - k;

            cout << min(left, right) << '\n';
        }
    }
}
