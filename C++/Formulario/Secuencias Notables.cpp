// <3
// Tema: Formulario / Secuencias Notables
// Las sucesiones que hay que reconocer de vista en un caso de ejemplo, con los primeros
// valores y el punto exacto donde se desbordan: 20! es el ultimo factorial que cabe en
// long long, F(92) es el ultimo Fibonacci que cabe, y 2^31 ya no cabe en int. Saber el
// limite de antemano evita el overflow silencioso, que es el bug mas caro en competencia.

// =============== SECUENCIAS NOTABLES ===============
//
// Fibonacci   F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
//     n      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
//     F(n)   0   1   1   2   3   5   8  13  21  34  55  89 144 233 377 610
//     F(20)=6765  F(30)=832040  F(40)=102334155
//     F(92) = 7540113804746346429 es el ULTIMO que cabe en long long;
//     F(93) = 12200160415121876738 ya se pasa (el techo es 9.22*10^18).
//     Identidades:
//       F(m+n) = F(m)F(n+1) + F(m-1)F(n)    fast doubling
//       sum_{i<=n} F(i) = F(n+2) - 1
//       F(n-1)F(n+1) - F(n)^2 = (-1)^n      Cassini
//       gcd(F(m),F(n)) = F(gcd(m,n))
//
// Lucas   L(0)=2, L(1)=1, misma recurrencia
//     n      0   1   2   3   4   5   6   7   8   9  10  11  12  13
//     L(n)   2   1   3   4   7  11  18  29  47  76 123 199 322 521
//     L(n) = F(n-1) + F(n+1)
//
// Numeros figurados
//     n            1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
//     triangular   1   3   6  10  15  21  28  36  45  55  66  78  91 105 120
//     cuadrado     1   4   9  16  25  36  49  64  81 100 121 144 169 196 225
//     pentagonal   1   5  12  22  35  51  70  92 117 145 176 210 247 287 330
//     hexagonal    1   6  15  28  45  66  91 120 153 190 231 276 325 378 435
//     triangular T(n)=n(n+1)/2, T(n)+T(n-1) = n^2
//
// Factoriales (20! es el ultimo que cabe en long long)
//     n       0      1      2      3      4      5      6      7      8      9
//     n!      1      1      2      6     24    120    720   5040  40320 362880
//     10! = 3628800         13! = 6227020800   (ya se pasa de int)
//     11! = 39916800        15! = 1307674368000
//     12! = 479001600       20! = 2432902008176640000
//     21! desborda long long. Si aparece n! con n > 20, es modular.
//
// Potencias de 2
//     k       0     1     2     3     4     5     6     7     8     9    10
//     2^k     1     2     4     8    16    32    64   128   256   512  1024
//     2^20 = 1048576  (~10^6)
//     2^30 = 1073741824  (~10^9, limite de int)
//     2^31 = 2147483648  2^32 = 4294967296
//     2^62 = 4611686018427387904  (long long aguanta hasta 2^63-1)
//
// Numeros perfectos (iguales a la suma de sus divisores propios)
//     6, 28, 496, 8128, 33550336
//     Todos los pares son 2^(p-1)*(2^p - 1) con 2^p-1 primo (Mersenne).
//
// En C++
//     Fibonacci por fast doubling: O(log n), aguanta n = 10^18.
//     pair<ll,ll> fib(ll n) {               // devuelve {F(n), F(n+1)} mod M
//         if (!n) return {0, 1};
//         pair<ll,ll> p = fib(n >> 1);
//         ll a = p.first, b = p.second;
//         ll c = a * ((2*b % M - a + M) % M) % M;
//         ll d = (a*a + b*b) % M;
//         return (n & 1) ? make_pair(d, (c+d) % M) : make_pair(c, d);
//     }
//     Los figurados son O(1) directo:
//     ll triangular(ll n) { return n*(n+1)/2; }
//     ll pentagonal(ll n) { return n*(3*n-1)/2; }
//     ll hexagonal(ll n)  { return n*(2*n-1); }
//     Para factoriales, tabla hasta 20 y listo: mas alla no cabe sin modulo.
