// <3
// Tema: Number Theory / Aritmetica Modular (Euclides Extendido, Phi, CRT General)
// Resumen: Inverso con modulo NO primo, phi de Euler, y CRT aunque los modulos no sean coprimos
// O: (log n) extgcd, inverso y cada paso de CRT; (raiz n) phi; (n log log n) la criba de phi
// Uso: inverso(a,m) da -1 si no existe; crt({r1,r2},{m1,m2}) -> {x, lcm} o {-1,-1}
// Detalle: Fermat (a^(p-2)) solo sirve si el modulo es PRIMO. Para cualquier modulo, el
// inverso de a existe si y solo si gcd(a,m) = 1, y sale de Euclides extendido: si
// a*x + m*y = 1, entonces a*x = 1 (mod m). extgcd devuelve g = gcd(a,b) y deja x, y con
// a*x + b*y = g; sirve tambien para ecuaciones diofanticas a*x + b*y = c (hay solucion
// si y solo si g divide a c; se escala x,y por c/g y las demas soluciones son
// x + k*(b/g), y - k*(a/g)).
// phi(n) cuenta los 1..n coprimos con n. Euler: a^phi(m) = 1 (mod m) si gcd(a,m) = 1, asi
// que un exponente gigante se reduce mod phi(m) (solo con gcd(a,m) = 1).
// CRT general: x = r1 (mod m1) y x = r2 (mod m2) tiene solucion si y solo si
// r1 = r2 (mod gcd(m1,m2)); la solucion es unica modulo lcm(m1,m2). Se pliega de a dos
// ecuaciones. Las cuentas intermedias van en __int128 porque lcm puede llegar a 10^18.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Devuelve g = gcd(a,b) y deja x, y con a*x + b*y = g
ll extgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Inverso de a modulo m (m cualquiera, no hace falta que sea primo). -1 si no existe
ll inverso(ll a, ll m)
{
    ll x, y;
    ll g = extgcd(((a % m) + m) % m, m, x, y);
    if (g != 1) return -1;
    return ((x % m) + m) % m;
}

// phi de Euler de un solo n, por factorizacion hasta la raiz
ll phi(ll n)
{
    ll r = n;
    for (ll p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
        {
            while (n % p == 0) n /= p;
            r -= r / p;
        }
    }
    if (n > 1) r -= r / n;
    return r;
}

// phi de 0..n de una vez, tipo criba
vector<int> phiCriba(int n)
{
    vector<int> ph(n + 1);
    iota(ph.begin(), ph.end(), 0);
    for (int i = 2; i <= n; i++)
    {
        if (ph[i] == i)                       // i es primo
        {
            for (int j = i; j <= n; j += i) ph[j] -= ph[j] / i;
        }
    }
    return ph;
}

// x = r[i] (mod m[i]) para todo i. Devuelve {x, lcm} con 0 <= x < lcm, o {-1,-1}
pair<ll, ll> crt(const vector<ll> &r, const vector<ll> &m)
{
    ll x = 0, M = 1;                          // x = 0 (mod 1) al empezar
    for (int i = 0; i < (int)r.size(); i++)
    {
        ll ri = ((r[i] % m[i]) + m[i]) % m[i];
        ll p, q;
        ll g = extgcd(M, m[i], p, q);
        if ((ri - x) % g != 0) return {-1, -1};
        // M*p = g (mod m[i]) -> k = (ri - x)/g * p (mod m[i]/g)
        ll mg = m[i] / g;
        __int128 k = (__int128)((ri - x) / g) % mg * (p % mg) % mg;
        if (k < 0) k += mg;
        __int128 nuevoM = (__int128)M * mg;
        x = (ll)((x + (__int128)M * k) % nuevoM);
        M = (ll)nuevoM;
    }
    return {x, M};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
