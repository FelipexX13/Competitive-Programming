// <3
// Tema: Formulario / Cotas y Limites
// La tabla que se mira ANTES de escribir codigo: dado el n del enunciado, que
// complejidad cabe en el tiempo limite, hasta donde llega cada tipo entero y cuanta
// memoria ocupa un arreglo. Leer n <= 20 y pensar en bitmask, o n <= 450 y pensar en
// Floyd-Warshall, ahorra media hora de rumbo equivocado.

// =============== COTAS Y LIMITES PRACTICOS ===============
//
// n maximo que aguanta cada complejidad (~10^8 operaciones, 1 seg)
//     O(n!)        n <= 11
//     O(2^n * n)   n <= 20
//     O(2^n)       n <= 25
//     O(n^3)       n <= 450
//     O(n^2 log n) n <= 5000
//     O(n^2)       n <= 10^4
//     O(n sqrt n)  n <= 10^5
//     O(n log^2 n) n <= 10^5
//     O(n log n)   n <= 10^6
//     O(n)         n <= 10^8
//     Si n <= 10^18 la respuesta es formula cerrada, log o binaria.
//
// Rangos de los enteros
//     int                 hasta 2147483647  (~2.1*10^9)
//     unsigned int        hasta 4294967295
//     long long           hasta 9223372036854775807
//     unsigned long long  hasta 18446744073709551615
//     __int128            hasta ~1.7*10^38  (no se imprime con cout)
//     ~9.2*10^18 es el techo de long long: dos numeros de 10^9
//     multiplicados caben, tres no.
//
// Precision de punto flotante
//     float   ~7 digitos significativos
//     double  ~15-16 digitos  (usar siempre este)
//     long double ~18-19 en GCC
//     Comparar con EPS: fabs(a-b) < 1e-9, nunca a == b
//     Si el problema pide enteros exactos, evitar sqrt y pow.
//
// Modulos comunes
//     1000000007  (10^9+7) primo, el mas usado
//     998244353   primo, el de NTT (= 119*2^23 + 1)
//     1000000009  primo
//     Con 10^9+7 dos residuos multiplicados llegan a ~10^18:
//     cabe en long long, pero sumar tres productos sin reducir NO.
//
// Tamanos de memoria (limite tipico 256 MB)
//     int[10^7]        40 MB      long long[10^7]   80 MB
//     int[10^8]       400 MB  (no cabe)
//     bool[10^8]      100 MB      bitset<10^8>      12.5 MB
//     vector<vector<int>> de 10^4 x 10^4 = 400 MB, no cabe
