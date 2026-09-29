// <3
// Tema: CSES / DP sobre el Automata de KMP
// Cuenta cuantas cadenas de largo n sobre un alfabeto de 26 letras CONTIENEN un patron dado, modulo
// 1e9+7.
// LA IDEA CENTRAL: en vez de contar las que lo contienen, se cuenta con una DP donde el estado es
// "cuanto del patron llevo casado". Se construye el AUTOMATA de KMP: nxt[j][c] dice a que estado se
// pasa si llevo j caracteres del patron casados y llega la letra c. Eso se calcula con la funcion de
// prefijos, retrocediendo igual que en la busqueda de KMP.
// Con el automata, la DP es directa: dp[i][j] = cuantas cadenas de largo i dejan el automata en el
// estado j. Desde cada estado se prueban las 26 letras y se avanza. Al llegar al estado m (patron
// completo) esa cadena ya sirve, y todas las formas de completarla tambien: se suman de golpe
// multiplicando por 26^(lo que falta), sin seguir simulando.
// POR QUE HACE FALTA EL AUTOMATA Y NO BASTA CONTAR: dos cadenas distintas pueden dejar el mismo
// "sufijo util" del patron, y de ahi en adelante se comportan igual. El estado de KMP es
// exactamente esa informacion, y es lo que colapsa un espacio de 26^n a n*m estados.
// La construccion de nxt se hace UNA vez, en O(m * 26), retrocediendo con pi; hacerlo dentro de la
// DP seria pagarlo n veces.
// Este patron (automata de KMP + DP) es el que resuelve toda la familia de "cuantas cadenas
// contienen / evitan un patron", y con varios patrones a la vez el equivalente es Aho-Corasick.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;


// --------------------------------------------------
// KMP - Prefix Function
// --------------------------------------------------

vector<int> prefixFunction(const string& s) {

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


// --------------------------------------------------
// Transiciones de KMP
// --------------------------------------------------

vector<vector<int>> buildKMPTransitions(const string& p) {

    int m = p.size();

    vector<int> pi = prefixFunction(p);

    vector<vector<int>> nxt(m, vector<int>(26));

    for (int j = 0; j < m; j++) {

        for (int c = 0; c < 26; c++) {

            char x = 'A' + c;

            int k = j;

            while (k > 0 && p[k] != x)
                k = pi[k - 1];

            if (p[k] == x)
                k++;

            nxt[j][c] = k;
        }
    }

    return nxt;
}


// --------------------------------------------------
// Main
// --------------------------------------------------

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string p;

    cin >> n >> p;

    int m = p.size();

    auto nxt = buildKMPTransitions(p);

    // Estados:
    // 0 ... m-1 = cuanto del patron tenemos
    // m         = el patron ya aparecio
    vector<ll> dp(m + 1);
    vector<ll> ndp(m + 1);

    dp[0] = 1;

    for (int len = 0; len < n; len++) {

        fill(ndp.begin(), ndp.end(), 0);

        for (int j = 0; j <= m; j++) {

            if (dp[j] == 0)
                continue;

            // Ya aparecio el patron.
            // Cualquier caracter que agreguemos mantiene
            // este estado.
            if (j == m) {

                ndp[m] += dp[j] * 26;
                ndp[m] %= MOD;

                continue;
            }

            // Todavia no aparecio.
            for (int c = 0; c < 26; c++) {

                int k = nxt[j][c];

                ndp[k] += dp[j];
                ndp[k] %= MOD;
            }
        }

        dp.swap(ndp);
    }

    cout << dp[m] << '\n';

    return 0;
}
