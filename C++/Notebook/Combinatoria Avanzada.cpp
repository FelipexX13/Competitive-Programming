// <3
// Tema: Combinatorics / Combinatoria Avanzada (Lucas, Catalan, Stirling)
// Formulas combinatorias que van mas alla del C(n,k) basico con factoriales precomputados
// (ese caso ya esta resuelto en "Binomial Coefficients"). Aqui van cuatro herramientas:
// Lucas, para cuando n y k son gigantes (hasta 1e18) pero el modulo es un primo pequeno,
// descomponiendo n y k en base p y multiplicando los binomiales de cada digito; multinomial,
// para repartir n objetos en grupos de tamanos distintos; Catalan, que cuenta estructuras
// balanceadas (parentesis validos, arboles binarios, caminos de Dyck); y Stirling de segunda
// especie, que cuenta en cuantas formas se parten n elementos en k grupos no vacios.
// Las tres primeras necesitan que el modulo sea primo (usan el inverso via Fermat).

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll modpow(ll a, ll e, ll m)
{
    ll r = 1 % m;
    a %= m;
    while (e)
    {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

// C(n,k) mod p directo en O(k), para n y k chicos (uso interno de Lucas)
ll Csmall(ll n, ll k, ll p)
{
    if (k < 0 || k > n) return 0;
    ll num = 1, den = 1;
    for (ll i = 1; i <= k; i++)
    {
        num = num * ((n - k + i) % p) % p;
        den = den * i % p;
    }
    return num * modpow(den, p - 2, p) % p;
}

// Teorema de Lucas: C(n,k) mod p con n, k enormes y p primo pequeno
ll C_lucas(ll n, ll k, ll p)
{
    ll res = 1;
    while (n || k)
    {
        ll ni = n % p, ki = k % p;
        res = res * Csmall(ni, ki, p) % p;
        n /= p;
        k /= p;
        if (!res) return 0;
    }
    return res;
}

const int MOD = 1e9 + 7;
const int MAXN = 1000000;
vector<ll> fact(MAXN + 1), invFact(MAXN + 1);

void precomputar()
{
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) fact[i] = fact[i - 1] * i % MOD;
    invFact[MAXN] = modpow(fact[MAXN], MOD - 2, MOD);
    for (int i = MAXN; i >= 1; i--) invFact[i - 1] = invFact[i] * i % MOD;
}

ll C(int n, int k)
{
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

// n! / (a1! * a2! * ... * ak!) : repartir n objetos en grupos de tamanos dados
ll multinomial(const vector<int>& a)
{
    ll n = 0;
    for (int x : a) n += x;
    ll r = fact[n];
    for (int x : a) r = r * invFact[x] % MOD;
    return r;
}

// Catalan(n) = C(2n,n) / (n+1) : parentesis balanceados, arboles binarios, caminos de Dyck
ll catalan(int n)
{
    return C(2 * n, n) * modpow(n + 1, MOD - 2, MOD) % MOD;
}

// Stirling de segunda especie: partir n elementos en k grupos no vacios
vector<vector<ll>> stirling2(int n, int k)
{
    vector<vector<ll>> S(n + 1, vector<ll>(k + 1, 0));
    S[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            S[i][j] = (S[i - 1][j - 1] + (ll)j * S[i - 1][j]) % MOD;
        }
    }
    return S;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
