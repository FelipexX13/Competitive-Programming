// <3
// Tema: Formulario / Trucos de Bits
// Resumen: Identidades de bits con la situacion concreta en la que sirve cada una, que es la
// parte que no se deduce
// O: (1) cada truco, que es justamente la gracia
// Detalle: Identidades de bits con la situacion concreta en la que sirve cada una, que es la
// parte que no se deduce: n & (n-1) es "potencia de 2", n & -n es el avance del Fenwick, y el
// xor se usa porque a^a=0 deja solo lo que aparece un numero impar de veces. Los valores de los
// builtins estan verificados corriendo el codigo, no de memoria. La trampa mas cara de esta
// seccion: 1 << 40 da 0 porque el literal 1 es int; hay que escribir 1LL << 40.

// =============== TRUCOS DE BITS ===============
//
// Operar el bit k (k empieza en 0)
//     leer    : (n >> k) & 1
//     prender : n |= 1LL << k
//     apagar  : n &= ~(1LL << k)
//     voltear : n ^= 1LL << k
//     mascara de k bits en 1 : (1LL << k) - 1
//     OJO: 1 << 40 da 0 porque el 1 es int. Usa 1LL << 40.
//
// Identidades y para que sirve cada una
//     n & (n-1)   apaga el bit encendido mas bajo
//                 -> n & (n-1) == 0 dice si n es potencia de 2
//                 -> contar bits: while (n) { n &= n-1; c++; }
//     n & -n      deja SOLO el bit mas bajo (lowbit)
//                 -> es el avance del Fenwick tree: i += i & -i
//     n | (n+1)   prende el cero mas bajo
//     n & (n+1)   apaga la cola de unos del final
//     n ^ (n>>1)  codigo Gray: dos consecutivos difieren en 1 bit
//                 -> recorrer subconjuntos cambiando un elemento
//     a ^ a = 0   y  a ^ 0 = a
//                 -> el que aparece un numero impar de veces sale solo
//                 -> xor de rango [l,r] = pre[r] ^ pre[l-1]
//     a ^ b >= 0  a y b tienen el mismo signo
//
// Codigo Gray, primeros valores
//     i        0  1  2  3  4  5  6  7
//     i^(i>>1) 0  1  3  2  6  7  5  4
//     binario  000 001 011 010 110 111 101 100
//
// Builtins de GCC (verificados con x = 40 = 101000b)
//     __builtin_popcount(40) = 2    bits en 1
//     __builtin_ctz(40)      = 3    ceros al final = indice del lowbit
//     __builtin_clz(40)      = 26   ceros al inicio (sobre 32 bits)
//     __builtin_parity(7)    = 1    1 si la cantidad de bits es impar
//     Para long long agrega ll: __builtin_popcountll, __builtin_ctzll
//     PELIGRO: ctz y clz con n = 0 son comportamiento indefinido.
//     bit mas alto de n = 31 - clz(n) = floor(log2(n))
//     siguiente potencia de 2 >= n : 1 << (32 - clz(n-1))
//
// Subconjuntos
//     recorrer TODAS las submascaras de m (sin el vacio):
//         for (int s = m; s; s = (s-1) & m)
//     hacerlo para todas las mascaras cuesta 3^n, no 4^n
//     complemento dentro de n bits : m ^ ((1<<n) - 1)
//     recorrer los bits: for (b=0;b<n;b++) if (m >> b & 1) ...
//     agregar elemento b: m | (1<<b)   quitarlo: m & ~(1<<b)
//
// Desplazamientos como aritmetica
//     n << 1 = n*2        n << k = n * 2^k
//     n >> 1 = n/2  solo si n >= 0
//     OJO: >> redondea hacia abajo y la division hacia cero:
//         -7 >> 1 = -4    pero    -7 / 2 = -3
//
// Cuando conviene pensar en bitmask
//     n <= 20  -> DP sobre 2^n estados es viable (~10^6)
//     n <= 25  -> 2^n cabe, pero ya va justo
//     Estado tipico: dp[mascara] = mejor valor usando ese subconjunto.
//     Si el enunciado dice n <= 20, casi siempre es bitmask DP.
//     bitset<N> para cribas o DP booleana: 64 veces menos memoria y
//     opera and/or/shift de a 64 bits por vez.
