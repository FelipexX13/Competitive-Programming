// <3
// Tema: CSES / Ciclo en Grafo Dirigido (DFS de Tres Colores)
// Resumen: Encontrar un ciclo en un grafo DIRIGIDO con DFS de tres colores
// O: (n + m), DFS de tres colores
// Detalle: Encontrar un ciclo en un grafo DIRIGIDO con DFS de tres colores: 0 = sin visitar, 1
// = en la pila (gris), 2 = terminado (negro). Hay ciclo si y solo si aparece una arista hacia
// un nodo GRIS, porque ese nodo es un ancestro en la rama actual. Una arista hacia un negro NO
// es ciclo: ese nodo ya se exploro entero por otra rama. Confundir gris con negro es EL error
// clasico aqui, y por eso el "visitado si/no" de los grafos no dirigidos no sirve. LO QUE HACE
// BIEN ESTE DFS ITERATIVO, y conviene copiarlo tal cual: la pila guarda el par (nodo, indice de
// la siguiente arista por mirar). Asi un nodo sigue gris hasta que se revisaron TODAS sus
// aristas, y solo ahi se vuelve negro. El DFS iterativo ingenuo (sacar el nodo de la pila
// apenas se visita, como en "Round Trip (Stack)") no sirve para colores, porque pierde el
// momento en que el nodo termina. El ciclo se reconstruye subiendo por anterior[] desde x hasta
// z, e invirtiendo. CUANDO USAR: detectar dependencias circulares, o como chequeo de que un
// grafo es un DAG antes de hacerle DP. Si solo hace falta saber SI hay ciclo, Kahn (ver "Course
// Schedule") es mas corto.

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;

    cin >> n >> m;

    vector<vector<long long>> matriz(n + 1);

    long long a, b;

    while (m--)
    {
        cin >> a >> b;
        matriz[a].push_back(b);
    }

    vector<long long> anterior(n + 1, -1);
    vector<long long> estado(n + 1, 0);

    for (long long i = 1; i <= n; i++)
    {
        if (estado[i] != 0) continue;

        stack<pair<long long, long long>> pila;

        estado[i] = 1;
        pila.push({i, 0});

        while (!pila.empty())
        {
            long long x = pila.top().first;
            long long posicion = pila.top().second;

            if (posicion == matriz[x].size())
            {
                estado[x] = 2;
                pila.pop();
                continue;
            }

            long long z = matriz[x][posicion];

            pila.top().second++;

            if (estado[z] == 0)
            {
                anterior[z] = x;
                estado[z] = 1;
                pila.push({z, 0});
            }
            else if (estado[z] == 1)
            {
                vector<long long> ciclo;

                ciclo.push_back(z);

                long long actual = x;

                while (actual != z)
                {
                    ciclo.push_back(actual);
                    actual = anterior[actual];
                }

                ciclo.push_back(z);
                reverse(ciclo.begin(), ciclo.end());

                cout << ciclo.size() << '\n';

                for (long long ciudad : ciclo)
                    cout << ciudad << ' ';

                cout << '\n';

                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}