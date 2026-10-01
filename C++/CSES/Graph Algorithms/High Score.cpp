// <3
// Tema: CSES / Bellman-Ford (Camino Maximo)
// Resumen: Camino de peso MAXIMO con aristas negativas, que es Bellman-Ford con la desigualdad
// volteada
// O: (n*m), Bellman-Ford maximizando y marcando ciclos positivos
// Detalle: Camino de peso MAXIMO con aristas negativas, que es Bellman-Ford con la desigualdad
// volteada. Se relaja n veces; si en la pasada n todavia mejora algo, hay un ciclo de ganancia
// infinita. El detalle que hace correcto el problema: un ciclo positivo solo importa si se
// puede LLEGAR a el desde el origen y desde el SALIR hacia el destino. Por eso los dos BFS
// previos, uno en el grafo normal desde 1 y otro en el grafo INVERSO desde n: solo los nodos
// marcados en ambos cuentan para detectar el ciclo. Sin ese filtro, un ciclo positivo en una
// parte inalcanzable del grafo daria -1 de mentiras. CUANDO USAR BELLMAN-FORD: pesos negativos
// (Dijkstra ya no sirve) o hay que DETECTAR ciclos negativos, que es su unica ventaja real. Es
// O(n*m), mucho mas lento que Dijkstra, asi que con pesos no negativos nunca se usa.

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
    long long n, m;
    cin >> n >> m;

    vector<vector<pair<long long, long long>>> conexion(n);
    vector<vector<pair<long long, long long>>> conexionInversa(n);

    for(long long i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        a--;
        b--;

        conexion[a].push_back({b, c});
        conexionInversa[b].push_back({a, c});
    }

    vector<bool> de0(n, false);
    vector<bool> antesN(n, false);

    // BFS desde 0
    queue<long long> cola;
    cola.push(0);
    de0[0] = true;

    while(!cola.empty())
    {
        long long actual = cola.front();
        cola.pop();

        for(auto vecino : conexion[actual])
        {
            long long siguiente = vecino.first;

            if(!de0[siguiente])
            {
                de0[siguiente] = true;
                cola.push(siguiente);
            }
        }
    }

    // BFS desde n-1 usando el grafo inverso
    cola.push(n - 1);
    antesN[n - 1] = true;

    while(!cola.empty())
    {
        long long actual = cola.front();
        cola.pop();

        for(auto vecino : conexionInversa[actual])
        {
            long long siguiente = vecino.first;

            if(!antesN[siguiente])
            {
                antesN[siguiente] = true;
                cola.push(siguiente);
            }
        }
    }

    // OUTPUT
    vector<long long> distancia(n, LLONG_MIN);
    distancia[0] = 0;

    bool ciclo = false;

    for(long long i = 0; i < n; i++)
    {
        ciclo = false;

        for(long long a = 0; a < n; a++)
        {
            if(!de0[a] || !antesN[a] || distancia[a] == LLONG_MIN)
                continue;

            for(auto vecino : conexion[a])
            {
                long long b = vecino.first;
                long long c = vecino.second;

                if(!de0[b] || !antesN[b])
                    continue;

                if(distancia[b] < distancia[a] + c)
                {
                    distancia[b] = distancia[a] + c;
                    ciclo = true;
                }
            }
        }
    }

    if(ciclo)
        cout << -1 << '\n';
    else
        cout << distancia[n - 1] << '\n';

    return 0;
}