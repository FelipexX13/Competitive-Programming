// <3
// Tema: CSES / Binaria sobre la Respuesta
// Resumen: Partir el arreglo en k tramos contiguos minimizando la suma maxima de un tramo
// O: (n log(suma total)), un greedy lineal por intento
// Uso: check(a, k, x) arma partes greedy; binaria sobre x entre el maximo y la suma
// Detalle: El molde de 'minimizar el maximo': se adivina la respuesta x y se pregunta si es
// factible, que siempre es mas facil que calcularla. Aqui check(x) va metiendo elementos en el
// tramo actual mientras quepan y abre uno nuevo cuando se pasa; si al final uso k tramos o
// menos, x sirve. La factibilidad es MONOTONA (si x sirve, cualquier x mayor tambien), y por
// eso se puede hacer binaria sobre ella. Los limites de la binaria no son arbitrarios: abajo el
// elemento MAS GRANDE (ningun tramo puede medir menos) y arriba la suma total (un solo tramo).

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool check(vector<ll>& a, int k, ll x)
{
    int partes = 1;
    ll sum = 0;

    for(ll v : a)
    {
        if(sum + v > x)
        {
            partes++;
            sum = v;
        }
        else
        {
            sum += v;
        }
    }

    return partes <= k;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n);

    ll lo = 0;
    ll hi = 0;

    for(ll &x : a)
    {
        cin >> x;

        lo = max(lo, x);
        hi += x;
    }

    while(lo < hi)
    {
        ll mid = (lo + hi) / 2;

        if(check(a, k, mid))
            hi = mid;
        else
            lo = mid + 1;
    }

    cout << lo << '\n';
}
