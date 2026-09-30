// <3
// Tema: CSES / Segment Tree Persistente
// O: (log n) por operacion, (n log n) de memoria
// Uso: raiz[k]=update(raiz[j],1,n,pos,x); query(raiz[k],1,n,l,r)  // persistente
// Segment tree PERSISTENTE: cada actualizacion no modifica nodos, crea copias nuevas SOLO del
// camino de la raiz a la hoja, O(log n) nodos, y todo lo demas se comparte con la version
// anterior. Asi cada version tiene su propia raiz y se puede consultar cualquiera.
// LO QUE HACE ESTE PROBLEMA ELEGANTE: copiar un arreglo entero (la operacion 3) cuesta O(1).
// Basta copiar el PUNTERO a la raiz, porque las dos versiones comparten todos los nodos hasta que
// alguna se modifique, y en ese momento la modificacion crea caminos nuevos sin tocar la otra.
// Los nodos no pueden ir en el esquema 2p / 2p+1 de siempre, porque un nodo tiene varios padres
// segun la version. Por eso cada nodo guarda los INDICES de sus hijos (l, r) y se sacan de un
// arreglo grande con un contador.
// EL TAMANO DEL POOL: el build usa 2n nodos y cada actualizacion unos log2(n)+1 = 19. Con 2*10^5
// actualizaciones son ~4.2 millones, y el arreglo reserva 25 por posicion (5 millones). Quedarse
// corto aqui da un error silencioso al pisar memoria. Ocupa unos 80 MB.
// CUANDO USAR: "consultar el arreglo como estaba en el momento k", versiones, o la k-esima
// estadistica en un rango (el clasico con persistencia sobre prefijos).

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    int l, r;
    ll sum;
};

const int MAXN = 200005;
const int MAXNODE = MAXN * 25;

Node st[MAXNODE];
int root[MAXN];
int nodes = 0;

int build(int l, int r, vector<ll>& a) {
    int p = ++nodes;

    if (l == r) {
        st[p].sum = a[l];
        return p;
    }

    int m = (l + r) / 2;

    st[p].l = build(l, m, a);
    st[p].r = build(m + 1, r, a);

    st[p].sum = st[st[p].l].sum + st[st[p].r].sum;

    return p;
}

int update(int old, int l, int r, int pos, ll x) {
    int p = ++nodes;
    st[p] = st[old];

    if (l == r) {
        st[p].sum = x;
        return p;
    }

    int m = (l + r) / 2;

    if (pos <= m)
        st[p].l = update(st[old].l, l, m, pos, x);
    else
        st[p].r = update(st[old].r, m + 1, r, pos, x);

    st[p].sum = st[st[p].l].sum + st[st[p].r].sum;

    return p;
}

ll query(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql)
        return 0;

    if (ql <= l && r <= qr)
        return st[p].sum;

    int m = (l + r) / 2;

    return query(st[p].l, l, m, ql, qr)
         + query(st[p].r, m + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    root[1] = build(1, n, a);

    int versions = 1;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int k, a, x;
            cin >> k >> a >> x;

            root[k] = update(root[k], 1, n, a, x);
        }
        else if (type == 2) {
            int k, a, b;
            cin >> k >> a >> b;

            cout << query(root[k], 1, n, a, b) << '\n';
        }
        else {
            int k;
            cin >> k;

            root[++versions] = root[k];
        }
    }
}

