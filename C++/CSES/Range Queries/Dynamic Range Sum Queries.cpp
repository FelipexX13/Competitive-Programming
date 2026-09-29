// <3
// Tema: CSES / Fenwick Tree (BIT)
// Fenwick (o BIT): sumas de prefijo con actualizacion puntual, ambas en O(log n), en ~10 lineas.
// Toda la magia esta en i & -i, que aisla el bit mas bajo encendido: sumando ese valor se sube a
// los padres (add) y restandolo se baja recorriendo bloques (sum).
// CUANDO USAR FENWICK EN VEZ DE SEGMENT TREE: si la operacion es SUMA (o cualquiera con inversa)
// y las actualizaciones son puntuales, Fenwick es la respuesta: menos codigo, menos memoria y
// mas rapido en la practica. El segment tree se necesita para min, max o gcd, que no se pueden
// restar, y para lazy propagation.
// Fenwick es 1-indexado a la fuerza: con i = 0, i & -i es 0 y el for no avanza nunca.

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

    ll query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> arr(n + 1);
    Fenwick fw(n);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        fw.add(i, arr[i]);
    }

    while (q--) {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        if (a == 1) {
            ll diff = c - arr[b];
            arr[b] = c;
            fw.add(b, diff);
        } else {
            cout << fw.query(b, c) << '\n';
        }
    }
}
