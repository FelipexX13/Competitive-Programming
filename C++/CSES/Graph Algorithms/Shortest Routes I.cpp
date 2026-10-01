// <3
// Tema: CSES / Dijkstra con Priority Queue
// Resumen: Dijkstra clasico en O(m log n) con priority_queue de minimos
// O: (m log n), Dijkstra con heap
// Detalle: Dijkstra clasico en O(m log n) con priority_queue de minimos. Los dos detalles que
// importan: la cola guarda el par (distancia, nodo) en ese orden para que ordene por distancia,
// y el if(dist > distancia[actual]) continue descarta las entradas viejas que quedaron en la
// cola cuando un nodo mejoro su distancia. Sin ese filtro no esta mal, pero se procesa basura.
// CUANDO USAR: camino minimo desde UN origen con pesos NO NEGATIVOS. Con un peso negativo
// Dijkstra da respuestas mal y hay que irse a Bellman-Ford. Si todos los pesos son iguales, BFS
// hace lo mismo mas rapido y sin cola de prioridad. Ojo con LLONG_MAX como infinito: si se suma
// algo se desborda. Aqui no pasa porque solo se compara, pero es el error clasico de esta
// plantilla.

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main()
{
    // INPUT
    long long n, m;
    cin >> n >> m;

    vector<vector<pair<long long, long long>>> matriz(n + 1);

    for(long long i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        matriz[a].push_back({b, c});
    }

    // OUTPUT
    vector<long long> distancia(n + 1, LLONG_MAX);
    priority_queue<pair<long long, long long>,
                   vector<pair<long long, long long>>,
                   greater<pair<long long, long long>>> cola;

    distancia[1] = 0;
    cola.push({0, 1});

    while(!cola.empty())
    {
        long long dist = cola.top().first;
        long long actual = cola.top().second;
        cola.pop();

        if(dist > distancia[actual])
            continue;

        for(auto vecino : matriz[actual])
        {
            long long siguiente = vecino.first;
            long long peso = vecino.second;

            if(distancia[actual] + peso < distancia[siguiente])
            {
                distancia[siguiente] = distancia[actual] + peso;
                cola.push({distancia[siguiente], siguiente});
            }
        }
    }

    for(long long i = 1; i < n+1; i++)
    {
        cout << distancia[i];
        if(i < n) cout << " ";
    }
    
    cout << endl;

    return 0;
}