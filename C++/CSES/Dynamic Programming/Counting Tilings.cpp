// <3
// Tema: CSES / Broken Profile DP (Dominos)
// Resumen: De cuantas formas se llena una cuadricula n x m con fichas de domino
// O: (m * 2^n * n), con n el lado corto
// Uso: generate(0, mask, 0, dp[mask], dp, ndp) por cada mascara de la columna
// Detalle: DP columna por columna, donde la MASCARA dice que celdas de la columna siguiente ya
// estan ocupadas por una ficha horizontal que se asomo desde la actual. Eso es el broken
// profile. La recursion generate() decide celda por celda de la columna: si ya esta ocupada,
// sigue; si no, puede poner una ficha VERTICAL (dos celdas de esta misma columna) o una
// HORIZONTAL, que ocupa una celda de la siguiente y por eso prende el bit en nextMask. OJO con
// cual lado es n: el estado es 2^n, asi que n tiene que ser el LADO CORTO. Con 10 x 1000 hay
// que girar la cuadricula. La respuesta es dp[0] al final: ninguna ficha asomandose fuera del
// tablero.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

int n, m;

void generate(int row, int mask, int nextMask, ll ways,
              vector<ll>& dp, vector<ll>& ndp)
{
    if(row == n)
    {
        ndp[nextMask] += ways;
        ndp[nextMask] %= MOD;
        return;
    }

    // Esta celda ya esta ocupada
    if(mask & (1 << row))
    {
        generate(row + 1, mask, nextMask, ways, dp, ndp);
        return;
    }

    // Ficha horizontal
    if(row + 1 < n && !(mask & (1 << (row + 1))))
    {
        generate(row + 2, mask, nextMask, ways, dp, ndp);
    }

    // Ficha vertical hacia la siguiente columna
    generate(row + 1,
             mask,
             nextMask | (1 << row),
             ways,
             dp,
             ndp);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int states = 1 << n;

    vector<ll> dp(states);
    dp[0] = 1;

    for(int col = 0; col < m; col++)
    {
        vector<ll> ndp(states);

        for(int mask = 0; mask < states; mask++)
        {
            if(dp[mask] == 0)
                continue;

            generate(0, mask, 0, dp[mask], dp, ndp);
        }

        dp = ndp;
    }

    cout << dp[0] << '\n';
}
