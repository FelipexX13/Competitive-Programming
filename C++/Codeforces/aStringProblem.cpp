// <3
// Tema: String / Z-Function
// Resumen: Cuenta cuantos t != "a" permiten partir s en trozos que sean t o "a", usando al
// menos un t
// O: (n + m), funcion Z
// Detalle: Resuelve "a String Problem" (Codeforces): cuenta cuantos t != "a" permiten partir s
// en trozos que sean t o "a", usando al menos un t. Si s es todo 'a', cualquier bloque de 2 a n
// letras sirve, o sea n-1. Si no, todo t valido tiene que cubrir el primer caracter distinto de
// 'a', asi que se recorta el prefijo de 'a' (largo p) y se prueba como candidato cada prefijo
// x[0..len-1] del resto. La Z-function decide en O(1) si el candidato reaparece en una posicion
// (z[pos] >= len), y nxt[] salta de un bloque de 'a' al siguiente caracter distinto de 'a'
// tambien en O(1). Como el recorrido avanza de len en len, cada longitud cuesta O(m/len) y el
// total queda O(m log m). mn guarda el bloque de 'a' mas corto que antecede a alguna ocurrencia
// (contando el prefijo p): el candidato puede llevar hasta mn letras 'a' pegadas al frente, y
// por eso cada len que funciona aporta mn+1 en vez de 1.

#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        string s;
        cin >> s;

        int n = s.size();
        int p = 0;

        while (p < n && s[p] == 'a')
            p++;

        if (p == n) {
            cout << n - 1 << '\n';
            continue;
        }

        string x = s.substr(p);
        int m = x.size();

        vector<int> z = z_function(x);

        vector<int> nxt(m + 1, m);

        for (int i = m - 1; i >= 0; i--) {
            if (x[i] != 'a')
                nxt[i] = i;
            else
                nxt[i] = nxt[i + 1];
        }

        long long ans = 0;

        for (int len = 1; len <= m; len++) {
            int pos = 0;
            int mn = p;
            bool ok = true;

            while (true) {
                if (pos + len > m) {
                    ok = false;
                    break;
                }

                if (pos != 0 && z[pos] < len) {
                    ok = false;
                    break;
                }

                pos += len;

                int next = nxt[pos];

                if (next == m)
                    break;

                mn = min(mn, next - pos);
                pos = next;
            }

            if (ok)
                ans += mn + 1;
        }

        cout << ans << '\n';
    }

    return 0;
}
