// <3
// Tema: CSES / Heavy-Light Decomposition
// Resumen: Maximo valor en el camino entre dos nodos, con actualizaciones de nodo
// O: (log^2 n) por consulta: log n cadenas, cada una con una consulta de log n al segment tree
// Uso: seg.update(pos[s], x) para cambiar un nodo; queryPath(a, b, seg) para el maximo
// Detalle: HLD parte el arbol en CADENAS de forma que cualquier camino raiz-nodo cruza a lo
// sumo log n cadenas. Cada nodo apunta al hijo con el subarbol mas grande (el 'pesado'), y esa
// es la cadena que continua. Con eso, los nodos se numeran de forma que cada cadena es un
// intervalo CONTIGUO, y entonces un segment tree normal responde sobre ella. Consultar un
// camino es subir saltando de cadena en cadena, pidiendo el maximo de cada tramo. El
// decompose() es el que asigna esas posiciones y el head de cada cadena. Es la herramienta mas
// pesada de escribir del notebook, pero es la que responde consultas de camino con
// actualizaciones, que ni el LCA ni el binary lifting resuelven.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTree
{
    int n;
    vector<ll> tree;

    SegTree(vector<ll>& a)
    {
        n = 1;
        while(n < (int)a.size())
            n *= 2;

        tree.assign(2 * n, 0);

        for(int i = 0; i < (int)a.size(); i++)
            tree[n + i] = a[i];

        for(int i = n - 1; i >= 1; i--)
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }

    void update(int pos, ll val)
    {
        pos += n;
        tree[pos] = val;

        pos /= 2;

        while(pos)
        {
            tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]);
            pos /= 2;
        }
    }

    ll query(int l, int r)
    {
        l += n;
        r += n;

        ll ans = 0;

        while(l <= r)
        {
            if(l & 1)
                ans = max(ans, tree[l++]);

            if(!(r & 1))
                ans = max(ans, tree[r--]);

            l /= 2;
            r /= 2;
        }

        return ans;
    }
};

int n, q;

vector<vector<int>> adj;

vector<int> parentNode;
vector<int> depth;
vector<int> sz;
vector<int> heavy;

vector<int> head;
vector<int> pos;

vector<ll> value;
vector<ll> base;

int timer = 0;

void dfs(int u, int p)
{
    parentNode[u] = p;
    sz[u] = 1;

    int best = 0;

    for(int v : adj[u])
    {
        if(v == p)
            continue;

        depth[v] = depth[u] + 1;

        dfs(v, u);

        sz[u] += sz[v];

        if(sz[v] > best)
        {
            best = sz[v];
            heavy[u] = v;
        }
    }
}

void decompose(int u, int h)
{
    head[u] = h;
    pos[u] = timer;
    base[timer] = value[u];
    timer++;

    if(heavy[u] != -1)
        decompose(heavy[u], h);

    for(int v : adj[u])
    {
        if(v == parentNode[u] || v == heavy[u])
            continue;

        decompose(v, v);
    }
}

ll queryPath(int u, int v, SegTree& seg)
{
    ll ans = 0;

    while(head[u] != head[v])
    {
        if(depth[head[u]] < depth[head[v]])
            swap(u, v);

        ans = max(
            ans,
            seg.query(pos[head[u]], pos[u])
        );

        u = parentNode[head[u]];
    }

    if(depth[u] > depth[v])
        swap(u, v);

    ans = max(
        ans,
        seg.query(pos[u], pos[v])
    );

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    value.resize(n + 1);

    for(int i = 1; i <= n; i++)
        cin >> value[i];

    adj.resize(n + 1);

    for(int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    parentNode.resize(n + 1);
    depth.resize(n + 1);
    sz.resize(n + 1);
    heavy.assign(n + 1, -1);

    head.resize(n + 1);
    pos.resize(n + 1);

    base.resize(n);

    dfs(1, 0);
    decompose(1, 1);

    SegTree seg(base);

    while(q--)
    {
        int type;
        cin >> type;

        if(type == 1)
        {
            int s;
            ll x;

            cin >> s >> x;

            seg.update(pos[s], x);
        }
        else
        {
            int a, b;
            cin >> a >> b;

            cout << queryPath(a, b, seg) << '\n';
        }
    }

    return 0;
}
