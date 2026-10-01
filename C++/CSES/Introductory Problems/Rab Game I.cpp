// <3
// Tema: CSES / Construccion por Rotacion de Bloque
// Resumen: Construccion con dos condiciones de imposibilidad
// O: (n), rotar un bloque
// Detalle: Construccion con dos condiciones de imposibilidad: a + b no puede pasar de n, y a y
// b tienen que ser cero los dos o ninguno, que es lo que verifica (a == 0) != (b == 0). La
// primera fila es la identidad. La segunda rota un bloque de tamano a+b: se sacan los a
// primeros y se ponen al final del bloque, y lo que queda despues de m se deja igual. Eso deja
// exactamente las coincidencias pedidas en cada lado. CUANDO USAR: "construya un ejemplo con
// exactamente X de esto y Y de aquello". El metodo es siempre el mismo, primero las condiciones
// que hacen imposible el caso, y despues un bloque chico que se manipula dejando el resto
// intacto. Rotar es la operacion mas util porque controla las coincidencias de forma exacta.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;

        if (a + b > n || (a == 0) != (b == 0)) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";

        for (int i = 1; i <= n; i++)
            cout << i << ' ';
        cout << '\n';

        int m = a + b;

        for (int i = a + 1; i <= m; i++)
            cout << i << ' ';

        for (int i = 1; i <= a; i++)
            cout << i << ' ';

        for (int i = m + 1; i <= n; i++)
            cout << i << ' ';

        cout << '\n';
    }
}
