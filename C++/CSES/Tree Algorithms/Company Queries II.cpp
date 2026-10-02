// <3
// Tema: CSES / LCA con Binary Lifting
// Resumen: El jefe comun mas cercano de dos empleados del arbol de la empresa
// O: (n log n) de tabla y (log n) por consulta
// Uso: up[k][u] = ancestro 2^k de u; lca(a,b) iguala alturas y despues sube los dos
// Detalle: LCA en dos fases, y las dos usan la misma tabla up[k][u] = el ancestro 2^k de u, que
// se llena durante el DFS porque up[k][u] = up[k-1][up[k-1][u]]. Primero se IGUALA LA ALTURA:
// se sube el mas profundo tantos niveles como diga la diferencia, en binario. Segundo, si no
// quedaron en el mismo nodo, se suben los DOS a la vez por los saltos mas grandes que NO los
// junten; al final los dos quedan justo debajo del LCA. El 'saltar solo si no se juntan' es lo
// que hace que no se pase de largo, y es la parte que se escribe mal la primera vez. LOG = 20
// cubre n hasta 10^6.

#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;

int n, q;

vector<vector<int>> up;
vector<int> depth;

void dfs(int u, int p, vector<vector<int>>& adj)
{
    up[0][u] = p;

    for(int k = 1; k < LOG; k++)
    {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }

    for(int v : adj[u])
    {
        if(v == p)
            continue;

        depth[v] = depth[u] + 1;
        dfs(v, u, adj);
    }
}

int lca(int a, int b)
{
    if(depth[a] < depth[b])
        swap(a, b);

    // Igualar alturas
    int diff = depth[a] - depth[b];

    for(int k = 0; k < LOG; k++)
    {
        if(diff & (1 << k))
            a = up[k][a];
    }

    if(a == b)
        return a;

    // Subir ambos
    for(int k = LOG - 1; k >= 0; k--)
    {
        if(up[k][a] != up[k][b])
        {
            a = up[k][a];
            b = up[k][b];
        }
    }

    return up[0][a];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    vector<vector<int>> adj(n + 1);

    for(int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;

        adj[p].push_back(i);
        adj[i].push_back(p);
    }

    up.assign(LOG, vector<int>(n + 1));
    depth.assign(n + 1, 0);

    depth[1] = 0;

    dfs(1, 1, adj);

    while(q--)
    {
        int a, b;
        cin >> a >> b;

        cout << lca(a, b) << '\n';
    }
}
