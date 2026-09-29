// <3
// Tema: CSES / Orden Topologico (Kahn)
// Orden topologico con el algoritmo de Kahn: se meten a la cola los nodos con grado de entrada
// 0 (nadie los obliga a esperar), y cada vez que se saca uno se le "quita" la arista a sus
// vecinos; el que se queda sin prerrequisitos entra a la cola. El orden en que salen de la cola
// es un orden topologico valido.
// LO QUE HACE A KAHN MEJOR QUE EL DFS PARA ESTO: detecta el ciclo gratis. Si hay un ciclo, sus
// nodos nunca llegan a grado 0 y jamas entran a la cola, asi que al final orden tiene MENOS de n
// nodos. Esa sola comparacion (orden.size() != n) es todo el chequeo de IMPOSSIBLE.
// CUANDO USAR: prerrequisitos, dependencias, "en que orden se hacen las tareas", y como primer
// paso de cualquier DP sobre un DAG (ver "Game Routes" y "Longest Flight Route"). Si piden el
// orden lexicograficamente menor, se cambia la queue por una priority_queue de minimos y ya.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    vector<vector<long long>> conexiones(n);
    vector<long long> grado(n, 0);

    for(long long i = 0; i < m; i++)
    {
        long long a, b;
        cin >> a >> b;

        a--;
        b--;

        conexiones[a].push_back(b);
        grado[b]++;
    }

    queue<long long> cola;

    for(long long i = 0; i < n; i++)
    {
        if(grado[i] == 0)
        {
            cola.push(i);
        }
    }

    vector<long long> orden;

    while(!cola.empty())
    {
        long long actual = cola.front();
        cola.pop();

        orden.push_back(actual);

        for(long long siguiente : conexiones[actual])
        {
            grado[siguiente]--;

            if(grado[siguiente] == 0)
            {
                cola.push(siguiente);
            }
        }
    }

    if(orden.size() != n)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for(long long nodo : orden)
    {
        cout << nodo + 1 << ' ';
    }

    cout << '\n';

    return 0;
}