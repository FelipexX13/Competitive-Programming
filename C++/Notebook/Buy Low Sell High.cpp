// <3
// Tema: Greedy / Buy Low Sell High (Comprar y Vender Acciones)
// O: (n) las tres primeras, (n*K) la de K transacciones
// Uso: maxProfit(p) -> {ganancia,{compra,venta}}; maxProfitK(p,K)
// Precio de una accion por dia: comprar un dia y vender un dia POSTERIOR (una transaccion)
// maximizando la ganancia. Un solo recorrido O(n), O(1) de memoria: se guarda el dia mas
// barato visto hasta ahora (el mejor momento para haber comprado) y cada dia se prueba vender
// hoy contra ese minimo. Si el precio solo baja, la respuesta es 0 (no operar).
// Es Kadane disfrazado: la ganancia es la suma maxima de un subarreglo de d[i] = p[i]-p[i-1].
// Variantes tipicas (en todas no se puede tener dos acciones a la vez):
//  - Ilimitadas: sumar cada subida max(0, d[i]); toda subida se puede cobrar.
//  - Con comision por transaccion: DP de dos estados, cash (sin accion) y hold (con accion).
//  - A lo sumo K transacciones: los mismos dos estados por cada transaccion, O(n*K).
//    Con K >= n/2 ya no limita y equivale a ilimitadas (O(n)).

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll NEG = LLONG_MIN / 4;

// Una transaccion: {ganancia, {dia de compra, dia de venta}} (dias -1 si no conviene operar)
pair<ll, pair<int, int>> maxProfit(const vector<ll> &p)
{
    ll best = 0;
    int low = 0, buy = -1, sell = -1;
    for (int i = 1; i < (int)p.size(); i++)
    {
        if (p[i] < p[low]) low = i;
        else if (p[i] - p[low] > best)
        {
            best = p[i] - p[low];
            buy = low;
            sell = i;
        }
    }
    return {best, {buy, sell}};
}

// Transacciones ilimitadas
ll maxProfitUnlimited(const vector<ll> &p)
{
    ll s = 0;
    for (int i = 1; i < (int)p.size(); i++) s += max(0LL, p[i] - p[i - 1]);
    return s;
}

// Ilimitadas, pagando `fee` por cada transaccion completa
ll maxProfitFee(const vector<ll> &p, ll fee)
{
    ll cash = 0, hold = NEG;
    for (ll x : p)
    {
        hold = max(hold, cash - x);
        cash = max(cash, hold + x - fee);
    }
    return cash;
}

// A lo sumo K transacciones
ll maxProfitK(const vector<ll> &p, int K)
{
    if (K <= 0) return 0;
    if (2 * K >= (int)p.size()) return maxProfitUnlimited(p);
    vector<ll> hold(K + 1, NEG), cash(K + 1, 0);
    for (ll x : p)
    {
        for (int t = 1; t <= K; t++)
        {
            hold[t] = max(hold[t], cash[t - 1] - x);
            cash[t] = max(cash[t], hold[t] + x);
        }
    }
    return cash[K];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> p(n);
    for (auto &x : p) cin >> x;

    auto r = maxProfit(p);
    cout << r.first << "\n";
    cout << r.second.first << " " << r.second.second << "\n";  // -1 -1 si no se opera
    return 0;
}
