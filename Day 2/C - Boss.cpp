// <3
// Tema: Graph / BFS
// Resuelve "Boss" (Maratona de Programacao da SBC 2013, problem C): en un organigrama de N
// empleados donde X maneja directamente a Y, la operacion "T A B" intercambia las POSICIONES
// que ocupan A y B dentro del organigrama (que nunca cambia), y "P E" pregunta la edad del jefe
// mas joven, directo o indirecto, de E.
// Guarda el grafo invertido rev[Y] = jefes directos de una posicion, y los arreglos
// empPos/posEmp para saber que empleado ocupa cada posicion despues de cada swap.
// Cada consulta hace BFS desde la posicion de E sobre rev, visita todas las posiciones jefe
// (ancestros) y se queda con la edad minima entre los empleados que hoy las ocupan.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, I;

    // El problema puede contener varios casos de prueba
    while (cin >> N >> M >> I) {

        // age[i] = edad del empleado i
        vector<int> age(N + 1);
        for (int i = 1; i <= N; i++)
            cin >> age[i];

        /*
            rev representa el grafo invertido.

            Si X maneja directamente a Y:
                    X -> Y

            entonces almacenamos:

                    rev[Y].push_back(X)

            porque durante una consulta queremos subir por la cadena
            de mando (buscar todos los jefes).
        */
        vector<vector<int>> rev(N + 1);

        for (int i = 0; i < M; i++) {
            int X, Y;
            cin >> X >> Y;
            rev[Y].push_back(X);
        }

        /*
            El grafo nunca cambia.

            Lo único que cambia es qué empleado ocupa cada posición
            dentro del organigrama.

            empPos[e] = posición donde está actualmente el empleado e.

            posEmp[p] = empleado que ocupa actualmente la posición p.
        */

        vector<int> empPos(N + 1);
        vector<int> posEmp(N + 1);

        // Inicialmente cada empleado está en su propia posición.
        for (int i = 1; i <= N; i++) {
            empPos[i] = i;
            posEmp[i] = i;
        }

        while (I--) {

            char op;
            cin >> op;

            // Cambio de posiciones
            if (op == 'T') {

                int A, B;
                cin >> A >> B;

                // Posiciones actuales de ambos empleados
                int posA = empPos[A];
                int posB = empPos[B];

                // Intercambiar las posiciones de los empleados
                swap(empPos[A], empPos[B]);

                // Actualizar qué empleado queda en cada posición
                swap(posEmp[posA], posEmp[posB]);
            }

            // Consulta
            else {

                int E;
                cin >> E;

                // Posición donde se encuentra actualmente el empleado E
                int start = empPos[E];

                vector<int> vis(N + 1, 0);
                queue<int> q;

                q.push(start);
                vis[start] = true;

                int ans = INT_MAX;

                /*
                    Hacemos BFS sobre el grafo invertido.

                    Desde la posición del empleado vamos visitando
                    todos los jefes (directos e indirectos).

                    Cada nodo del BFS representa una POSICIÓN.

                    Para conocer la edad del jefe debemos averiguar
                    qué empleado ocupa actualmente esa posición.
                */
                while (!q.empty()) {

                    int u = q.front();
                    q.pop();

                    // Revisar todos los jefes directos
                    for (int bossPos : rev[u]) {

                        if (vis[bossPos])
                            continue;

                        vis[bossPos] = true;
                        q.push(bossPos);

                        // Empleado que ocupa esa posición
                        int bossEmp = posEmp[bossPos];

                        // Actualizar la edad mínima encontrada
                        ans = min(ans, age[bossEmp]);
                    }
                }

                // Si nunca encontramos un jefe
                if (ans == INT_MAX)
                    cout << "*\n";
                else
                    cout << ans << "\n";
            }
        }
    }

    return 0;
}