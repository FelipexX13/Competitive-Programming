// <3
// Tema: Graph / LCA con Binary Lifting
// Resumen: Ancestro comun mas bajo, distancia entre dos nodos y k-esimo ancestro en un arbol
// O: (n log n) armar, (log n) cada consulta
// Uso: LCA L(g, raiz); L.lca(a,b); L.dist(a,b); L.subir(v,k); g lista de adyacencia
// Detalle: up[j][v] es el ancestro 2^j niveles arriba de v (la raiz es su propio padre).
// Para lca(a,b): se sube el mas profundo hasta igualar profundidades, y despues se suben
// los dos juntos con saltos de 2^j de mayor a menor mientras NO coincidan; al final el
// padre de cualquiera es el LCA. dist = dep[a] + dep[b] - 2*dep[lca].
// Se arma con BFS, sin recursion: no revienta la pila con un arbol en cadena de 10^6.
// Arbol con pesos: guardar ademas la suma de pesos desde la raiz (distRaiz) y la distancia
// es distRaiz[a] + distRaiz[b] - 2*distRaiz[lca]. Maximo de arista en el camino: guardar
// mx[j][v] junto a up[j][v] y combinarlo en los mismos saltos.
// El arbol tiene que ser conexo; con un bosque, una raiz por componente (o una raiz
// virtual conectada a todas).

#include <bits/stdc++.h>

using namespace std;

struct LCA
{
    int n, LOG;
    vector<vector<int>> up;
    vector<int> dep;

    LCA(const vector<vector<int>> &g, int raiz = 0) : n(g.size()), LOG(1), dep(n, -1)
    {
        while ((1 << LOG) < n) LOG++;
        up.assign(LOG, vector<int>(n, raiz));
        queue<int> q;
        q.push(raiz);
        dep[raiz] = 0;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int u : g[v])
            {
                if (dep[u] != -1) continue;
                dep[u] = dep[v] + 1;
                up[0][u] = v;
                q.push(u);
            }
        }
        for (int j = 1; j < LOG; j++)
        {
            for (int v = 0; v < n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
        }
    }

    int subir(int v, int k)          // ancestro k niveles arriba (raiz si se pasa)
    {
        k = min(k, dep[v]);          // sin esto, un k >= 2^LOG perdia sus bits altos
        for (int j = 0; j < LOG; j++)
        {
            if (k >> j & 1) v = up[j][v];
        }
        return v;
    }

    int lca(int a, int b)
    {
        if (dep[a] < dep[b]) swap(a, b);
        a = subir(a, dep[a] - dep[b]);
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--)
        {
            if (up[j][a] != up[j][b])
            {
                a = up[j][a];
                b = up[j][b];
            }
        }
        return up[0][a];
    }

    int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
