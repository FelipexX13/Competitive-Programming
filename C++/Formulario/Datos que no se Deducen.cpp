// <3
// Tema: Formulario / Datos que no se Deducen
// Resumen: Hechos sueltos que si no te los sabes no los inventas en media hora de competencia
// O: no aplica: son datos duros que hay que saberse
// Detalle: Hechos sueltos que si no te los sabes no los inventas en media hora de competencia:
// el xor de 1..n tiene periodo 4, el ultimo digito de a^b cicla cada 4, un numero es cuadrado
// perfecto si y solo si tiene una cantidad impar de divisores, y la cantidad de nodos de grado
// impar de cualquier grafo siempre es par. Las tablas de xor y de ultimo digito estan
// verificadas corriendo el codigo.

// =============== DATOS QUE NO SE DEDUCEN ===============
//
// XOR de 1 hasta n  (verificado)
//     n % 4 == 0  ->  n
//     n % 4 == 1  ->  1
//     n % 4 == 2  ->  n + 1
//     n % 4 == 3  ->  0
//     n      : 1  2  3  4  5  6  7  8  9 10 11 12
//     1^..^n : 1  3  0  4  1  7  0  8  1 11  0 12
//     Xor de un rango [l,r] = f(r) ^ f(l-1)
//
// Reglas de divisibilidad
//     2  : ultimo digito par          5 : termina en 0 o 5
//     3  : suma de digitos div 3      9 : suma de digitos div 9
//     4  : los ultimos 2 digitos      8 : los ultimos 3 digitos
//     6  : divisible por 2 y por 3
//     11 : suma alternada de digitos divisible por 11
//     7  : no hay regla comoda; saca el modulo digito a digito (Horner)
//
// Ultimo digito de a^b: el ciclo dura a lo sumo 4  (verificado)
//     2: 2 4 8 6      3: 3 9 7 1      7: 7 9 3 1      8: 8 4 2 6
//     4: 4 6          9: 9 1          5: 5            6: 6
//     0: 0            1: 1
//     Entonces a^b mod 10 depende de b mod 4, tratando b = 0 aparte.
//
// Cantidad de digitos
//     digitos de n = floor(log10(n)) + 1   para n >= 1
//     Mas seguro sin flotantes: to_string(n).size()
//     digitos de n! = suma de log10(i) para i=1..n, redondeado arriba
//
// Josephus: n en circulo, se elimina cada k-esima persona
//     k = 2 : escribe n = 2^m + L, la respuesta es 2L + 1
//             equivale a rotar a la izquierda el bit mas alto de n
//     k general (0-indexado):
//         J = 0; for (i = 2; i <= n; i++) J = (J + k) % i;
//         la respuesta 1-indexada es J + 1
//
// Principio del palomar
//     n+1 objetos en n cajas -> alguna caja tiene 2 o mas
//     Entre n+1 numeros cualesquiera de 1..2n hay dos consecutivos
//     Con n+1 prefijos y n residuos, dos comparten residuo
//         -> siempre existe un subarreglo con suma divisible por n
//
// Grafos: hechos que se olvidan
//     arbol de n nodos: exactamente n-1 aristas y ningun ciclo
//     grafo completo de n nodos: n(n-1)/2 aristas
//     suma de todos los grados = 2 * cantidad de aristas
//     la cantidad de nodos de grado impar siempre es PAR
//     camino euleriano existe si hay 0 o 2 nodos de grado impar
//     ciclo euleriano existe si todos los grados son pares
//     arboles etiquetados con n nodos: n^(n-2)  (Cayley)
//     un grafo bipartito no tiene ciclos de longitud impar
//
// Varios que aparecen disfrazados
//     ceros al final de n! = n/5 + n/25 + n/125 + ...
//     n es cuadrado perfecto <=> tiene una cantidad IMPAR de divisores
//         (de ahi el problema clasico de los casilleros que se abren)
//     suma de los primeros n impares = n^2
//     la mediana minimiza la suma de distancias absolutas
//     el promedio minimiza la suma de distancias al cuadrado
//     para repartir en dos grupos lo mas parejo posible: subset sum
//     (a+b) % m = ((a%m) + (b%m)) % m , igual con el producto,
//     pero NO con la division: ahi va el inverso modular
//
// En C++
//     ll xorHasta(ll n) {                   // 1^2^...^n en O(1)
//         switch (n % 4) {
//             case 0: return n;
//             case 1: return 1;
//             case 2: return n + 1;
//         }
//         return 0;
//     }
//     xor del rango [l,r] = xorHasta(r) ^ xorHasta(l-1)
//     int josephus(int n, int k) {          // O(n), 1-indexado
//         int j = 0;
//         for (int i = 2; i <= n; i++) j = (j + k) % i;
//         return j + 1;
//     }
//     int josephus2(int n) {                // caso k=2 en O(1)
//         return 2 * (n - (1 << (31 - __builtin_clz(n)))) + 1;
//     }
//     int numDigitos(ll n) {                // sin log10, sin error de flotante
//         int d = 0;
//         while (n) d++, n /= 10;
//         return d ? d : 1;
//     }
