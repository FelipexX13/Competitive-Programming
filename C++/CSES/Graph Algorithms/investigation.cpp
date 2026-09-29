// <3
// Tema: CSES / Dijkstra con Cuatro Cantidades a la Vez
// Un solo Dijkstra que ademas del costo minimo lleva otras tres cosas: cuantos caminos minimos hay
// (modulo 1e9+7), el minimo de aristas de un camino minimo y el maximo.
// LA IDEA ES QUE LAS CUATRO SE PROPAGAN CON LA MISMA REGLA, mirando si la distancia MEJORA o EMPATA:
//   - si mejora: se reinicia todo copiando lo del nodo de donde se viene (caminos, y los conteos
//     de aristas mas uno)
//   - si empata: se ACUMULA, sumando los caminos y quedandose con el minimo y el maximo de aristas
// Ese "si mejora reinicio, si empata acumulo" es el patron general para colgar estadisticas de un
// Dijkstra, y sirve igual para contar caminos, sumar pesos o llevar cualquier cosa asociativa.
// El if (peso != distancia[actual]) continue descarta las entradas viejas de la cola, que es lo que
// permite usar priority_queue sin decrease-key. Sin el se procesarian nodos con distancias
// obsoletas y los acumulados saldrian mal, no solo lentos.
// Los caminos se cuentan modulo 1e9+7 porque pueden ser astronomicos, mientras que las distancias
// van en long long sin modulo: mezclar las dos cosas es el error clasico aqui.
// Solo funciona porque los pesos son no negativos, que es lo que garantiza que un nodo ya sacado de
// la cola no vuelva a mejorar. Con pesos negativos habria que irse a Bellman-Ford y la logica de
// acumulacion se complica.

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 1000000007;

    long long n, m;
    cin >> n >> m;

    vector<vector<pair<long long, long long>>> conexiones(n);

    for(long long i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        a--;
        b--;

        conexiones[a].push_back({b, c});
    }

    vector<long long> caminos(n, 0);
    vector<long long> distancia(n, LLONG_MAX);
    vector<long long> minvuelos(n, LLONG_MAX);
    vector<long long> maxvuelos(n, 0);

    priority_queue<
        pair<long long, long long>,
        vector<pair<long long, long long>>,
        greater<pair<long long, long long>>
    > cola;

    caminos[0] = 1;
    distancia[0] = 0;
    minvuelos[0] = 0;

    cola.push({0, 0});

    while(!cola.empty())
    {
        long long peso = cola.top().first;
        long long actual = cola.top().second;
        cola.pop();

        if(peso != distancia[actual])
        {
            continue;
        }

        for(pair<long long, long long> siguiente : conexiones[actual])
        {
            long long hacia = siguiente.first;
            long long cuanto = siguiente.second;

            long long nuevaDistancia = peso + cuanto;
            long long nuevosVuelos = minvuelos[actual] + 1;

            if(distancia[hacia] > nuevaDistancia)
            {
                distancia[hacia] = nuevaDistancia;
                caminos[hacia] = caminos[actual];

                minvuelos[hacia] = nuevosVuelos;
                maxvuelos[hacia] = maxvuelos[actual] + 1;

                cola.push({nuevaDistancia, hacia});
            }
            else if(distancia[hacia] == nuevaDistancia)
            {
                caminos[hacia] += caminos[actual];
                caminos[hacia] %= MOD;

                minvuelos[hacia] = min(minvuelos[hacia], nuevosVuelos);
                maxvuelos[hacia] = max(maxvuelos[hacia], maxvuelos[actual] + 1);
            }
        }
    }

    cout << distancia[n - 1] << " "
         << caminos[n - 1] << " "
         << minvuelos[n - 1] << " "
         << maxvuelos[n - 1] << '\n';

    return 0;
}