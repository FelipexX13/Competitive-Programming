// <3
// Tema: CSES / Construccion Directa
// En vez de buscar, se CONSTRUYE: primero todos los pares y despues todos los impares. Dos
// numeros de la misma paridad difieren en al menos 2, asi que dentro de cada mitad no hay
// problema, y en la frontera se juntan el ultimo par con el 1, que para n >= 4 tambien difieren
// en mas de 1.
// LOS CASOS IMPOSIBLES: n = 2 y n = 3 no tienen solucion y hay que responderlo aparte. n = 1 si
// la tiene (un solo numero, sin vecinos que comparar), y confundirse ahi es el error tipico.
// CUANDO PENSAR EN CONSTRUCCION: el enunciado dice "imprima CUALQUIER solucion" o "muestre una
// que cumpla". Eso casi siempre significa que existe un patron y que buscar con backtracking es
// perder el tiempo. Y conviene mirar los n chicos a mano: ahi salen los casos imposibles.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 2 || n == 3) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    for (int i = 2; i <= n; i += 2)
        cout << i << ' ';

    for (int i = 1; i <= n; i += 2)
        cout << i << ' ';

    cout << '\n';
}
