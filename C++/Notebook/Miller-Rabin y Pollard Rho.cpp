// <3
// Tema: Number Theory / Miller-Rabin y Pollard Rho (Factorizar hasta 10^18)
// Resumen: Primalidad exacta y factorizacion de cualquier numero de 64 bits en milisegundos
// O: (log^3 n) isPrime, ~(n^(1/4)) esperado por factor en Pollard
// Uso: isPrime(n); auto f = factorizar(n); -> primos ordenados, con repeticion
// Detalle: La criba llega a 10^7 y probar divisores hasta la raiz llega a 10^12-10^14. Para
// numeros de 10^18 hace falta esto. Miller-Rabin con los 12 primeros primos como bases es
// DETERMINISTA para todo n < 3.3*10^24, o sea para todo unsigned long long: no es una prueba
// probabilistica en este rango. Pollard rho encuentra un divisor no trivial de un compuesto
// en ~n^(1/4) pasos esperados (para 10^18, del orden de 30.000), y factorizar() recursa.
// Antes de Pollard se sacan a mano los primos < 100: es mas rapido y evita los casos
// feos de rho con potencias de primos chicos.
// mulmod usa __int128: a*b de dos numeros de 10^18 no cabe en 64 bits.
// Divisores: con la factorizacion p1^e1 ... pk^ek hay (e1+1)...(ek+1) divisores; se generan
// con un for anidado por primo. phi(n) = n * prod (1 - 1/p) sobre los primos distintos.
// Si el problema factoriza MUCHOS numeros <= 10^7, la criba con menor factor primo es mejor.

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull mulmod(ull a, ull b, ull m)
{
    return (__uint128_t)a * b % m;
}

ull powmod(ull a, ull e, ull m)
{
    ull r = 1;
    a %= m;
    while (e)
    {
        if (e & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return r;
}

bool isPrime(ull n)
{
    if (n < 2) return false;
    for (ull p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if (n % p == 0) return n == p;
    }
    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0)
    {
        d >>= 1;
        s++;
    }
    for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool compuesto = true;
        for (int r = 1; r < s && compuesto; r++)
        {
            x = mulmod(x, x, n);
            if (x == n - 1) compuesto = false;
        }
        if (compuesto) return false;
    }
    return true;
}

// Un divisor no trivial de n (n compuesto, impar, sin factores < 100)
ull pollard(ull n)
{
    static mt19937_64 rng(1234567);
    while (true)
    {
        ull c = rng() % (n - 1) + 1, x = rng() % n, y = x, g = 1;
        // v*v + c en 128 bits: con n > 2^63, (mulmod(v,v,n) + c) DESBORDA 64 bits, la
        // secuencia deja de ser congruente mod p y rho tarda segundos (medido: 8 s)
        auto f = [&](ull v) { return (ull)(((__uint128_t)v * v + c) % n); };
        while (g == 1)
        {
            ull prod = 1, xs = x, ys = y;     // se guardan por si hay que rehacer
            for (int i = 0; i < 64; i++)      // un gcd cada 64 pasos, no cada paso
            {
                x = f(x);
                y = f(f(y));
                prod = mulmod(prod, x > y ? x - y : y - x, n);
            }
            g = __gcd(prod, n);
            if (g == n)                       // el lote se paso: rehacerlo de a uno
            {
                x = xs;
                y = ys;
                g = 1;
                for (int i = 0; i < 64 && g == 1; i++)
                {
                    x = f(x);
                    y = f(f(y));
                    g = __gcd(x > y ? x - y : y - x, n);
                }
            }
        }
        if (g != n) return g;                 // g == n: mala suerte, otra c
    }
}

void factorRec(ull n, vector<ull> &out)
{
    if (n == 1) return;
    if (isPrime(n))
    {
        out.push_back(n);
        return;
    }
    ull d = pollard(n);
    factorRec(d, out);
    factorRec(n / d, out);
}

vector<ull> factorizar(ull n)
{
    vector<ull> out;
    for (ull p = 2; p < 100 && p * p <= n; p++)
    {
        while (n % p == 0)
        {
            out.push_back(p);
            n /= p;
        }
    }
    if (n > 1) factorRec(n, out);
    sort(out.begin(), out.end());
    return out;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
