// <3
// Tema: CSES / Funcion de Prefijos (Cadena de Bordes)
// Resumen: Todos los bordes de s (prefijos que tambien son sufijos) salen de la funcion de
// prefijos
// O: (n), funcion de prefijos
// Detalle: Todos los bordes de s (prefijos que tambien son sufijos) salen de la funcion de
// prefijos, sin buscar nada mas. El borde mas largo es pi[n-1]; y el siguiente mas largo es el
// borde mas largo DE ESE BORDE, o sea pi[pi[n-1] - 1]; y asi hasta llegar a 0. POR QUE LA
// CADENA LOS DA TODOS: un borde de s mas corto que el borde mas largo b tambien es borde de b
// (es prefijo de s, luego prefijo de b; y es sufijo de s, luego sufijo de b). Asi que los
// bordes de s son b y los bordes de b, recursivamente, y no se salta ninguno. Salen de mayor a
// menor, por eso el reverse al final. Esta cadena j -> pi[j-1] es la misma que usa KMP para
// retroceder, y es de las ideas mas reusadas de strings: aparece en periodos, en el automata de
// KMP y en contar apariciones de cada prefijo.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

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

    vector<int> ans;

    int j = pi[n - 1];

    while (j > 0) {
        ans.push_back(j);
        j = pi[j - 1];
    }

    reverse(ans.begin(), ans.end());

    for (int x : ans)
        cout << x << ' ';

    cout << '\n';
}
