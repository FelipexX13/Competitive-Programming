// <3
// Tema: CSES / Prefijos con Map (Valores Negativos)
// Resumen: Cuantos subarreglos suman exactamente x, con valores que pueden ser negativos
// O: (n log n) por el map; con unordered_map seria (n)
// Uso: freq[0] = 1 antes del ciclo; ans += freq[sum - x]; freq[sum]++
// Detalle: Un subarreglo (i, j] suma x cuando pref[j] - pref[i] = x, asi que por cada prefijo
// nuevo se pregunta cuantas veces se vio ya el valor pref - x. LA VERSION I usa ventana
// deslizante porque los valores son positivos y la suma es monotona; aqui hay NEGATIVOS, la
// ventana deja de servir y toca el diccionario de prefijos. Reconocer ese cambio es todo el
// salto entre las dos versiones. El freq[0] = 1 del inicio es el prefijo vacio, y es lo que
// permite contar los subarreglos que arrancan en la posicion 1.

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

    map<ll, ll> freq;

    ll sum = 0;
    ll ans = 0;

    freq[0] = 1;

    for(int i = 0; i < n; i++)
    {
        ll a;
        cin >> a;

        sum += a;

        ans += freq[sum - x];

        freq[sum]++;
    }

    cout << ans << '\n';
}
