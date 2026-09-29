// <3
// Tema: CSES / Prefix XOR
// Idem prefix sums pero con xor, y funciona por la misma razon: el xor es su propia inversa, asi
// que pref[r] ^ pref[l-1] cancela todo lo de antes de l. Los elementos repetidos se anulan de a
// pares.
// CUANDO USAR: ver que el xor tiene inversa es lo que abre la puerta. Mismo patron para cualquier
// grupo abeliano: suma, xor, producto modular con inversos. Para min o max NO aplica, porque no
// hay nada que "deshaga" un minimo.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> pref(n + 1);

    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        pref[i] = pref[i - 1] ^ x;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (pref[r] ^ pref[l - 1]) << '\n';
    }
}
