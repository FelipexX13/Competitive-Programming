// <3
// Tema: CSES / Meet in the Middle
// Resumen: Cuantos subconjuntos suman exactamente x, con n hasta 40
// O: (2^(n/2) * n), contra (2^n) de la fuerza bruta
// Uso: generateSums(a, l, r, sums) por mitad; ordenar una y buscar en ella
// Detalle: Con n = 40 los 2^40 subconjuntos no caben, pero 2^20 si. Se parte el arreglo por la
// MITAD, se generan todas las sumas de cada mitad (2^20 cada una), se ordena la segunda y para
// cada suma de la primera se busca cuantas de la segunda completan x. ESE ES EL PATRON: cuando
// 2^n no cabe pero 2^(n/2) si, partir en dos y cruzar. Aplica a subset sum, a contar caminos, y
// en general a cualquier enumeracion exponencial sobre un n de 30 a 45. El conteo usa
// upper_bound - lower_bound para contar repetidos de golpe, que es lo correcto cuando varias
// combinaciones dan la misma suma.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void generateSums(vector<ll>& a, int l, int r, vector<ll>& sums)
{
    int len = r - l;

    for(int mask = 0; mask < (1 << len); mask++)
    {
        ll sum = 0;

        for(int i = 0; i < len; i++)
        {
            if(mask & (1 << i))
                sum += a[l + i];
        }

        sums.push_back(sum);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll x;

    cin >> n >> x;

    vector<ll> a(n);

    for(auto &v : a)
        cin >> v;

    int mid = n / 2;

    vector<ll> left;
    vector<ll> right;

    generateSums(a, 0, mid, left);
    generateSums(a, mid, n, right);

    sort(right.begin(), right.end());

    ll ans = 0;

    for(ll sum : left)
    {
        ll need = x - sum;

        ans += upper_bound(right.begin(), right.end(), need)
             - lower_bound(right.begin(), right.end(), need);
    }

    cout << ans << '\n';
}
