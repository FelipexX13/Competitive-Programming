// <3
// Tema: Formulario / Checklist de Contest
// Resumen: Que revisar cuando da WA, TLE o RE, antes de enviar, y como elegir que resolver
// O: no aplica: es la lista para el momento en que algo sale mal
// Detalle: En reglas ICPC cada envio rechazado de un problema que al final se resuelve suma
// 20 minutos de penalizacion, y los problemas no resueltos no suman nada. Revisar 2 minutos
// antes de enviar sale mas barato que un WA. Las listas van en orden de probabilidad: lo de
// arriba es lo que mas veces resulto ser el error.

// =============== CHECKLIST DE CONTEST ===============
//
// Primeros 20 minutos
//     plantilla               uno la escribe y la compila; los otros leen problemas
//     cada problema leido     una linea en papel: que pide, y facil / medio / dificil
//     a los 20-30 minutos     mirar el marcador: lo que muchos ya resolvieron es facil
//     orden                   de mas resueltos a menos, nunca en orden de letra
//
// Durante el contest
//     teclado                 nunca quieto: uno escribe, los otros piensan EN PAPEL
//     30-40 min sin avanzar   explicarlo en voz alta a un companero, o cambiar
//     falla y no se ve        imprimirlo, revisarlo en papel y soltar el PC
//     ultima hora             terminar el mas cercano al AC; no empezar uno dificil
//
// Antes de enviar (2 minutos)
//     ejemplos                TODOS, comparados caracter por caracter
//     formato                 YES/Yes, espacios, salto de linea final, decimales
//     varios casos            reiniciar globales, vectores y contadores en CADA caso
//     bordes                  el caso mas chico, y uno del tamano maximo (tiempo)
//     overflow                long long si una suma o un producto pasa de 2*10^9
//     al enviar               sin cout de depuracion; problema y lenguaje correctos
//
// Dio WA (en este orden)
//     1. enunciado            releer: formato, "al menos" o "exactamente", 0/1-indexado
//     2. overflow             int*int, suma de n valores de 10^9, acumulador en int
//     3. casos borde          n = 1, todos iguales, ceros, negativos, valores maximos
//     4. varios casos         algo que no se reinicio entre un caso y el siguiente
//     5. tamanos              arreglo justo (off-by-one), variable sin inicializar
//     6. supuestos            grafo desconectado, aristas repetidas, lazos, desorden
//     7. decimales            comparar con EPS; imprimir con setprecision suficiente
//     8. nada de eso          STRESS TEST contra fuerza bruta (en Implementation)
//
// Dio TLE
//     1. complejidad          contra el n maximo (hoja de GATILLOS)
//     2. entrada rapida       sync_with_stdio(false), cin.tie(nullptr), "\n" no endl
//     3. copias               vector por VALOR en una recursion: pasarlo con &
//     4. estructuras          map donde alcanza un vector, o sort + binaria
//     5. por caso             memset de un arreglo enorme en cada caso de prueba
//     6. bucle infinito       un while que no termina (el stress test lo encuentra)
//     7. Python               pasarlo a C++
//
// Dio RE
//     1. indices              fuera del arreglo: tamano, off-by-one, negativo
//     2. division             por cero, o modulo por cero
//     3. vacio                top(), front(), back() o *begin() de algo vacio
//     4. pila                 arreglo grande dentro de una funcion: hacerlo global
//     5. recursion            DFS de 10^5-10^6 niveles: hacerla iterativa
//
// Atascados
//     a mano                  4 o 5 casos chicos resueltos en papel; buscar el patron
//     fuerza bruta            imprimir la respuesta de n = 1..15: la formula se ve
//     la cota de n            n <= 20 bitmask, n <= 5000 O(n^2): hoja de GATILLOS
//     al reves                binaria sobre la respuesta, consultas al reves, complemento
