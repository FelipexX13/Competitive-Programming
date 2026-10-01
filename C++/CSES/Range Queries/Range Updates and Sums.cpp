// <3
// Tema: CSES / Lazy Propagation con Suma y Asignacion
// Resumen: Lazy propagation con DOS tipos de actualizacion (sumar x al rango y ASIGNAR x al
// rango)
// Detalle: Lazy propagation con DOS tipos de actualizacion (sumar x al rango y ASIGNAR x al
// rango), y todo el problema es como se componen cuando se encuentran en un mismo nodo. Se
// mantiene el invariante "lo pendiente es: primero asignar lazySet (si hasSet), despues sumar
// lazyAdd": - Una ASIGNACION borra cualquier suma pendiente: applySet pone lazyAdd en 0. La
// asignacion pisa todo lo anterior. - Una SUMA sobre un nodo que ya tiene una asignacion
// pendiente no se guarda como suma: se le suma al valor asignado (lazySet += x). Asignar S y
// despues sumar x es asignar S + x. - Al empujar, se baja primero la asignacion y despues la
// suma, en ese orden. Equivocarse en cualquiera de las tres da respuestas que parecen bien en
// casos chicos y fallan cuando las dos operaciones se mezclan sobre el mismo rango. Se usa
// hasSet aparte en vez de un valor centinela porque asignar 0 es una operacion valida. EL
// PATRON GENERAL: con varios tipos de lazy, antes de programar se escribe la tabla de "si llega
// B encima de A, que queda". Si esa tabla cierra, el lazy funciona.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 200005;

ll st[4 * N];
ll lazyAdd[4 * N];
ll lazySet[4 * N];
bool hasSet[4 * N];

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

void applySet(int p, int l, int r, ll x) {
    st[p] = x * (r - l + 1);

    lazySet[p] = x;
    lazyAdd[p] = 0;
    hasSet[p] = true;
}

void applyAdd(int p, int l, int r, ll x) {
    st[p] += x * (r - l + 1);

    if (hasSet[p])
        lazySet[p] += x;
    else
        lazyAdd[p] += x;
}

void push(int p, int l, int r) {
    if (l == r)
        return;

    int m = (l + r) / 2;

    if (hasSet[p]) {
        applySet(p * 2, l, m, lazySet[p]);
        applySet(p * 2 + 1, m + 1, r, lazySet[p]);

        hasSet[p] = false;
    }

    if (lazyAdd[p] != 0) {
        applyAdd(p * 2, l, m, lazyAdd[p]);
        applyAdd(p * 2 + 1, m + 1, r, lazyAdd[p]);

        lazyAdd[p] = 0;
    }
}

void updateAdd(int p, int l, int r, int ql, int qr, ll x) {
    if (qr < l || r < ql)
        return;

    if (ql <= l && r <= qr) {
        applyAdd(p, l, r, x);
        return;
    }

    push(p, l, r);

    int m = (l + r) / 2;

    updateAdd(p * 2, l, m, ql, qr, x);
    updateAdd(p * 2 + 1, m + 1, r, ql, qr, x);

    st[p] = st[p * 2] + st[p * 2 + 1];
}

void updateSet(int p, int l, int r, int ql, int qr, ll x) {
    if (qr < l || r < ql)
        return;

    if (ql <= l && r <= qr) {
        applySet(p, l, r, x);
        return;
    }

    push(p, l, r);

    int m = (l + r) / 2;

    updateSet(p * 2, l, m, ql, qr, x);
    updateSet(p * 2 + 1, m + 1, r, ql, qr, x);

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

        if (type == 1) {
            ll x;
            cin >> x;
            updateAdd(1, 1, n, l, r, x);
        }
        else if (type == 2) {
            ll x;
            cin >> x;
            updateSet(1, 1, n, l, r, x);
        }
        else {
            cout << query(1, 1, n, l, r) << '\n';
        }
    }
}
