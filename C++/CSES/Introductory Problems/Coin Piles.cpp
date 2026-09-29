// <3
// Tema: CSES / Invariantes Aritmeticos
// Sin simular nada: dos condiciones cerradas. Cada movimiento quita 3 monedas en total, asi que
// (a+b) tiene que ser divisible por 3. Y cada movimiento quita al menos 1 de cada pila, asi que
// ninguna puede ser mas del DOBLE de la otra, max(a,b) <= 2*min(a,b). Las dos juntas son
// suficientes.
// COMO SE LLEGA A ESO: buscar que cantidad se conserva o cambia de forma fija en cada movimiento.
// Aqui el total baja de 3 en 3 (invariante de divisibilidad) y la diferencia entre pilas esta
// acotada (invariante de desigualdad).
// CUANDO USAR: el problema pregunta si un estado es ALCANZABLE, con t casos grandes que hacen
// imposible simular. Buscar el invariante es lo que convierte una simulacion en un par de ifs.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long a, b;
        cin >> a >> b;

        if ((a + b) % 3 == 0 && max(a, b) <= 2 * min(a, b))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
