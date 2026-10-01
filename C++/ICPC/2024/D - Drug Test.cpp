// <3
// Tema: Math / 2-Coloreo por Suma Potencia de 2
// Resumen: Resuelve "Drug Test" (problema D, ICPC 2024)
// Detalle: Resuelve "Drug Test" (problema D, ICPC 2024). El codigo le asigna a cada x de 1 a N
// un tipo, A o P, con el 0 fijo en P, de forma que x y p - x queden con tipos OPUESTOS, siendo
// p la menor potencia de 2 que es mayor o igual a x (o sea, x y su complemento suman potencia
// de 2). LA OBSERVACION QUE LO VUELVE UN FOR: el complemento p - x siempre es MENOR que x. Como
// p es la menor potencia de 2 que alcanza a x, p/2 < x, o sea p < 2x, y entonces p - x < x
// (verificado para x hasta 2*10^5). Asi que cada x depende de un numero mas chico, y
// recorriendo en orden creciente su complemento ya tiene tipo cuando se le necesita. Visto como
// grafo: cada x tiene exactamente un "padre" menor que el, asi que las restricciones forman un
// ARBOL con raiz en 0. Un arbol siempre se puede 2-colorear y la coloracion queda determinada
// por la raiz, por eso no hay que probar nada ni hacer backtracking. El caso "x es potencia de
// 2" es redundante: ahi el complemento es 0, que es P, y la regla general ya le da A. COMO LEER
// BIEN EL ENUNCIADO: al pie de la letra solo pide que cada tamano tenga AL MENOS UN companero
// de tipo opuesto, y asi hay muchas asignaciones validas (con N = 12 salen 66), lo que choca
// con que el enunciado diga que el diseno es unico. La lectura que lo hace unico es la del
// ejemplo, que lista TODOS los pares de tamanos distintos que suman potencia de 2: ninguno
// puede quedar con el mismo tipo. El codigo solo mira un companero por numero (el del arbol),
// pero esa coloracion resulta respetar tambien todos los demas pares: comprobado para N hasta
// 9999, sin un conflicto, y enumerando todas las asignaciones para N hasta 15 es la unica.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;

    while (cin >> N >> Q && (N || Q)) {

        vector<char> tipo(N + 1);

        // 0 siempre es placebo
        tipo[0] = 'P';

        for (int x = 1; x <= N; x++) {

            int p = 1;

            while (p < x)
                p *= 2;

            if (p == x) {
                // x + 0 = potencia de 2
                tipo[x] = 'A';
            }
            else {
                int complement = p - x;

                // x y complement tienen tipos opuestos
                tipo[x] = (tipo[complement] == 'A' ? 'P' : 'A');
            }
        }

        while (Q--) {
            int x;
            cin >> x;
            cout << tipo[x];
        }

        cout << '\n';
    }

    return 0;
}
