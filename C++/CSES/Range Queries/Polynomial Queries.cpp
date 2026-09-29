// <3
// Tema: CSES / Lazy Propagation de Progresiones Aritmeticas
// Lazy propagation donde la actualizacion no suma una constante sino 1, 2, 3, ... a lo largo del
// rango. La clave es que una progresion aritmetica se describe con DOS numeros, el primer termino
// A y la diferencia D, y que dos progresiones se SUMAN componente a componente. Por eso el lazy
// es el par (A, D), y componer dos actualizaciones pendientes es sumar los pares.
// Al empujar a los hijos, el izquierdo recibe (A, D) tal cual, pero el derecho arranca mas
// adelante en la progresion: recibe (A + lenLeft*D, D). Ese corrimiento es lo unico nuevo respecto
// a un lazy de suma normal.
// La suma de la progresion sobre un nodo de largo len es len*(2A + (len-1)*D)/2, y la division es
// exacta siempre: si len es par, listo; si es impar, (len-1)*D es par.
// EL PATRON GENERAL: se puede hacer lazy de cualquier actualizacion que (1) se describa con pocos
// numeros, (2) se pueda componer con otra del mismo tipo, y (3) permita recalcular la suma del
// nodo sin bajar a las hojas. Las progresiones cumplen las tres; por eso sirve.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 200005;

ll st[4 * N];
ll lazyA[4 * N];
ll lazyD[4 * N];

void build(int p, int l, int r, vector<ll>& a) {
    if (l == r) {
        st[p] = a[l];
        return;
    }

    int m = (l + r) / 2;

    build(p * 2, l, m, a);
    build(p * 2 + 1, m + 1, r, a);

    st[p] = st[p * 2] + st[p * 2 + 1];
}

void apply(int p, int l, int r, ll A, ll D) {
    ll len = r - l + 1;

    st[p] += len * (2 * A + (len - 1) * D) / 2;

    lazyA[p] += A;
    lazyD[p] += D;
}

void push(int p, int l, int r) {
    if (lazyA[p] == 0 && lazyD[p] == 0)
        return;

    int m = (l + r) / 2;
    int lenLeft = m - l + 1;

    apply(p * 2, l, m, lazyA[p], lazyD[p]);

    apply(
        p * 2 + 1,
        m + 1,
        r,
        lazyA[p] + lenLeft * lazyD[p],
        lazyD[p]
    );

    lazyA[p] = 0;
    lazyD[p] = 0;
}

void update(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql)
        return;

    if (ql <= l && r <= qr) {
        ll A = l - ql + 1;
        apply(p, l, r, A, 1);
        return;
    }

    push(p, l, r);

    int m = (l + r) / 2;

    update(p * 2, l, m, ql, qr);
    update(p * 2 + 1, m + 1, r, ql, qr);

    st[p] = st[p * 2] + st[p * 2 + 1];
}

ll query(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql)
        return 0;

    if (ql <= l && r <= qr)
        return st[p];

    push(p, l, r);

    int m = (l + r) / 2;

    return query(p * 2, l, m, ql, qr)
         + query(p * 2 + 1, m + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    build(1, 1, n, a);

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1)
            update(1, 1, n, l, r);
        else
            cout << query(1, 1, n, l, r) << '\n';
    }
}
