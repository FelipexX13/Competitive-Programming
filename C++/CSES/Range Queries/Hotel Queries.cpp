// <3
// Tema: CSES / Segment Tree con Descenso
// O: (log n) por consulta, con descenso por el arbol
// Uso: ST st; st.find(x) -> primer hotel con cupo >= x, 0 si no hay
// Segment tree de MAXIMOS, pero lo interesante no es la consulta sino el DESCENSO: para hallar el
// primer hotel con capacidad suficiente, en vez de buscar con una consulta y despues actualizar
// (dos O(log n) y una busqueda binaria por fuera), se baja una sola vez desde la raiz preguntando
// si el hijo izquierdo alcanza; si alcanza se va por ahi, si no por el derecho. Al llegar a la
// hoja se descuenta de una. Todo en un solo O(log n).
// CUANDO USAR EL DESCENSO: cada vez que el problema pida "el PRIMER indice que cumple algo" y el
// predicado se pueda decidir mirando el maximo (o el minimo, o la suma) de un nodo. Es el patron
// que reemplaza a "busqueda binaria + consulta", que seria O(log^2 n).

#include <bits/stdc++.h>
using namespace std;

struct ST {
    int n;
    vector<int> t;

    ST(vector<int>& a) {
        n = a.size() - 1;
        t.resize(4 * n);
        build(1, 1, n, a);
    }

    void build(int p, int l, int r, vector<int>& a) {
        if (l == r) {
            t[p] = a[l];
            return;
        }

        int m = (l + r) / 2;

        build(p * 2, l, m, a);
        build(p * 2 + 1, m + 1, r, a);

        t[p] = max(t[p * 2], t[p * 2 + 1]);
    }

    int find(int p, int l, int r, int x) {
        if (l == r) {
            t[p] -= x;
            return l;
        }

        int m = (l + r) / 2;
        int pos;

        if (t[p * 2] >= x)
            pos = find(p * 2, l, m, x);
        else
            pos = find(p * 2 + 1, m + 1, r, x);

        t[p] = max(t[p * 2], t[p * 2 + 1]);

        return pos;
    }

    int find(int x) {
        if (t[1] < x)
            return 0;

        return find(1, 1, n, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    ST st(a);

    while (m--) {
        int x;
        cin >> x;
        cout << st.find(x) << ' ';
    }
}
