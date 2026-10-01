// <3
// Tema: CSES / K Caminos Mas Cortos
// Resumen: Los k caminos mas cortos al nodo n, con la variante de Dijkstra que en vez de UNA
// distancia por nodo guarda...
// Detalle: Los k caminos mas cortos al nodo n, con la variante de Dijkstra que en vez de UNA
// distancia por nodo guarda las k mejores en un priority_queue de maximos por nodo. Cada nodo
// se puede sacar de la cola hasta k veces, y ahi esta la clave: la k-esima vez que un nodo sale
// de la cola, sale con su k-esima distancia mas corta. Por eso el contador usados[] y el corte
// cuando pasa de k. El priority_queue de MAXIMOS por nodo es para poder botar el peor de los k
// que se llevan cuando llega uno mejor. Es un heap acotado a tamano k. CUANDO USAR: "los k
// caminos mas cortos", "el k-esimo mas corto", con repeticiones permitidas. Costo O(k*m*log).
// Ojo que aqui los caminos pueden repetir nodos; si el problema pide caminos DISJUNTOS o
// simples, esto no sirve y el problema es muchisimo mas duro.

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<long long, long long>>> conexion(n);

    for(long long i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        conexion[--a].push_back({--b, c});
    }

    vector<priority_queue<long long>> distancia(n);
    vector<long long> usados(n, 0);

    priority_queue<
        pair<long long, long long>,
        vector<pair<long long, long long>>,
        greater<pair<long long, long long>>
    > cola;

    distancia[0].push(0);
    cola.push({0, 0});

    while(!cola.empty())
    {
        long long costo = cola.top().first;
        long long actual = cola.top().second;
        cola.pop();

        usados[actual]++;

        if(usados[actual] > k)
            continue;

        for(auto vecino : conexion[actual])
        {
            long long siguiente = vecino.first;
            long long peso = vecino.second;

            long long nuevoCosto = costo + peso;

            if(distancia[siguiente].size() < k)
            {
                distancia[siguiente].push(nuevoCosto);
                cola.push({nuevoCosto, siguiente});
            }
            else if(nuevoCosto < distancia[siguiente].top())
            {
                distancia[siguiente].pop();
                distancia[siguiente].push(nuevoCosto);
                cola.push({nuevoCosto, siguiente});
            }
        }
    }

    vector<long long> respuesta;

    while(!distancia[n - 1].empty())
    {
        respuesta.push_back(distancia[n - 1].top());
        distancia[n - 1].pop();
    }

    for(long long i = respuesta.size() - 1; i >= 0; i--)
        cout << respuesta[i] << ' ';

    cout << '\n';

    return 0;
}