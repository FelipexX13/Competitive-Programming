// <3
// Tema: Combinatorics / Contar por Quien es la Mediana
// Resumen: Probabilidad de que un subconjunto de k elementos tenga la misma mediana que todo
// O: (n log n) por el sort, mas (n) de barrido; (MAXN) de precomputo de factoriales
// Uso: ORDENAR primero; cada posicion i aporta C(i,m) * C(n-1-i,m) con m = (k-1)/2
// Detalle: Se escoge al azar, uniformemente entre los C(n,k) posibles, un subconjunto de k
// elementos (k impar). Se pide la probabilidad de que su mediana sea igual a la mediana del
// arreglo completo, como fraccion modulo 1e9+7. LA IDEA: en vez de recorrer subconjuntos, se
// cuenta POR QUIEN ES LA MEDIANA. Con el arreglo ordenado, el elemento de la posicion i es la
// mediana de un subconjunto si y solo si se escogen m = (k-1)/2 elementos de los i que tiene
// a la izquierda y m de los n-1-i de la derecha, o sea C(i,m) * C(n-1-i,m) subconjuntos. Se
// suman los de las posiciones que valen lo mismo que la mediana global (P) y los demas (Q), y
// la respuesta es P / (P+Q) con inverso modular. El rango de i va de m a n-1-m, que son
// exactamente n-k+1 posiciones: antes de m no hay suficientes elementos a la izquierda.
// ESTE ARCHIVO EXISTE POR DOS ERRORES QUE COSTARON UN PROBLEMA EN LA NACIONAL 2026, y los dos
// son de los que no avisan. (1) EL ARREGLO HAY QUE ORDENARLO. No solo para que nums[(n-1)/2]
// sea la mediana: todo el conteo asume que los i de la izquierda son los MENORES. Medido sin
// ordenar: 86 de 220 casos chicos dan mal. (2) P Y Q HAY QUE REDUCIRLOS AL ACUMULAR. Cada
// termino cabe, pero la suma de n-k+1 terminos de hasta 1e9 llega a 1e15; eso cabe en long
// long y nada falla ahi. Revienta una linea despues, cuando ese P+Q se pasa como BASE a
// modpow y adentro se hace a*a: 1e10 al cuadrado es 1e20 y el tope de long long es 9.2e18.
// Medido: con k=3 aguanta hasta n=2000 y se rompe en n=5001; con n=101 aguanta hasta k=5 y se
// rompe en k=7. O sea, los ejemplos del enunciado pasan y los casos grandes no.
// La guarda a %= MOD al entrar a modpow arregla el segundo error sola, sin tocar P ni Q, y es
// la que conviene tener siempre puesta.
// VERIFICADO contra fuerza bruta sobre TODOS los C(n,k) subconjuntos: 220 casos con n hasta 11
// y todos los k impares, 0 diferencias; y contra la misma formula en enteros exactos de Python
// hasta n = 99999, tambien 0 diferencias.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;
const ll MAXN = 1000001;

vector<ll> fact(MAXN + 1), invFact(MAXN + 1);

ll modpow(ll a, ll e)
{
    a %= MOD;                       // la guarda: sin esto, una base sin
    ll ans = 1;                     // reducir desborda en el a*a de abajo

    while (e)
    {
        if (e & 1)
            ans = ans * a % MOD;

        a = a * a % MOD;
        e >>= 1;
    }

    return ans;
}

ll moddivision(ll a, ll b)
{
    return a % MOD * modpow(b, MOD - 2) % MOD;
}

ll nCr(ll a, ll b)
{
    if (b < 0 || b > a)
        return 0;

    ll r = fact[a];

    r = r * invFact[b] % MOD;
    r = r * invFact[a - b] % MOD;

    return r;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;

    for (ll i = 1; i <= MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[MAXN] = modpow(fact[MAXN], MOD - 2);

    for (ll i = MAXN; i >= 1; i--)
        invFact[i - 1] = invFact[i] * i % MOD;

    ll n, k;

    while (cin >> n >> k)
    {
        if (n == 0 && k == 0)
            break;

        vector<ll> nums(n);

        for (ll i = 0; i < n; i++)
            cin >> nums[i];

        sort(nums.begin(), nums.end());     // SIN ESTO nada de abajo sirve

        ll median = nums[(n - 1) / 2];
        ll m = (k - 1) / 2;

        ll P = 0;
        ll T = 0;

        // i solo puede ser mediana si le caben m a cada lado
        for (ll i = m; i <= n - 1 - m; i++)
        {
            ll c = nCr(i, m) * nCr(n - 1 - i, m) % MOD;

            T = (T + c) % MOD;              // reducir AL ACUMULAR, no al final

            if (nums[i] == median)
                P = (P + c) % MOD;
        }

        cout << moddivision(P, T) << '\n';
    }

    return 0;
}
