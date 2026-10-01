// <3
// Tema: Graph / BFS sobre Grafo Producto (dos fichas a la vez)
// Resumen: Hay que mover DOS posiciones a la vez por un grafo dirigido y llegar a una
// configuracion objetivo
// Detalle: Resuelve "Infiltration Route" (problema I, Regionals 2025): hay que mover DOS
// posiciones a la vez por un grafo dirigido y llegar a una configuracion objetivo. LA TECNICA
// ES EL GRAFO PRODUCTO: el estado no es un nodo sino un PAR (p1, p2), mas alguna bandera extra
// segun lo que pida el problema. El BFS corre sobre esos estados, y desde cada uno se ramifica
// moviendo una ficha o la otra. Con n nodos son n^2 estados, lo que acota n a unos pocos
// cientos, y por eso MAXN es 505. CUANDO USARLO: cualquier problema con dos entidades que se
// mueven y que interactuan (dos robots que no pueden chocar, un perseguidor y un perseguido,
// dos tokens que deben encontrarse). Si las entidades fueran independientes se resolverian por
// separado; el grafo producto es justamente para cuando NO lo son. El BFS da el camino minimo
// porque todos los movimientos cuestan lo mismo, y la reconstruccion se hace guardando de que
// estado se vino, igual que en un BFS normal pero con el estado compuesto. El toclear sirve
// para limpiar solo lo que se toco entre casos, en vez de reiniciar los n^2 estados enteros:
// util cuando hay muchos casos de prueba y el grafo es grande. OJO: usa structured bindings
// (auto [a, b]), que piden C++17. En el juez compila, pero con un g++ viejo hay que volver a
// .first y .second.

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

bool seen[MAXN][MAXN][2];
array<int, 3> bck[MAXN][MAXN][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(2 * n);

    for (int i = 0; i < m; i++) {
        int s, t;
        cin >> s >> t;

        --s;
        --t;

        adj[s].push_back(t);
    }

    bool can = false;
    vector<int> route;

    queue<array<int, 3>> q;
    vector<array<int, 3>> toclear;

    /*
        cross = unica arista que pasa de:

            [0 ... n-1]

        a:

            [n ... 2n-1]
    */

    for (int cross = n + 1; cross < 2 * n && !can; cross++) {

        q.push({0, cross - n, 0});

        seen[0][cross - n][0] = true;

        bck[0][cross - n][0] = {
            -1, -1, 0
        };

        while (!q.empty()) {

            auto [p1, p2, t] = q.front();
            q.pop();

            toclear.push_back({p1, p2, t});

            // ------------------------------------------------
            // Mover p1
            // ------------------------------------------------

            if (p1 < p2 && t == 0) {

                for (auto v : adj[p1]) {

                    if (v < n && v != p2) {

                        if (!seen[v][p2][0]) {

                            seen[v][p2][0] = true;

                            bck[v][p2][0] = {
                                p1, p2, t
                            };

                            q.push({v, p2, 0});
                        }
                    }
                }
            }

            // ------------------------------------------------
            // Mover p2
            // ------------------------------------------------

            if (t == 1 || (t == 0 && p1 < p2)) {

                for (auto v : adj[n + p2]) {

                    int np2 = v - n;

                    if (np2 != p1) {

                        if (!seen[p1][np2][1]) {

                            seen[p1][np2][1] = true;

                            bck[p1][np2][1] = {
                                p1, p2, t
                            };

                            q.push({p1, np2, 1});
                        }
                    }
                }
            }

            // ------------------------------------------------
            // Caso p1 > p2
            // ------------------------------------------------

            else if (t == 0 && p1 > p2) {

                for (auto v : adj[n + p2]) {

                    int np2 = v - n;

                    if (np2 != p1) {

                        if (!seen[p1][np2][t]) {

                            seen[p1][np2][t] = true;

                            bck[p1][np2][t] = {
                                p1, p2, t
                            };

                            q.push({p1, np2, t});
                        }
                    }
                }
            }
        }

        // ----------------------------------------------------
        // Buscamos:
        //
        // p1 = bc
        // p2 = n-1
        //
        // y la arista bc -> cross.
        // ----------------------------------------------------

        for (int bc = 0; bc < n - 1 && !can; bc++) {

            for (int t = 0; t <= 1 && !can; t++) {

                if (!seen[bc][n - 1][t])
                    continue;

                for (auto v : adj[bc]) {

                    if (v != cross)
                        continue;

                    can = true;

                    // ------------------------------------------------
                    // Reconstruir
                    // ------------------------------------------------

                    array<int, 3> cur = {
                        bc,
                        n - 1,
                        t
                    };

                    while (cur[0] != -1) {

                        route.push_back(cur[0]);
                        route.push_back(n + cur[1]);

                        cur =
                            bck[cur[0]][cur[1]][cur[2]];
                    }

                    sort(route.begin(), route.end());

                    route.erase(
                        unique(route.begin(), route.end()),
                        route.end()
                    );

                    break;
                }
            }
        }

        // ----------------------------------------------------
        // Limpiar solamente los estados visitados
        // ----------------------------------------------------

        for (auto [u, v, t] : toclear) {

            seen[u][v][t] = false;

            bck[u][v][t] = {
                0, 0, 0
            };
        }

        toclear.clear();
    }

    if (can) {

        cout << route.size() << '\n';

        for (int x : route)
            cout << x + 1 << ' ';

        cout << '\n';

    } else {

        cout << "*\n";
    }

    return 0;
}
