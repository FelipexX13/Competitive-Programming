// <3
// Tema: Dynamic Programming / DP con Arreglo de Diferencias
// Resumen: Contar secuencias donde el promedio se mantiene entero en cada paso, modulo
// 998244353
// Detalle: Resuelve "Balanced Balloons" (problema B, Regionals 2025): contar secuencias donde
// el promedio se mantiene entero en cada paso, modulo 998244353. El estado es dp[q] = cuantas
// secuencias de i elementos tienen promedio actual q. Al agregar el elemento i+1, el nuevo
// promedio q2 tiene que cumplir que el aporte quede entre 1 y K: 1 <= (i+1)*q2 - i*q <= K que
// despejando da un INTERVALO de q2 validos: de ceil((i*q+1)/(i+1)) hasta floor((i*q+K)/(i+1)).
// EL TRUCO QUE LO HACE VIABLE: cada q manda su dp[q] a un intervalo CONTIGUO de destinos. Sumar
// uno por uno seria O(K) por origen y O(K^2) por paso. Con un ARREGLO DE DIFERENCIAS se marca
// +dp[q] en lo y -dp[q] en hi+1, y al final una suma de prefijos reconstruye toda la fila de
// golpe: O(K) por paso en vez de O(K^2). Ese patron -"la transicion va a un rango, no a un
// punto"- es el que convierte muchas DP cuadraticas en lineales, y vale reconocerlo: si al
// escribir la transicion sale un for sobre un intervalo, casi siempre se puede cambiar por
// diferencias. El N = min(N, K) del principio es una poda real: pasadas K personas ya no
// aparecen promedios nuevos, asi que iterar mas es trabajo perdido. La resta modular se hace
// con (x - y + MOD) % MOD para no quedarse en negativo, que es el error clasico de los arreglos
// de diferencias con modulo.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, K;
    cin >> N >> K;

    // Despues de K personas ya no aparecen nuevas posibilidades.
    N = min(N, K);

    /*
        dp[q] = cantidad de secuencias cuyo promedio actual es q.
    */

    vector<ll> dp(K + 2, 0);

    // Con una sola persona:
    // puede aportar cualquier valor entre 1 y K.
    for(int q = 1; q <= K; q++)
        dp[q] = 1;

    for(ll i = 1; i < N; i++)
    {
        vector<ll> diff(K + 3, 0);

        for(int q = 1; q <= K; q++)
        {
            if(dp[q] == 0)
                continue;

            /*
                Queremos:

                1 <= (i+1)*q2 - i*q <= K

                Por lo tanto:

                ceil((i*q + 1)/(i+1)) <= q2
                q2 <= floor((i*q + K)/(i+1))
            */

            ll lo = (i * q + 1 + i) / (i + 1);
            ll hi = (i * q + K) / (i + 1);

            lo = max(lo, 1LL);
            hi = min(hi, K);

            if(lo <= hi)
            {
                // Sumar dp[q] a todo [lo, hi]
                diff[lo] = (diff[lo] + dp[q]) % MOD;

                diff[hi + 1] =
                    (diff[hi + 1] - dp[q] + MOD) % MOD;
            }
        }

        // Reconstruimos ndp usando prefijos.
        vector<ll> ndp(K + 2, 0);

        ll cur = 0;

        for(int q = 1; q <= K; q++)
        {
            cur = (cur + diff[q]) % MOD;
            ndp[q] = cur;
        }

        dp = ndp;
    }

    ll ans = 0;

    for(int q = 1; q <= K; q++)
    {
        ans = (ans + dp[q]) % MOD;
    }

    cout << ans << '\n';

    return 0;
}
