// <3
// Tema: CSES / DP sobre DAG en Orden Topologico
// Resumen: Contar caminos de 1 a n en un DAG: caminos[v] = suma de caminos[u] sobre las aristas
// u -> v
// Detalle: Contar caminos de 1 a n en un DAG: caminos[v] = suma de caminos[u] sobre las aristas
// u -> v. La recurrencia es obvia; lo que la hace correcta es el ORDEN: hay que procesar un
// nodo solo cuando ya se sumaron TODOS sus predecesores, y eso es exactamente lo que garantiza
// recorrer en orden topologico con Kahn. Cuando grado[v] llega a 0, caminos[v] ya esta
// completo. El detalle de arranque: solo caminos[0] = 1. Los otros nodos que tambien empiezan
// con grado 0 entran a la cola igual, pero con 0 caminos, asi que empujan ceros y no contaminan
// la cuenta: solo cuentan los caminos que salen del nodo 1. CUANDO USAR: cualquier "cuantas
// formas", "camino mas largo", "camino mas barato" sobre un grafo SIN ciclos. En un DAG todas
// esas son una DP en orden topologico, O(n + m). Con ciclos contar caminos puede ser infinito,
// y el camino mas largo pasa a ser NP-dificil.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 1000000007;

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

    vector<long long> caminos(n, 0);
    queue<long long> cola;

    caminos[0] = 1;

    for(long long i = 0; i < n; i++)
    {
        if(grado[i] == 0)
        {
            cola.push(i);
        }
    }

    while(!cola.empty())
    {
        long long actual = cola.front();
        cola.pop();

        for(long long siguiente : conexiones[actual])
        {
            caminos[siguiente] += caminos[actual];
            caminos[siguiente] %= MOD;

            grado[siguiente]--;

            if(grado[siguiente] == 0)
            {
                cola.push(siguiente);
            }
        }
    }

    cout << caminos[n - 1] << '\n';

    return 0;
}