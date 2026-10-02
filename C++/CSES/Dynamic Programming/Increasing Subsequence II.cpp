// <3
// Tema: CSES / Contar Subsecuencias Crecientes con Fenwick
// Resumen: Cuantas subsecuencias estrictamente crecientes tiene el arreglo, modulo 10^9+7
// O: (n log n), Fenwick sobre coordenadas comprimidas
// Uso: dp = 1 + fw.query(pos-1); fw.add(pos, dp)  // 1-INDEXADO
// Detalle: dp[i] = cuantas subsecuencias crecientes TERMINAN en i, que es 1 (ella sola) mas la
// suma de los dp de todos los valores estrictamente menores que ya se vieron. Esa suma 'de
// todos los menores vistos hasta ahora' es exactamente una consulta de prefijo, asi que un
// Fenwick indexado por VALOR (no por posicion) la responde en log n. Como los valores son
// grandes, primero se comprimen. El pos-1 de la consulta es lo que hace que sea ESTRICTAMENTE
// menor; con pos seria menor o igual y contaria repetidos. Fenwick indexado por valor es un
// patron que sirve para inversiones, para rangos y para cualquier 'cuantos menores llevo'.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

struct Fenwick
{
    int n;
    vector<ll> bit;

    Fenwick(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void add(int pos, ll val)
    {
        for(; pos <= n; pos += pos & -pos)
        {
            bit[pos] += val;
            bit[pos] %= MOD;
        }
    }

    ll query(int pos)
    {
        ll ans = 0;

        for(; pos > 0; pos -= pos & -pos)
        {
            ans += bit[pos];
            ans %= MOD;
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);

    for(auto &x : a)
        cin >> x;

    // Coordinate compression
    vector<ll> vals = a;

    sort(vals.begin(), vals.end());

    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    Fenwick fw(vals.size());

    ll ans = 0;

    for(int i = 0; i < n; i++)
    {
        int pos = lower_bound(vals.begin(), vals.end(), a[i])
                  - vals.begin() + 1;

        // Todos los valores estrictamente menores
        ll dp = 1 + fw.query(pos - 1);

        dp %= MOD;

        fw.add(pos, dp);

        ans += dp;
        ans %= MOD;
    }

    cout << ans << '\n';
}
