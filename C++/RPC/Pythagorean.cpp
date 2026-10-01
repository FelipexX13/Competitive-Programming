// <3
// Tema: Number Theory / Ternas Pitagoricas
// Resumen: Dado n, cuenta en cuantas ternas pitagoricas participa, separando cuatro casos
// Detalle: Dado n, cuenta en cuantas ternas pitagoricas participa, separando cuatro casos: n
// como hipotenusa (primitivas y no primitivas) y n como cateto (primitivas y no primitivas).
// Para n como hipotenusa recorre cada cateto a y verifica si n*n - a*a es cuadrado perfecto,
// ajustando la raiz con sqrtl mas dos while para corregir el error de punto flotante (nunca
// confiar en sqrt directo con enteros grandes); exige b > a para no contar la misma terna dos
// veces, y gcd(a,b) == 1 la marca como primitiva. Para n como cateto usa la factorizacion
// (c-b)(c+b) = n*n: cada divisor d < n de n*n da e = n*n/d, y si d y e tienen la misma paridad
// se recupera b = (e-d)/2 y c = (e+d)/2.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    if (!(cin >> n)) return 0;

    ll hypPrim = 0, hypNon = 0, legPrim = 0, legNon = 0;
    ll n2 = n * n;

    // --- n como hipotenusa ---
    for (ll a = 1; a < n; a++) {
        ll t = n2 - a * a;
        ll b = (ll)sqrtl((long double)t);
        while (b * b < t) b++;
        while (b * b > t) b--;
        if (b * b == t && b > a) {          // b > a evita contar dos veces
            if (__gcd(a, b) == 1) hypPrim++;
            else hypNon++;
        }
    }

    // --- n como cateto: (c-b)(c+b) = n^2 ---
    for (ll d = 1; d < n; d++) {            // d = c-b, d < e obliga d < n
        if (n2 % d) continue;
        ll e = n2 / d;                      // e = c+b
        if (((e - d) & 1LL)) continue;      // misma paridad
        ll b = (e - d) / 2;
        ll c = (e + d) / 2;
        if (b <= 0) continue;
        if (__gcd(n, b) == 1) legPrim++;
        else legNon++;
    }

    cout << hypPrim << ' ' << hypNon << ' '
         << legPrim << ' ' << legNon << '\n';
    return 0;
}
