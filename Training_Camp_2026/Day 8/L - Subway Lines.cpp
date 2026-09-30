// <3
// Tema: Graphs / LCA (Binary Lifting)
// Resuelve "Subway Lines": en un sistema de subte con forma de arbol, las lineas de tren van
// y vuelven entre pares de estaciones terminales (hojas), pasando por el unico camino entre
// ellas; dadas Q consultas con dos pares de terminales (A,B) y (C,D), hay que calcular cuantas
// estaciones tienen en comun los caminos que definen esas dos lineas.
// Precalcula profundidad y ancestros con binary lifting (bfsSetup/up_) para responder lca(u,v)
// y dist(u,v) en O(log N), y solveQuery halla la interseccion de los dos caminos comparando
// las profundidades de lca(a,b) y lca(c,d), usando lca/isAncestor para ubicar los extremos
// de la interseccion y devolver su longitud (dist+1) o 0 si los caminos no se cruzan.

#include <bits/stdc++.h>
using namespace std;

static char buf_[1 << 22];
static int bufLen_, bufPos_;
inline int gc() {
    if (bufPos_ == bufLen_) { bufLen_ = fread(buf_, 1, sizeof(buf_), stdin); bufPos_ = 0; if (!bufLen_) return -1; }
    return buf_[bufPos_++];
}
inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    bool neg = false; if (c == '-') { neg = true; c = gc(); }
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

int N, Q;
vector<vector<int>> adj;
vector<int> depth_;
int LOG_;
vector<vector<int>> up_;

void bfsSetup(int root) {
    depth_.assign(N + 1, -1);
    up_.assign(LOG_, vector<int>(N + 1, root));
    depth_[root] = 0;
    up_[0][root] = root;
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (depth_[v] == -1) {
                depth_[v] = depth_[u] + 1;
                up_[0][v] = u;
                q.push(v);
            }
        }
    }
    for (int k = 1; k < LOG_; k++) {
        for (int v = 1; v <= N; v++) {
            up_[k][v] = up_[k - 1][up_[k - 1][v]];
        }
    }
}

int lca(int u, int v) {
    if (depth_[u] < depth_[v]) swap(u, v);
    int diff = depth_[u] - depth_[v];
    for (int k = 0; k < LOG_; k++) if ((diff >> k) & 1) u = up_[k][u];
    if (u == v) return u;
    for (int k = LOG_ - 1; k >= 0; k--) {
        if (up_[k][u] != up_[k][v]) { u = up_[k][u]; v = up_[k][v]; }
    }
    return up_[0][u];
}

inline int dist(int u, int v) {
    return depth_[u] + depth_[v] - 2 * depth_[lca(u, v)];
}

inline bool isAncestor(int u, int v) {
    return lca(u, v) == u;
}

int solveQuery(int a, int b, int c, int d) {
    int l1 = lca(a, b), l2 = lca(c, d);
    if (depth_[l1] > depth_[l2]) {
        swap(a, c); swap(b, d); swap(l1, l2);
    }
    // is l2 on path(a,b)?
    if (dist(a, l2) + dist(l2, b) != dist(a, b)) return 0;

    if (l1 == l2) {
        int lac = lca(a, c), lad = lca(a, d);
        int deepA = (depth_[lac] >= depth_[lad]) ? lac : lad;
        int lbc = lca(b, c), lbd = lca(b, d);
        int deepB = (depth_[lbc] >= depth_[lbd]) ? lbc : lbd;
        return dist(deepA, deepB) + 1;
    } else {
        if (isAncestor(l2, a)) {
            int lac = lca(a, c), lad = lca(a, d);
            int deepA = (depth_[lac] >= depth_[lad]) ? lac : lad;
            return dist(l2, deepA) + 1;
        } else {
            int lbc = lca(b, c), lbd = lca(b, d);
            int deepB = (depth_[lbc] >= depth_[lbd]) ? lbc : lbd;
            return dist(l2, deepB) + 1;
        }
    }
}

int main() {
    N = readInt(); Q = readInt();
    adj.assign(N + 1, {});
    for (int i = 0; i < N - 1; i++) {
        int u = readInt(), v = readInt();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    LOG_ = 1;
    while ((1 << LOG_) < N + 1) LOG_++;
    bfsSetup(1);

    string out;
    out.reserve(Q * 7);
    char tmp[16];
    for (int q = 0; q < Q; q++) {
        int a = readInt(), b = readInt(), c = readInt(), d = readInt();
        int res = solveQuery(a, b, c, d);
        int len = sprintf(tmp, "%d\n", res);
        out.append(tmp, len);
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}