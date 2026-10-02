// <3
// Tema: Graph / Puentes y Puntos de Articulacion
// Resumen: Que aristas o que nodos, si se quitan, desconectan el grafo (no dirigido)
// O: (n + m)
// Uso: agregarArista(a,b) con ids 0..m-1; calcular(); puentes = ids; esArt[v]
// Detalle: DFS guardando tin[v] (cuando se visito) y low[v] (el tin mas chico al que se
// llega desde el subarbol de v usando UNA arista de retroceso). Para la arista v-u del
// arbol: es puente si low[u] > tin[v] (desde u no hay forma de volver a v o mas arriba).
// v es punto de articulacion si low[u] >= tin[v] para algun hijo u (y v no es la raiz);
// la raiz lo es si tiene 2 o mas hijos en el arbol DFS.
// Se salta la arista por la que se llego (por su ID, no por el nodo padre): asi dos
// aristas paralelas entre a y b quedan bien, y ninguna de las dos es puente.
// Vale con grafo desconectado (el for de calcular arranca un DFS por componente).
// Componentes 2-arista-conexas: quitar los puentes y lo que queda conectado.
// Recursivo: con 10^5-10^6 nodos en cadena puede reventar la pila.

#include <bits/stdc++.h>

using namespace std;

int n, m = 0, timer_;
vector<vector<pair<int, int>>> g;            // (vecino, id de la arista)
vector<int> tin, low, puentes;
vector<bool> esArt;

void agregarArista(int a, int b)
{
    g[a].push_back({b, m});
    g[b].push_back({a, m});
    m++;
}

void dfs(int v, int aristaPadre)
{
    tin[v] = low[v] = timer_++;
    int hijos = 0;
    for (auto [u, id] : g[v])
    {
        if (id == aristaPadre) continue;
        if (tin[u] != -1)
        {
            low[v] = min(low[v], tin[u]);
        }
        else
        {
            dfs(u, id);
            low[v] = min(low[v], low[u]);
            if (low[u] > tin[v]) puentes.push_back(id);
            if (low[u] >= tin[v] && aristaPadre != -1) esArt[v] = true;
            hijos++;
        }
    }
    if (aristaPadre == -1 && hijos > 1) esArt[v] = true;
}

void calcular()
{
    tin.assign(n, -1);
    low.assign(n, 0);
    esArt.assign(n, false);
    puentes.clear();
    timer_ = 0;
    for (int v = 0; v < n; v++)
    {
        if (tin[v] == -1) dfs(v, -1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // cin >> n >> mm; g.assign(n, {}); for (...) agregarArista(a, b); calcular();
    return 0;
}
