// <3
// Tema: Graph / SCC (Tarjan) y 2-SAT
// Resumen: Componentes fuertemente conexas, y con eso: existe asignacion verdadero/falso?
// O: (n + m)
// Uso: SCC s(n); s.add(a,b); s.run(); s.comp[v]. TwoSat t(vars); t.alMenosUno(a,va,b,vb)
// Detalle: Tarjan numera las componentes en orden topologico INVERSO: la componente 0 no
// tiene aristas hacia otras (es un sumidero). Grafo condensado: una arista comp[a]->comp[b]
// por cada a->b con comp distinto; es un DAG. "Minimo de nodos a activar para alcanzar
// todo" = cantidad de componentes con grado de entrada 0 en el condensado (Lumina, 2024).
// 2-SAT: cada variable x tiene dos nodos, x verdadera (2x) y x falsa (2x+1). La clausula
// (A o B) son dos implicaciones: no A -> B y no B -> A. Hay solucion si y solo si ninguna
// variable queda en la misma componente que su negacion; y x es verdadera si
// comp[2x] < comp[2x+1] (con la numeracion de Tarjan). Signal Coverage (2024) era esto.
// Restricciones utiles: "a implica b" = alMenosUno(a,false, b,true); "a y b no los dos" =
// alMenosUno(a,false, b,false); "a obligatoria" = alMenosUno(a,true, a,true).

#include <bits/stdc++.h>

using namespace std;

struct SCC
{
    int n, timer_ = 0, nc = 0;
    vector<vector<int>> g;
    vector<int> comp, tin, low, pila;
    vector<bool> enPila;

    SCC(int n) : n(n), g(n) {}
    void add(int a, int b) { g[a].push_back(b); }

    void dfs(int v)
    {
        tin[v] = low[v] = timer_++;
        pila.push_back(v);
        enPila[v] = true;
        for (int u : g[v])
        {
            if (tin[u] == -1)
            {
                dfs(u);
                low[v] = min(low[v], low[u]);
            }
            else if (enPila[u])
            {
                low[v] = min(low[v], tin[u]);
            }
        }
        if (low[v] == tin[v])                // v es la cabeza de su componente
        {
            while (true)
            {
                int u = pila.back();
                pila.pop_back();
                enPila[u] = false;
                comp[u] = nc;
                if (u == v) break;
            }
            nc++;
        }
    }

    int run()                                // devuelve la cantidad de componentes
    {
        comp.assign(n, -1);
        tin.assign(n, -1);
        low.assign(n, 0);
        enPila.assign(n, false);
        for (int v = 0; v < n; v++)
        {
            if (tin[v] == -1) dfs(v);
        }
        return nc;
    }
};

struct TwoSat
{
    int n;
    SCC s;
    vector<bool> valor;
    TwoSat(int n) : n(n), s(2 * n) {}
    int nodo(int x, bool v) { return 2 * x + (v ? 0 : 1); }

    // (x == vx) o (y == vy)
    void alMenosUno(int x, bool vx, int y, bool vy)
    {
        s.add(nodo(x, !vx), nodo(y, vy));
        s.add(nodo(y, !vy), nodo(x, vx));
    }

    bool resolver()
    {
        s.run();
        valor.assign(n, false);
        for (int x = 0; x < n; x++)
        {
            if (s.comp[2 * x] == s.comp[2 * x + 1]) return false;
            valor[x] = s.comp[2 * x] < s.comp[2 * x + 1];
        }
        return true;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
