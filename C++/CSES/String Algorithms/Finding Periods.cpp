// <3
// Tema: CSES / Periodos = n - Bordes
// Resumen: Un periodo p de s es un desplazamiento tal que s[i] = s[i+p] para todo i valido
// Detalle: Un periodo p de s es un desplazamiento tal que s[i] = s[i+p] para todo i valido. La
// equivalencia que resuelve el problema: p es periodo <=> n - p es un borde porque "s[i] =
// s[i+p] para todo i" dice exactamente que el prefijo de largo n-p es igual al sufijo de largo
// n-p. Asi que los periodos son n menos cada borde de la cadena de "Finding Borders", mas el
// periodo trivial n (que corresponde al borde vacio). Se juntan y se ordenan. CUANDO USAR: "la
// cadena es repeticion de un bloque", "el periodo mas corto", "cuantas veces se repite". El
// periodo mas corto es n - pi[n-1]; y s es una repeticion EXACTA de un bloque si y solo si ese
// periodo divide a n. Esa ultima condicion es la que se olvida.

#include <bits/stdc++.h>
using namespace std;

vector<int> KMP(string s) {
    int n = s.size();
    vector<int> pi(n);

    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];

        if (s[i] == s[j])
            j++;

        pi[i] = j;
    }

    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    vector<int> pi = KMP(s);

    vector<int> ans;

    int j = pi[n - 1];

    while (j > 0) {
        ans.push_back(n - j);
        j = pi[j - 1];
    }

    ans.push_back(n);

    sort(ans.begin(), ans.end());

    for (int x : ans)
        cout << x << ' ';

    cout << '\n';
}
