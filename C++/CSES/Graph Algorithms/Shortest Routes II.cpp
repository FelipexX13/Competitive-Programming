// <3
// Tema: CSES / Dijkstra desde Cada Nodo
// Resumen: Distancias entre TODOS los pares resueltas con n Dijkstras, uno por nodo
// Detalle: Distancias entre TODOS los pares resueltas con n Dijkstras, uno por nodo, en vez del
// Floyd-Warshall que suele ser la respuesta esperada. Trae un atajo: si un nodo tiene grado 1,
// su unico camino al resto pasa por su vecino, asi que se copia la fila del vecino sumando el
// peso de esa arista y se ahorra un Dijkstra completo. CUANDO CADA UNO: Floyd-Warshall es
// O(n^3) y se escribe en tres lineas, asi que con n <= 500 es lo que uno hace. n Dijkstras es
// O(n*m log n), que gana cuando el grafo es DISPERSO (m del orden de n), y pierde feo si es
// denso. Tambien hay que recordar quedarse con la arista mas barata entre cada par y que Floyd
// aguanta pesos negativos sin ciclos negativos, mientras Dijkstra no.

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // INPUT
    long long n, m, q;
    cin >> n >> m >> q;

    vector<vector<pair<long long, long long>>> conexion(n);

    vector<vector<long long>> conexiondirecta(
        n, vector<long long>(n, LLONG_MAX));
    
    for(long long i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
    
        a--;
        b--;
    
        if(conexiondirecta[a][b] > c)
        {
            conexiondirecta[a][b] = c;
            conexiondirecta[b][a] = c;
        }
    }
    
    for(long long i = 0; i < n; i++)
    {
        for(long long j = i + 1; j < n; j++)
        {
            if(conexiondirecta[i][j] != LLONG_MAX)
            {
                conexion[i].push_back({j, conexiondirecta[i][j]});
                conexion[j].push_back({i, conexiondirecta[i][j]});
            }
        }
    }

    // OUTPUT
    vector<vector<long long>> camino(n, vector<long long>(n, -1));
    vector<bool> dijkstrados(n, false);

    for(long long x = 0; x < n; x++)
    {
        if(conexion[x].size() == 1)
        {
            long long z = conexion[x][0].first;
            long long distanciaXZ = conexion[x][0].second;

            if(!dijkstrados[z])
            {
                vector<long long> distancia(n, LLONG_MAX);

                priority_queue<
                    pair<long long, long long>,
                    vector<pair<long long, long long>>,
                    greater<pair<long long, long long>>
                > cola;

                distancia[z] = 0;
                cola.push({0, z});

                while(!cola.empty())
                {
                    long long distanciaActual = cola.top().first;
                    long long actual = cola.top().second;
                    cola.pop();

                    if(distanciaActual > distancia[actual])
                        continue;

                    for(auto vecino : conexion[actual])
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

                for(long long i = 0; i < n; i++)
                {
                    if(distancia[i] != LLONG_MAX)
                        camino[z][i] = distancia[i];
                }

                dijkstrados[z] = true;
            }

            for(long long i = 0; i < n; i++)
            {
                if(camino[z][i] != -1)
                    camino[x][i] = camino[z][i] + distanciaXZ;
            }

            camino[x][x] = 0;
            dijkstrados[x] = true;
        }
    }

    for(long long x = 0; x < n; x++)
    {
        if(!dijkstrados[x])
        {
            vector<long long> distancia(n, LLONG_MAX);

            priority_queue<
                pair<long long, long long>,
                vector<pair<long long, long long>>,
                greater<pair<long long, long long>>
            > cola;

            distancia[x] = 0;
            cola.push({0, x});

            while(!cola.empty())
            {
                long long distanciaActual = cola.top().first;
                long long actual = cola.top().second;
                cola.pop();

                if(distanciaActual > distancia[actual])
                    continue;

                for(auto vecino : conexion[actual])
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

            for(long long i = 0; i < n; i++)
            {
                if(distancia[i] != LLONG_MAX)
                    camino[x][i] = distancia[i];
            }

            dijkstrados[x] = true;
        }
    }

    // INPUT
    for(long long i = 0; i < q; i++)
    {
        long long a, b;
        cin >> a >> b;

        cout << camino[a - 1][b - 1] << '\n';
    }

    return 0;
}