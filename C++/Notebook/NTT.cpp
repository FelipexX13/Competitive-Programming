// <3
// Tema: Math / NTT (Multiplicar Polinomios mod 998244353)
// Resumen: Producto de dos polinomios, o convolucion de dos arreglos, en O(n log n)
// O: (n log n)
// Uso: c = multiplicar(a, b); c[k] = suma de a[i]*b[k-i] mod 998244353
// Detalle: La multiplicacion ingenua es O(n*m); con n = m = 10^5 son 10^10, no entra. NTT es
// la FFT pero en aritmetica modular: evalua los dos polinomios en las raices n-esimas de la
// unidad mod p, multiplica punto a punto y vuelve con la transformada inversa. Sin doubles,
// asi que no hay error de redondeo. Funciona porque 998244353 = 119*2^23 + 1 tiene raices
// de la unidad de orden 2^23 (con 3 como raiz primitiva): el resultado puede tener hasta
// 2^23 = 8.388.608 coeficientes.
// Cuando sirve aunque no lo parezca: contar pares (i,j) con a_i + b_j = s para todo s (hacer
// polinomios de frecuencias y multiplicarlos), sumas de dados, "de cuantas formas sumo k
// eligiendo uno de cada grupo", y comparar patrones con comodines.
// OJO: el resultado sale MOD 998244353. Si se necesita el valor EXACTO (sin modulo) y cada
// coeficiente del producto es menor que 998244353, sale exacto igual. Si puede pasarse, hay
// que hacer CRT con dos o tres primos NTT, o FFT con doubles cuidando el redondeo.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353, RAIZ = 3;

ll power(ll a, ll e)
{
    ll r = 1;
    a %= MOD;
    while (e)
    {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void ntt(vector<ll> &a, bool inversa)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)          // permutacion de bits invertidos
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        ll w = power(RAIZ, (MOD - 1) / len);
        if (inversa) w = power(w, MOD - 2);
        for (int i = 0; i < n; i += len)
        {
            ll wn = 1;
            for (int j = 0; j < len / 2; j++)
            {
                ll u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (inversa)
    {
        ll inv = power(n, MOD - 2);
        for (ll &x : a) x = x * inv % MOD;
    }
}

vector<ll> multiplicar(vector<ll> a, vector<ll> b)
{
    if (a.empty() || b.empty()) return {};
    int tam = a.size() + b.size() - 1, n = 1;
    while (n < tam) n <<= 1;
    for (ll &x : a) x = ((x % MOD) + MOD) % MOD;
    for (ll &x : b) x = ((x % MOD) + MOD) % MOD;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(tam);
    return a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
