// <3
// Tema: Graphs / Max Flow (Binary Search + Dinic)
// Resuelve "Gasoline": hay P gasolineras con demanda D_i y R refinerias con stock E_j, con
// solo algunos pares (refineria,gasolinera) habilitados por contrato y un tiempo de viaje T
// conocido para esos pares; hay que hallar el menor tiempo t tal que, usando solo rutas con
// T<=t, se pueda abastecer completamente a todas las gasolineras (repartiendo entre varias
// refinerias si hace falta), o -1 si nunca alcanza.
// Hace busqueda binaria sobre los tiempos distintos y, para cada candidato t, feasible(t)
// arma una red fuente->refineria->gasolinera->sumidero (capacidades = stock, infinito solo
// si tiempo<=t, y demanda) y corre Dinic (network::max_flow) comparando contra sumD.

#include <bits/stdc++.h>
using namespace std;

struct edge {
    int v, cap, inv, flow;
};

struct network {
    int n, s, t;
    vector<int> lvl;
    vector<vector<edge>> g;
    network(int n) : n(n), lvl(n), g(n) {}
    void add_edge(int u, int v, int c) {
        g[u].push_back({v, c, (int)g[v].size(), 0});
        g[v].push_back({u, 0, (int)g[u].size()-1, c});
    }
    bool bfs() {
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q;
        lvl[s] = 0;
        for(q.push(s); q.size(); q.pop()) {
            int u = q.front();
            for (auto &e : g[u]) {
                if(e.cap > 0 && lvl[e.v] == -1) {
                    lvl[e.v] = lvl[u]+1;
                    q.push(e.v);
                }
            }
        }
        return lvl[t] != -1;
    }
    int dfs(int u, int nf) {
        if(u == t) return nf;
        int res = 0;
        for (auto &e : g[u]) {
            if(e.cap > 0 && lvl[e.v] == lvl[u]+1) {
                int tf = dfs(e.v, min(nf, e.cap));
                res += tf;
                nf -= tf;
                e.cap -= tf;
                g[e.v][e.inv].cap += tf;
                g[e.v][e.inv].flow -= tf;
                e.flow += tf;
                if(nf == 0) return res;
            }
        }
        if(!res) lvl[u] = -1;
        return res;
    }
    int max_flow(int so, int si, int res = 0) {
        s = so; t = si;
        while(bfs()) res += dfs(s, INT_MAX);
        return res;
    }
};

int P, R, C;
vector<int> D, E; // D[1..P], E[1..R]
vector<array<int,3>> edges; // I (station), J (refinery), T
long long sumD;

// nodos: 0 = source
//        1..R  = refinerias
//        R+1..R+P = gasolineras
//        R+P+1 = sumidero
bool feasible(int t) {
    int n = R + P + 2;
    int S = 0, T = R + P + 1;
    network net(n);

    // source -> refineria, capacidad = stock
    for (int j = 1; j <= R; j++) {
        net.add_edge(S, j, E[j]);
    }
    // gasolinera -> sumidero, capacidad = demanda
    for (int i = 1; i <= P; i++) {
        net.add_edge(R + i, T, D[i]);
    }
    // refineria -> gasolinera, solo si T_edge <= t
    int INF = 1000000000;
    for (auto &e : edges) {
        int i = e[0], j = e[1], time = e[2];
        if (time <= t) {
            net.add_edge(j, R + i, INF);
        }
    }

    long long f = net.max_flow(S, T);
    return f >= sumD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> P >> R >> C;
    D.assign(P+1, 0);
    E.assign(R+1, 0);
    for (int i = 1; i <= P; i++) cin >> D[i];
    for (int j = 1; j <= R; j++) cin >> E[j];

    edges.resize(C);
    vector<int> times(C);
    for (int k = 0; k < C; k++) {
        int i, j, t;
        cin >> i >> j >> t;
        edges[k] = {i, j, t};
        times[k] = t;
    }

    sumD = 0;
    for (int i = 1; i <= P; i++) sumD += D[i];

    // valores distintos de tiempo, ordenados
    sort(times.begin(), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());

    // primero chequeamos si es factible usando TODOS los arcos (t = maximo)
    if (times.empty() || !feasible(times.back())) {
        cout << -1 << "\n";
        return 0;
    }

    // binary search: encontrar el menor t factible
    int lo = 0, hi = (int)times.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (feasible(times[mid])) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << times[lo] << "\n";
    return 0;
}