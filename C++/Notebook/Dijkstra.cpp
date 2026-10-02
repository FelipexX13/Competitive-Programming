// <3
// Tema: Graph / Dijkstra con Reconstruccion de Camino
// Resumen: Distancias minimas desde un origen con pesos >= 0, y el camino hasta cualquier nodo
// O: ((n + m) log m)
// Uso: g[u].push_back({v,w}); auto d = dijkstra(g, s, padre); camino(padre, t)
// Detalle: Heap de minimo con (distancia, nodo). Al sacar un nodo cuya distancia guardada
// ya mejoro, se descarta (el "if (du != d[u]) continue"): sin esa linea el algoritmo sigue
// siendo correcto pero puede volverse cuadratico. d[v] == INF significa inalcanzable; INF
// nunca se suma (solo se relaja desde un d[u] ya finito), asi que no desborda.
// Variantes: muchos origenes a la vez -> meterlos todos al heap con distancia 0. El
// k-esimo camino mas corto -> dejar sacar cada nodo hasta k veces. Grafo de estados
// (nodo, cupones usados, ...) -> el mismo codigo sobre el estado compuesto.
// Pesos 0/1 -> BFS 0-1 con deque. Pesos negativos -> Bellman-Ford, NO Dijkstra.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 4e18;

vector<ll> dijkstra(const vector<vector<pair<int, ll>>> &g, int s, vector<int> &padre)
{
    int n = g.size();
    vector<ll> d(n, INF);
    padre.assign(n, -1);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    d[s] = 0;
    pq.push({0, s});
    while (!pq.empty())
    {
        auto [du, u] = pq.top();
        pq.pop();
        if (du != d[u]) continue;            // entrada vieja del heap
        for (auto [v, w] : g[u])
        {
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                padre[v] = u;
                pq.push({d[v], v});
            }
        }
    }
    return d;
}

// Camino s -> t como lista de nodos (vacio si t es inalcanzable y t != s)
vector<int> camino(const vector<int> &padre, int t)
{
    vector<int> c;
    for (int v = t; v != -1; v = padre[v]) c.push_back(v);
    reverse(c.begin(), c.end());
    return c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
