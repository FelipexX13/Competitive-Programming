// <3
// Tema: CSES / DP con Resta de la Aparicion Anterior
// Resumen: Cuantas subsecuencias distintas tiene la cadena, modulo 10^9+7
// O: (n) tiempo, (n) memoria
// Uso: dp[i] = 2*dp[i-1] - dp[last[c]-1]; la respuesta es dp[n] - 1
// Detalle: Cuantas SUBSECUENCIAS distintas tiene la cadena, modulo 10^9+7. Cada letra nueva
// duplica las subsecuencias, porque cada una existente se puede quedar igual o tomar la letra.
// Pero si esa letra YA habia salido antes, las que se formaron la vez pasada se cuentan dos
// veces, asi que se RESTA el dp justo antes de la aparicion anterior. Ese 'duplicar y restar la
// aparicion previa' es el patron, y aparece en varios problemas de conteo de subsecuencias
// distintas. El -1 del final quita la subsecuencia vacia. El last[] guarda posiciones
// 1-indexadas para que 0 signifique 'no ha salido', por eso el dp[last[c] - 1] y no
// dp[last[c]].

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    vector<ll> dp(n + 1);
    vector<int> last(26, 0);

    dp[0] = 1;

    for(int i = 1; i <= n; i++)
    {
        int c = s[i - 1] - 'a';

        dp[i] = 2 * dp[i - 1] % MOD;

        if(last[c] != 0)
        {
            dp[i] -= dp[last[c] - 1];

            if(dp[i] < 0)
                dp[i] += MOD;
        }

        last[c] = i;
    }

    // Quitamos la subsecuencia vacia
    cout << (dp[n] - 1 + MOD) % MOD << '\n';

    return 0;
}
