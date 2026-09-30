// <3
// Tema: Graph / Quitar el DAG de Rutas Minimas
// O: (m log n), dos Dijkstra mas un barrido del DAG
// Uso: leer el grafo dirigido, s y d; imprime la ruta mas corta que NO usa ninguna arista minima
// Resuelve "Almost Shortest Path" (UVa 12144): dado un grafo dirigido con pesos, hallar la ruta
// mas corta de s a d que no use NINGUNA arista que aparezca en ALGUNA ruta minima de s a d.
// Son tres fases y la del medio es la que hay que entender:
//   1. Dijkstra desde s, guardando ademas los PREDECESORES de cada nodo sobre rutas minimas.
//   2. Desde d, ir hacia atras por esos predecesores marcando cada arista como prohibida. Eso
//      recorre exactamente el DAG de rutas minimas de s a d, ni una arista mas.
//   3. Dijkstra otra vez saltando las prohibidas. Si d queda inalcanzable, la respuesta es -1.
// LA FASE 2 ES LA CLAVE: no basta con borrar las aristas tensas (dist[u] + w == dist[v]), porque
// hay aristas tensas que no llevan a d y esas SI se pueden usar. Por eso se entra al DAG desde d
// y no desde s. Ese es el error tipico del problema.
// Como se llenan los predecesores: si la distancia MEJORA en sentido estricto, la lista se
// REINICIA a ese unico predecesor; si EMPATA, se agrega. Ese par reiniciar/agregar es lo unico
// que hay que copiar bien, y sirve igual para contar rutas minimas o para el k-esimo camino.
// El caminos[s] = {-1} es el centinela que corta el barrido hacia atras al llegar al origen.
// OJO CON EL VISTO DEL BFS (la linea marcada abajo): sin el, un nodo se vuelve a encolar una vez
// por cada ruta que lo cruza, no una vez en total, y eso es EXPONENCIAL. Medido: con una escalera
// de capas de 2 nodos donde toda ruta es minima, sin el visto tarda 0.06 s con 46 nodos, 0.24 s
// con 50, 0.96 s con 54, y con 82 nodos y 160 aristas se queda sin memoria y sale sin imprimir
// nada. Con el visto, los mismos casos van en 0.01 s. Y 82 nodos caben de sobra en el limite del
// problema (n <= 500), asi que no es un caso de laboratorio.
// OJO CON LA MATRIZ paso: es n x n, o sea que con n grande no cabe, y colapsa las aristas
// paralelas (si hubiera dos a->b con pesos distintos, prohibir una prohibe las dos). Con n <= 500
// va bien; si el limite sube, hay que marcar por INDICE de arista y no por par (a, b).
// VERIFICADO: el sample oficial (5 / -1 / 6) y 10.000 grafos aleatorios contra una implementacion
// independiente, 0 diferencias.

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

    long long n, m;
    long long s,d;

    while(cin >> n >> m && n != 0 && m != 0)
    {
        cin >> s >> d;

        vector<vector<pair<long long, long long>>> conexiones(n);
        vector<vector<bool>> paso(n,vector<bool>(n,false));

        for(long long i = 0; i < m; i++)
        {
            long long a, b, c;
            cin >> a >> b >> c;

            conexiones[a].push_back({b, c});
            paso[a][b] = true;
        }

        vector<vector<long long>> caminos(n);
        vector<long long> distancia(n, LLONG_MAX);

        priority_queue<
            pair<long long, long long>,
            vector<pair<long long, long long>>,
            greater<pair<long long, long long>>
        > cola;

        caminos[s] = {-1};
        distancia[s] = 0;
        cola.push({0, s});

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

                if(distancia[hacia] > nuevaDistancia)
                {

                    distancia[hacia] = nuevaDistancia;

                    caminos[hacia] = {actual};       // mejora: se REINICIA la lista

                    cola.push({nuevaDistancia, hacia});
                }
                else if(distancia[hacia] == nuevaDistancia)
                {
                    caminos[hacia].push_back(actual); // empate: se AGREGA
                }
            }
        }

        queue<long long> colita;
        vector<bool> visto(n, false);
        colita.push(d);
        visto[d] = true;

        while(!colita.empty())
        {
            long long ahora = colita.front();
            colita.pop();

            for(long long poraca: caminos[ahora])
            {
                if(poraca == -1) continue;
                paso[poraca][ahora] = false;
                if(visto[poraca]) continue;      // sin esta linea el BFS es exponencial
                visto[poraca] = true;
                colita.push(poraca);
            }
        }

        distancia.assign(n, LLONG_MAX);

        distancia[s] = 0;
        cola.push({0, s});

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

                if(!paso[actual][hacia]) continue;

                long long nuevaDistancia = peso + cuanto;

                if(distancia[hacia] > nuevaDistancia)
                {
                    distancia[hacia] = nuevaDistancia;

                    cola.push({nuevaDistancia, hacia});
                }
            }
        }

        cout << (distancia[d] == LLONG_MAX ? -1 : distancia[d]) << '\n';
    }

    return 0;
}
