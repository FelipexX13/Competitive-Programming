// <3
// Tema: Formulario / Combinatoria
// Conteos clasicos con sus primeros valores para identificar la sucesion en la salida de
// ejemplo: 1, 2, 5, 14, 42 son Catalan; 1, 1, 2, 5, 15, 52 son Bell; 1, 0, 1, 2, 9, 44 son
// desarreglos. Incluye el triangulo de Pascal hasta n=10 y las identidades que permiten
// cerrar una sumatoria antes de escribir una sola linea de codigo.

// =============== COMBINATORIA ===============
//
// Los cuatro conteos base
//     P(n,k) = n!/(n-k)!        ordenado,  sin repetir
//     C(n,k) = n!/(k!(n-k)!)    sin orden, sin repetir
//     n^k                       ordenado,  con repeticion
//     C(n+k-1, k)               sin orden, con repeticion
//     n!/(a! b! c! ...)         permutaciones de un multiconjunto
//
// Identidades de binomiales (sirven para colapsar sumatorias)
//     C(n,k) = C(n-1,k-1) + C(n-1,k)     Pascal
//     C(n,k) = C(n,n-k)                  simetria
//     sum_k C(n,k) = 2^n                 fila completa
//     sum_k (-1)^k C(n,k) = 0            para n >= 1
//     sum_{i=k..n} C(i,k) = C(n+1,k+1)   hockey stick
//     sum_i C(m,i)C(n,k-i) = C(m+n,k)    Vandermonde
//     k*C(n,k) = n*C(n-1,k-1)            absorcion
//
// Triangulo de Pascal
//     n=0     1
//     n=1     1    1
//     n=2     1    2    1
//     n=3     1    3    3    1
//     n=4     1    4    6    4    1
//     n=5     1    5   10   10    5    1
//     n=6     1    6   15   20   15    6    1
//     n=7     1    7   21   35   35   21    7    1
//     n=8     1    8   28   56   70   56   28    8    1
//     n=9     1    9   36   84  126  126   84   36    9    1
//     n=10    1   10   45  120  210  252  210  120   45   10    1
//
// Stars and bars: repartir n objetos iguales en k grupos
//     permitiendo grupos vacios : C(n+k-1, k-1)
//     todos con al menos uno    : C(n-1, k-1)
//
// Catalan   Cat(n) = C(2n,n)/(n+1) = sum_i Cat(i)*Cat(n-1-i)
//     Parentesis balanceados, arboles binarios de n nodos,
//     triangulaciones de un poligono de n+2 lados, caminos de Dyck.
//     n          0     1     2     3     4     5     6     7     8     9
//     Cat(n)     1     1     2     5    14    42   132   429  1430  4862
//     Cat(12)=208012  Cat(13)=742900  Cat(14)=2674440
//
// Desarreglos: permutaciones sin ningun punto fijo
//     !n = (n-1)(!(n-1) + !(n-2))   ~ n!/e
//     n         0        1        2        3        4        5        6
//     !n        1        0        1        2        9       44      265
//
// Bell: formas de particionar un conjunto de n elementos
//     n         0      1      2      3      4      5      6      7      8
//     B(n)      1      1      2      5     15     52    203    877   4140
//
// Inclusion-exclusion
//     |AuB| = |A| + |B| - |AnB|
//     |AuBuC| = |A|+|B|+|C| -|AnB|-|AnC|-|BnC| +|AnBnC|
//     General: sumar los de tamano impar, restar los de tamano par.
//
// En C++
//     ll nCr(ll n, ll k) {                  // O(k), sin precomputar nada
//         if (k < 0 || k > n) return 0;
//         k = min(k, n - k);
//         ll r = 1;
//         for (ll i = 1; i <= k; i++) r = r * (n - i + 1) / i;
//         return r;                         // la division siempre es exacta
//     }
//     ll nPr(ll n, ll k) {                  // O(k), con orden
//         if (k < 0 || k > n) return 0;
//         ll r = 1;                         // SIN el min(k, n-k): esa
//         for (ll i = 0; i < k; i++)        // simetria es solo de C
//             r *= (n - i);
//         return r;                         // crece rapido: P(60,10) cabe,
//     }                                     // P(60,11) ya se desborda
//     ll catalan(int n) {                   // O(n), sin binomiales
//         ll c = 1;
//         for (int i = 0; i < n; i++) c = c * 2 * (2*i + 1) / (i + 2);
//         return c;
//     }
//     ll desarreglos(int n) {               // O(n), sin memoria extra
//         ll a = 1, b = 0;
//         for (int i = 2; i <= n; i++) {
//             ll c = (i-1) * (a + b); a = b; b = c;
//         }
//         return n == 0 ? 1 : b;
//     }
//     ll bell(int n) {                      // triangulo de Bell, O(n^2)
//         vector<ll> f = {1};
//         for (int i = 0; i < n; i++) {
//             vector<ll> g = {f.back()};
//             for (ll x : f) g.push_back(g.back() + x);
//             f = g;
//         }
//         return f[0];
//     }
//     Si n es grande y hay muchas consultas, precomputa factoriales e inversos
//     (esta en la ficha Binomial Coefficients) y cada nCr sale en O(1).
