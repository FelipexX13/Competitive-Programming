// <3
// Tema: Graph / Flujo Maximo (Dinic), Corte Minimo y Matching Bipartito (Kuhn)
// Resumen: Flujo maximo = corte minimo, y el emparejamiento maximo entre dos grupos
// O: Dinic O(V^2 E) en general, O(E raiz V) en bipartito; Kuhn O(V E)
// Uso: D.add(a,b,cap); D.maxflow(s,t); D.ladoS(v). Kuhn: K.g[izq].push_back(der); K.run()
// Detalle: Dinic: BFS arma niveles desde s en el grafo residual, y DFS empuja flujo solo por
// aristas que suben un nivel; it[] recuerda por que arista va cada nodo para no repetir.
// Cada add crea la arista y su reversa (indices i e i^1). Arista NO dirigida de capacidad c:
// add(a, b, c, c).
// Corte minimo: tras maxflow, ladoS(v) dice si v quedo del lado de s (alcanzable en el
// residual). Las aristas de un nodo con ladoS a uno sin ladoS forman el corte, y suman el
// flujo maximo. "Separar/cortar al menor costo" es esto.
// Modelados comunes: capacidad en NODOS -> partir v en v_in -> v_out con esa capacidad.
// Varias fuentes -> una superfuente conectada a todas. Matching bipartito -> s -> izq (1),
// izq -> der (1), der -> t (1).
// Kuhn: mas corto de escribir para matching bipartito; con 10^3 a 10^4 nodos entra bien.
// K.mR[r] es la pareja izquierda de r (-1 si quedo libre).
// En bipartito (Konig): matching maximo = cubrimiento minimo de vertices; conjunto
// independiente maximo = V - matching. En un DAG: minimo de caminos que cubren todos los
// nodos sin compartir ninguno = n - matching (cada nodo partido en izquierda y derecha, y
// cada arista u->v de izquierda u a derecha v).

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Dinic
{
    struct Arista
    {
        int to;
        ll cap;
    };
    vector<Arista> e;
    vector<vector<int>> g;
    vector<int> nivel, it;

    Dinic(int n) : g(n), nivel(n), it(n) {}

    void add(int a, int b, ll cap, ll capReversa = 0)
    {
        g[a].push_back(e.size());
        e.push_back({b, cap});
        g[b].push_back(e.size());
        e.push_back({a, capReversa});
    }

    bool bfs(int s, int t)
    {
        fill(nivel.begin(), nivel.end(), -1);
        queue<int> q;
        q.push(s);
        nivel[s] = 0;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int id : g[v])
            {
                if (e[id].cap > 0 && nivel[e[id].to] == -1)
                {
                    nivel[e[id].to] = nivel[v] + 1;
                    q.push(e[id].to);
                }
            }
        }
        return nivel[t] != -1;
    }

    ll dfs(int v, int t, ll f)
    {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); i++)
        {
            int id = g[v][i];
            int u = e[id].to;
            if (e[id].cap > 0 && nivel[u] == nivel[v] + 1)
            {
                ll d = dfs(u, t, min(f, e[id].cap));
                if (d > 0)
                {
                    e[id].cap -= d;
                    e[id ^ 1].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    ll maxflow(int s, int t)
    {
        ll flujo = 0;
        while (bfs(s, t))
        {
            fill(it.begin(), it.end(), 0);
            while (ll d = dfs(s, t, LLONG_MAX)) flujo += d;
        }
        return flujo;
    }

    bool ladoS(int v) { return nivel[v] != -1; }   // valido despues de maxflow
};

struct Kuhn
{
    int nL, nR, marca = 0;
    vector<vector<int>> g;                   // g[izquierda] = derechas vecinas
    vector<int> mR, vis;

    Kuhn(int nL, int nR) : nL(nL), nR(nR), g(nL) {}

    bool intentar(int v)
    {
        for (int u : g[v])
        {
            if (vis[u] == marca) continue;
            vis[u] = marca;
            if (mR[u] == -1 || intentar(mR[u]))
            {
                mR[u] = v;
                return true;
            }
        }
        return false;
    }

    int run()
    {
        mR.assign(nR, -1);
        vis.assign(nR, 0);
        int res = 0;
        for (int v = 0; v < nL; v++)
        {
            marca++;
            if (intentar(v)) res++;
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
