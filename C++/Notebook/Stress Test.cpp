// <3
// Tema: Implementation / Stress Test (Encontrar el Caso que da WA)
// Resumen: Generador aleatorio + fuerza bruta + script que compara hasta hallar la diferencia
// O: no aplica: es un procedimiento, 5 minutos de armar
// Uso: gen.cpp (este archivo), brute.cpp, sol.cpp; correr el script de abajo en bash
// Detalle: Cuando da WA y no se ve por que, se deja de mirar el codigo y se le pide a la
// maquina el caso. Hace falta: (1) sol.cpp, la solucion que falla; (2) brute.cpp, la
// version mas TONTA posible, la que es obviamente correcta aunque sea O(2^n) o O(n^3);
// (3) gen.cpp, que imprime un caso al azar segun la semilla que recibe. El script corre
// los tres miles de veces y se detiene en la primera diferencia, mostrando la entrada.
// Lo que hace que funcione: n MUY chico (3 a 8) y valores en un rango CHICO (1 a 10). Asi
// salen repetidos, empates, ceros y casos borde solos, y el caso que falla se lee a ojo.
// Si con n chico nunca falla, subir n de a poco; si nunca falla con nada, el WA puede ser
// de formato (espacios, saltos de linea, decimales) o de un caso que el generador no arma.
// El script tambien atrapa RE (el programa revento) y TLE (timeout 2).
// Mientras uno arma esto en la maquina, los otros dos siguen pensando en papel.

#include <bits/stdc++.h>

using namespace std;

mt19937 rng;

int rnd(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

string rndStr(int n, char desde, char hasta)
{
    string s(n, desde);
    for (char &c : s) c = (char)rnd(desde, hasta);
    return s;
}

int main(int, char *argv[])
{
    rng.seed(atoi(argv[1]));                 // misma semilla -> mismo caso

    int n = rnd(1, 8);                       // CHICO: el caso que falla se lee a ojo
    printf("%d\n", n);
    for (int i = 0; i < n; i++) printf("%d ", rnd(1, 10));
    printf("\n");

    // Arbol al azar con n nodos (1-indexado): el padre de i es alguno anterior
    // vector<int> perm(n); iota(perm.begin(), perm.end(), 1);
    // shuffle(perm.begin(), perm.end(), rng);       // para que 1 no sea siempre la raiz
    // for (int i = 1; i < n; i++) printf("%d %d\n", perm[rnd(0, i - 1)], perm[i]);

    // Permutacion al azar
    // vector<int> p(n); iota(p.begin(), p.end(), 1); shuffle(p.begin(), p.end(), rng);

    // Cadena al azar con alfabeto CHICO para que haya repeticiones
    // printf("%s\n", rndStr(n, 'a', 'b').c_str());
    return 0;
}

/* ===================== stress.sh =====================  correr: bash stress.sh

g++ -O2 -o sol sol.cpp && g++ -O2 -o brute brute.cpp && g++ -O2 -o gen gen.cpp || exit
for i in $(seq 1 2000); do
    ./gen $i > in.txt
    timeout 2 ./sol < in.txt > out1.txt
    est=$?
    if [ $est -eq 124 ]; then echo "TLE con semilla $i"; cat in.txt; exit; fi
    if [ $est -ne 0 ];   then echo "RE con semilla $i";  cat in.txt; exit; fi
    ./brute < in.txt > out2.txt
    if ! diff -bq out1.txt out2.txt > /dev/null; then
        echo "DIFERENCIA con semilla $i"; cat in.txt
        echo "--- sol:";   cat out1.txt
        echo "--- brute:"; cat out2.txt
        exit
    fi
done
echo "2000 casos iguales"

diff -b ignora espacios de mas al final de linea. Si la salida tiene decimales, comparar
con tolerancia en un checker propio en vez de diff. En Windows: correrlo en Git Bash.
*/
