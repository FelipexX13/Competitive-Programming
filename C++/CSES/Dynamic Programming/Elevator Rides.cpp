// <3
// Tema: CSES / Bitmask DP con Estado de Dos Partes
// Resumen: Minimo de viajes de ascensor para subir a n personas con limite de peso x
// O: (2^n * n)
// Uso: dp[mask] = {viajes, peso del ultimo}; se minimiza el par con min()
// Detalle: El truco es QUE SE GUARDA en el dp. No basta con la cantidad de viajes: entre dos
// formas de subir al mismo grupo con los mismos viajes, es mejor la que deja el ultimo viaje
// mas vacio, porque deja mas espacio para los que faltan. Por eso dp[mask] es el PAR {viajes,
// peso del ultimo viaje}, y el min() de pair lo compara lexicograficamente solo: primero menos
// viajes, y si empatan, menos peso. Esa comparacion gratis del pair es lo que hace que el
// codigo quepa en 20 lineas. OJO: usa auto [a,b], que pide C++17. En el juez compila.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll x;

    cin >> n >> x;

    vector<ll> w(n);

    for(auto &v : w)
        cin >> v;

    int N = 1 << n;

    // {numero de viajes, peso del ultimo viaje}
    vector<pair<int,ll>> dp(N, {n + 1, 0});

    dp[0] = {1, 0};

    for(int mask = 0; mask < N; mask++)
    {
        for(int i = 0; i < n; i++)
        {
            if(mask & (1 << i))
                continue;

            auto [rides, weight] = dp[mask];

            pair<int,ll> nxt;

            if(weight + w[i] <= x)
            {
                // La persona cabe en el ultimo viaje
                nxt = {rides, weight + w[i]};
            }
            else
            {
                // Abrimos un nuevo viaje
                nxt = {rides + 1, w[i]};
            }

            int newMask = mask | (1 << i);

            dp[newMask] = min(dp[newMask], nxt);
        }
    }

    cout << dp[N - 1].first << '\n';
}
