// <3
// Tema: Game Theory / Nim con Segment Tree
// Resuelve "Juan vs Frank": Frank y Juan juegan duelos de Nim sobre un rango
// de columnas [l,r], donde cada columna es un monton de fragmentos y en cada
// turno se retiran fragmentos de una sola columna; pierde quien no puede
// mover. Por la teoria de Nim, el primer jugador (Frank) gana si y solo si
// el XOR de los valores del rango es distinto de cero. Mantiene un segment
// tree que guarda el XOR de rangos (arreglo seg) con soporte de update
// puntual (rituales que suman x a una columna) y query de rango (profecias),
// respondiendo "FRANK" si el XOR del rango es != 0 y "JUAN" si es 0.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<ll> a(N);

    int SZ = N;
    vector<ll> seg(2 * SZ);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
        seg[SZ + i] = a[i];
    }

    for (int i = SZ - 1; i > 0; i--)
        seg[i] = seg[i << 1] ^ seg[i << 1 | 1];

    auto update = [&](int pos, ll val) {
        pos--;
        a[pos] += val;
        int p = pos + SZ;
        seg[p] = a[pos];
        while (p >>= 1)
            seg[p] = seg[p << 1] ^ seg[p << 1 | 1];
    };

    auto query = [&](int l, int r) {
        ll ans = 0;
        l = l - 1 + SZ;
        r = r + SZ;
        while (l < r) {
            if (l & 1) ans ^= seg[l++];
            if (r & 1) ans ^= seg[--r];
            l >>= 1;
            r >>= 1;
        }
        return ans;
    };

    while (Q--) {
        char op;
        cin >> op;

        if (op == 'P') {
            int l, r;
            cin >> l >> r;
            if (query(l, r) == 0)
                cout << "JUAN\n";
            else
                cout << "FRANK\n";
        } else {
            int k;
            ll x;
            cin >> k >> x;
            update(k, x);
        }
    }

    return 0;
}