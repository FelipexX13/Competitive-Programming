// <3
// Tema: CSES / Construccion por Bloques de 4
// Resumen: La suma total es n*(n+1)/2, y para partirla en dos mitades iguales tiene que ser PAR
// Detalle: La suma total es n*(n+1)/2, y para partirla en dos mitades iguales tiene que ser
// PAR, lo que solo pasa si n mod 4 es 0 o 3. Ese es todo el criterio de imposibilidad. La
// construccion aprovecha que cuatro consecutivos se parten perfecto: {i, i+3} y {i+1, i+2}
// suman lo mismo. Con n mod 4 == 0 se cubre todo asi; con n mod 4 == 3 sobran los tres
// primeros, que se acomodan a mano como {1,2} contra {3} y desde el 4 siguen los bloques.
// CUANDO USAR: reparticiones en grupos de suma igual. Lo primero es siempre la condicion de
// paridad o divisibilidad de la suma total, que descarta los imposibles de una; despues se
// busca el bloque chico que se parte solo y se repite.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n % 4 == 1 || n % 4 == 2) {
        cout << "NO\n";
        return 0;
    }

    vector<int> a, b;

    if (n % 4 == 3) {
        a.push_back(1);
        a.push_back(2);
        b.push_back(3);

        for (int i = 4; i <= n; i += 4) {
            a.push_back(i);
            a.push_back(i + 3);
            b.push_back(i + 1);
            b.push_back(i + 2);
        }
    } else {
        for (int i = 1; i <= n; i += 4) {
            a.push_back(i);
            a.push_back(i + 3);
            b.push_back(i + 1);
            b.push_back(i + 2);
        }
    }

    cout << "YES\n";

    cout << a.size() << '\n';
    for (int x : a) cout << x << ' ';
    cout << '\n';

    cout << b.size() << '\n';
    for (int x : b) cout << x << ' ';
    cout << '\n';
}
