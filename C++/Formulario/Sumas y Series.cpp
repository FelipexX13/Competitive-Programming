// <3
// Tema: Formulario / Sumas y Series
// Resumen: Las sumas cerradas que mas se repiten
// Detalle: Las sumas cerradas que mas se repiten, cada una con sus primeros valores para
// reconocer el patron directamente en el ejemplo del enunciado: si la salida crece 1, 3, 6, 10,
// 15 es Gauss; 1, 4, 9, 16 son cuadrados; 1, 5, 14, 30 es suma de cuadrados; 1, 9, 36, 100 es
// suma de cubos. Identificar la sucesion en los casos de prueba suele ser mas rapido que
// derivar.

// =============== SUMAS Y SERIES ===============
//
// Gauss: suma de los primeros n enteros
//     1 + 2 + ... + n = n(n+1)/2
//     n     1  2  3  4  5  6  7  8  9 10 11 12
//     S(n)  1  3  6 10 15 21 28 36 45 55 66 78
//
// Suma de cuadrados
//     1^2 + 2^2 + ... + n^2 = n(n+1)(2n+1)/6
//     n      1   2   3   4   5   6   7   8   9  10  11  12
//     S(n)   1   5  14  30  55  91 140 204 285 385 506 650
//
// Suma de cubos = el cuadrado de la suma de Gauss
//     1^3 + 2^3 + ... + n^3 = [n(n+1)/2]^2
//     n       1    2    3    4    5    6    7    8    9   10   11   12
//     S(n)    1    9   36  100  225  441  784 1296 2025 3025 4356 6084
//
// Impares dan cuadrados perfectos, pares dan n(n+1)
//     1+3+5+...+(2n-1) = n^2        2+4+...+2n = n(n+1)
//     n         1   2   3   4   5   6   7   8   9  10  11  12
//     impares   1   4   9  16  25  36  49  64  81 100 121 144
//     pares     2   6  12  20  30  42  56  72  90 110 132 156
//
// Progresion aritmetica  (a, a+d, a+2d, ...)
//     termino k : a + (k-1)d
//     suma de n : n(2a + (n-1)d)/2 = n(primero + ultimo)/2
//
// Progresion geometrica  (a, ar, ar^2, ...)
//     termino k : a*r^(k-1)
//     suma de n : a(r^n - 1)/(r - 1)     si r != 1
//     suma inf  : a/(1 - r)              si |r| < 1
//     En modular /(r-1) es inverso modular; si r = 1 mod p no existe.
//
// Potencias de 2: la suma es la siguiente menos 1
//     1 + 2 + 4 + ... + 2^n = 2^(n+1) - 1
//     n       0    1    2    3    4    5    6    7    8    9   10   11   12
//     2^n     1    2    4    8   16   32   64  128  256  512 1024 2048 4096
//     suma    1    3    7   15   31   63  127  255  511 1023 2047 4095 8191
//
// Serie armonica  H(n) = 1 + 1/2 + ... + 1/n ~ ln(n) + 0.5772
//     H(10) ~ 2.93    H(100) ~ 5.19    H(10^6) ~ 14.39
//     Aparece al contar divisores: sum_{d=1..n} n/d ~ n*ln(n).
//
// Conteos sobre un arreglo de n elementos
//     pares i<j             : n(n-1)/2
//     pares ordenados i!=j  : n(n-1)
//     subarreglos contiguos : n(n+1)/2
//     subconjuntos          : 2^n        no vacios: 2^n - 1
//
// En C++  (todo O(1); dividir ANTES de multiplicar evita el overflow)
//     ll gauss(ll n) {                      // 1+2+...+n
//         return n % 2 ? (n+1)/2*n : n/2*(n+1);
//     }
//     ll sumaCuadrados(ll n) {              // 1^2+...+n^2
//         ll a = n, b = n+1, c = 2*n+1;
//         if (a % 2 == 0) a /= 2; else b /= 2;
//         if (a % 3 == 0) a /= 3;
//         else if (b % 3 == 0) b /= 3; else c /= 3;
//         return a * b * c;
//     }
//     ll sumaCubos(ll n) { ll g = gauss(n); return g * g; }
//     Con n = 10^9, gauss(n) = 500000000500000000 y cabe en long long;
//     pero n*(n+1) sin dividir primero YA se desborda.
//     Suma geometrica modular, O(log n):
//     ll sumaGeoMod(ll a, ll r, ll n) {     // a(r^n-1)/(r-1) mod M
//         if (r % M == 1) return a % M * (n % M) % M;
//         ll num = (modpow(r, n, M) - 1 + M) % M;
//         return a % M * num % M * modpow((r-1) % M, M-2, M) % M;
//     }
