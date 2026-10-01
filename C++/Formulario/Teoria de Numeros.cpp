// <3
// Tema: Formulario / Teoria de Numeros
// Resumen: Divisores, phi, gcd, aritmetica modular y CRT, con las tablas hasta 20 para revisar
// a mano un caso chico
// Detalle: Divisores, phi, gcd, aritmetica modular y CRT, con las tablas hasta 20 para revisar
// a mano un caso chico. La mitad de los problemas de numeros se resuelven sabiendo que d(n),
// sigma(n) y phi(n) salen directo de la factorizacion, y que en modular dividir significa
// multiplicar por el inverso.

// =============== TEORIA DE NUMEROS ===============
//
// Con la factorizacion n = p1^a1 * p2^a2 * ...
//     cantidad de divisores  d(n)     = (a1+1)(a2+1)...
//     suma de divisores      sigma(n) = prod (p^(a+1)-1)/(p-1)
//     funcion de Euler       phi(n)   = n * prod (1 - 1/p)
//     Ejemplo n=12=2^2*3 : d=3*2=6, sigma=7*4=28, phi=12*(1/2)(2/3)=4
//
// Tablas hasta 20
//     n       1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
//     d(n)    1  2  2  3  2  4  2  4  3  4  2  6  2  4  4  5  2  6  2  6
//     sig(n)  1  3  4  7  6 12  8 15 13 18 12 28 14 24 24 31 18 39 20 42
//     phi(n)  1  1  2  2  4  2  6  4  6  4 10  4 12  6  8  8 16  6 18  8
//
// gcd y lcm
//     gcd(a,b) * lcm(a,b) = a*b      (dividir antes de multiplicar)
//     gcd(a,b) = gcd(b, a mod b)     Euclides
//     gcd(F(m), F(n)) = F(gcd(m,n))  Fibonacci
//     a y b coprimos  <=>  gcd(a,b) = 1
//
// Modular
//     Fermat  : a^(p-1) = 1 mod p      si p primo y p no divide a
//     inverso : a^(p-2) mod p          si p primo
//     Euler   : a^phi(m) = 1 mod m     si gcd(a,m) = 1
//     Wilson  : (p-1)! = -1 mod p      si y solo si p es primo
//     (a/b) mod p = a * b^(p-2) mod p
//     OJO: restar en modular siempre ((a-b) % m + m) % m
//
// Teorema chino del resto (CRT)
//     x = r1 mod m1, x = r2 mod m2, con m1, m2 coprimos
//     -> solucion unica modulo m1*m2
//
// Legendre: exponente de p en n!
//     e = n/p + n/p^2 + n/p^3 + ...   (divisiones enteras)
//     Sirve para contar ceros finales de n! (exponente de 5).
//
// Primos menores que 100  (hay 25)
//      2  3  5  7 11 13 17 19 23 29 31 37
//     41 43 47 53 59 61 67 71 73 79 83 89
//     97
//
// Criba: O(n log log n). Cantidad de primos ~ n/ln(n).
//     hasta 10^3 hay 168     hasta 10^6 hay 78498
//     hasta 10^4 hay 1229    hasta 10^7 hay 664579
//     hasta 10^5 hay 9592    hasta 10^9 hay ~5.08*10^7
//
// En C++  (factorizar en O(sqrt n) da los tres de una)
//     ll numDivisores(ll n) {
//         ll r = 1;
//         for (ll p = 2; p*p <= n; p++) if (n % p == 0) {
//             ll e = 0; while (n % p == 0) n /= p, e++;
//             r *= e + 1;
//         }
//         if (n > 1) r *= 2;                // quedo un primo grande
//         return r;
//     }
//     ll sumaDivisores(ll n) {
//         ll r = 1;
//         for (ll p = 2; p*p <= n; p++) if (n % p == 0) {
//             ll t = 1, q = 1;
//             while (n % p == 0) n /= p, q *= p, t += q;
//             r *= t;
//         }
//         if (n > 1) r *= 1 + n;
//         return r;
//     }
//     ll phi(ll n) {
//         ll r = n;
//         for (ll p = 2; p*p <= n; p++) if (n % p == 0) {
//             while (n % p == 0) n /= p;
//             r -= r / p;
//         }
//         if (n > 1) r -= r / n;
//         return r;
//     }
//     ll modpow(ll b, ll e, ll m) {         // O(log e)
//         ll r = 1; b %= m;
//         while (e) { if (e & 1) r = r*b % m; b = b*b % m; e >>= 1; }
//         return r;
//     }
//     inverso modular con m primo: modpow(a, m-2, m)
//     ll legendre(ll n, ll p) {             // exponente de p en n!
//         ll e = 0;
//         for (ll q = p; q <= n; q *= p) e += n / q;
//         return e;
//     }
//     Criba lineal, O(n): cada compuesto se tacha UNA sola vez.
//     vector<int> criba(int n) {
//         vector<int> pr; vector<char> c(n+1, 1); c[0] = c[1] = 0;
//         for (int i = 2; i <= n; i++) {
//             if (c[i]) pr.push_back(i);
//             for (int p : pr) {
//                 if ((ll)i*p > n) break;
//                 c[i*p] = 0;
//                 if (i % p == 0) break;
//             }
//         }
//         return pr;
//     }
