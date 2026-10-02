// <3
// Tema: Formulario / Grafos, Esperanza y Calendario
// Resumen: Teoremas de grafos que se usan sin demostrar, valor esperado, y dia de la semana
// O: no aplica: son resultados para usar directo
// Detalle: Lo que no estaba en las otras fichas: los teoremas de grafos que convierten un
// problema raro en un matching o en una cuenta de grados, las reglas de valor esperado
// (la linealidad resuelve casi todo sin calcular distribuciones) y el dia de la semana de
// cualquier fecha. Lo numerico esta verificado corriendolo.

// =============== GRAFOS, ESPERANZA Y CALENDARIO ===============
//
// Grafos: grados y estructura
//     suma de grados          = 2 * aristas; la cantidad de nodos de grado impar es par
//     arbol                   n nodos, n-1 aristas, conexo y sin ciclos (2 de 3 bastan)
//     bosque                  componentes = n - aristas
//     bipartito               si y solo si no tiene ciclos de largo impar (2-colorear BFS)
//     planar                  aristas <= 3n - 6 (n >= 3); si tiene mas, no es planar
//     Euler (formula)         V - E + F = 2 en un planar conexo (F cuenta la cara externa)
//
// Grafos: caminos que pasan por todo
//     camino euleriano        conexo y 0 o 2 nodos de grado impar (empieza en un impar)
//     circuito euleriano      conexo y todos los grados pares
//     dirigido                entrada = salida en todos (circuito); o uno con salida-entrada
//                             = 1 (inicio) y otro con entrada-salida = 1 (fin) (camino)
//     Dirac (hamiltoniano)    n >= 3 y todo grado >= n/2 -> hay ciclo hamiltoniano
//
// Grafos: matching y coberturas (ver Flujo Maximo y Matching)
//     Konig (bipartito)       matching maximo = cubrimiento minimo de vertices
//     independiente maximo    = V - matching maximo (bipartito)
//     cubrir con aristas      minimo de aristas que tocan todo = V - matching (sin aislados)
//     Hall                    hay matching que cubre toda la izquierda si y solo si cada
//                             grupo S de la izquierda tiene >= |S| vecinos en total
//     caminos en un DAG       minimo de caminos disjuntos que cubren todo = n - matching
//     Dilworth                minimo de cadenas que cubren un orden = la anticadena maxima
//
// Grafos: contar arboles
//     Cayley                  arboles con n nodos etiquetados = n^(n-2)   (K4 -> 16)
//     Kirchhoff               arboles generadores de G = determinante de L sin una fila y
//                             su columna; L = grados en la diagonal menos la adyacencia
//                             (eliminacion gaussiana; mod p si el numero es enorme)
//     Erdos-Gallai            d1 >= ... >= dn es secuencia de grados de un grafo simple
//                             si (suma par) y para todo k = 1..n:
//                             d1+...+dk <= k(k-1) + min(d(k+1),k) + ... + min(dn,k)
//
// Valor esperado y probabilidad
//     linealidad              E[X + Y] = E[X] + E[Y] SIEMPRE, aunque no sean independientes
//     truco del indicador     E[cuantos cumplen] = suma de P(el i-esimo cumple)
//     producto                E[X * Y] = E[X] * E[Y] solo si son independientes
//     geometrica              intentos hasta el primer exito con prob p: E = 1/p
//     coleccionista           E[tiradas hasta ver los n valores] = n * (1 + 1/2 + ... + 1/n)
//                             (dado de 6 caras: 14.7 tiradas)
//     union                   P(A o B) = P(A) + P(B) - P(A y B)
//     Bayes                   P(A | B) = P(B | A) * P(A) / P(B)
//     DP de esperanza         E[estado] = costo + suma de p(siguiente) * E[siguiente];
//                             si un estado vuelve a si mismo: E = c + p*E -> despejar E
//     modulo p                respuesta P/Q se imprime como P * inverso(Q) mod p
//
// Dia de la semana (Sakamoto, calendario gregoriano; 0 = domingo ... 6 = sabado)
//     int diaSemana(int y, int m, int d) {
//         static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
//         if (m < 3) y--;
//         return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
//     }
//     diaSemana(2026, 10, 3) = 6 -> sabado     diaSemana(2000, 1, 1) = 6 -> sabado
