// <3
// Tema: CSES / Fenwick de Diferencias
// O: (log n) por operacion
// Uso: add(l,+x) y add(r+1,-x); sum(i) da el valor de la posicion i
// La vuelta de tuerca: en vez de guardar los valores, el Fenwick guarda las DIFERENCIAS. Sumar x
// a todo el rango [a,b] son dos operaciones puntuales, add(a, x) y add(b+1, -x), y consultar la
// posicion k es la suma de prefijo hasta k. O sea que el mismo Fenwick que hace
// "actualizacion puntual + consulta de rango" tambien hace lo contrario,
// "actualizacion de rango + consulta puntual", solo cambiando lo que se guarda.
// CUANDO USAR: el problema actualiza rangos completos y pregunta por posiciones sueltas. Si
// necesita actualizar rangos Y consultar rangos, ahi si toca el Fenwick doble o un segment tree
// con lazy propagation.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Fenwick {
    int n;
    vector<ll> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, ll x) {
        for (; i <= n; i += i & -i)
            bit[i] += x;
    }

    ll sum(int i) {
        ll res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
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

    Fenwick fw(n + 1);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int a, b;
            ll c;
            cin >> a >> b >> c;

            fw.add(a, c);
            fw.add(b + 1, -c);
        } else {
            int k;
            cin >> k;

            cout << arr[k] + fw.sum(k) << '\n';
        }
    }
}
