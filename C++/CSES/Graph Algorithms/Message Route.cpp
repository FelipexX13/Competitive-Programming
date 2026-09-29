// <3
// Tema: CSES / BFS de Camino Minimo con Reconstruccion
// Mismo patron que Labyrinth pero en grafo general: BFS desde n hacia 1 guardando siguiente[] y
// la distancia en cuantos[]. Arrancar del destino tiene su gracia: los punteros ya quedan
// apuntando hacia adelante y el camino se imprime directo, sin invertir nada.
// El cuantos[] hace doble trabajo, de contador de pasos y de marca de visitado (0 = no visto),
// que es un truco comun para no llevar dos arreglos.
// CUANDO USAR: grafo sin pesos y hay que devolver el camino, no solo su largo. Si el grafo
// tuviera pesos, esto mismo pero con Dijkstra.

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

    vector<vector<long long>> vecinos(n + 1);

    long long a, b;

    while(m--)
    {
        cin >> a >> b;

        vecinos[a].push_back(b);
        vecinos[b].push_back(a);
    }

    vector<long long> siguiente(n + 1, -1);
    vector<long long> cuantos(n + 1, 0);

    queue<long long> cola;

    cola.push(n);
    cuantos[n] = 1;

    while(!cola.empty())
    {
        long long actual = cola.front();
        cola.pop();

        if(actual == 1)
        {
            break;
        }

        for(long long vecino : vecinos[actual])
        {
            if(cuantos[vecino] == 0)
            {
                siguiente[vecino] = actual;
                cuantos[vecino] = cuantos[actual] + 1;
                cola.push(vecino);
            }
        }
    }

    if(cuantos[1] == 0)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << cuantos[1] << '\n';

    long long actual = 1;

    while(actual != n)
    {
        cout << actual << ' ';
        actual = siguiente[actual];
    }

    cout << n << '\n';

    return 0;
}