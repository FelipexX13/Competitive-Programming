// <3
// Tema: Graph / Kruskal Reconstruction Tree
// Resuelve "Trucks" (Maratona de Programacao da SBC 2013, problem J): Nlogonia es un
// archipielago de N islas unidas por M puentes, cada uno con un limite maximo de peso W; para
// S sitios de competencia hay que hallar el mayor peso que puede transportarse por camion entre
// el almacen H y el sitio L, es decir, el maximo sobre todos los caminos posibles del minimo W
// en ese camino (cuello de botella maximo).
// Ordena los puentes por peso decreciente y los va uniendo con un DSU al estilo Kruskal, pero
// en vez de solo unir arma un arbol binario de reconstruccion (nodeRepr/leftChild/rightChild)
// donde cada fusion crea un nodo interno con el peso del puente. El ancestro comun mas bajo
// (LCA, calculado con binary lifting) de dos hojas en ese arbol es justamente el nodo cuyo peso
// es la respuesta a la consulta.

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

int N, M, S;
vector<int> dsuParent;
int find(int x) {
    while (dsuParent[x] != x) { dsuParent[x] = dsuParent[dsuParent[x]]; x = dsuParent[x]; }
    return x;
}

int main() {
    N = readInt(); M = readInt(); S = readInt();

    vector<array<int,3>> edgeList(M); // {W, A, B} for easy sort by weight
    for (int i = 0; i < M; i++) {
        int a = readInt(), b = readInt(), w = readInt();
        edgeList[i] = {w, a, b};
    }
    sort(edgeList.begin(), edgeList.end(), [](const array<int,3>&x, const array<int,3>&y){
        return x[0] > y[0]; // decreasing weight
    });

    int totalNodes = 2 * N; // leaves 1..N, internal nodes N+1..2N-1 (at most N-1 of them)
    dsuParent.assign(totalNodes + 1, 0);
    iota(dsuParent.begin(), dsuParent.end(), 0);

    vector<int> nodeRepr(totalNodes + 1, 0);
    for (int i = 1; i <= N; i++) nodeRepr[i] = i;

    vector<int> leftChild(totalNodes + 1, 0), rightChild(totalNodes + 1, 0), weightOf(totalNodes + 1, 0);

    int nextInternal = N + 1;
    int merges = 0;
    for (auto &e : edgeList) {
        if (merges == N - 1) break;
        int w = e[0], a = e[1], b = e[2];
        int ra = find(a), rb = find(b);
        if (ra == rb) continue;
        int newNode = nextInternal++;
        weightOf[newNode] = w;
        leftChild[newNode] = nodeRepr[ra];
        rightChild[newNode] = nodeRepr[rb];
        dsuParent[ra] = rb; // union
        nodeRepr[rb] = newNode; // rb is now the representative root (arbitrary choice), pointing to new node
        merges++;
    }
    int root = nodeRepr[find(1)];

    int totalUsed = nextInternal - 1; // highest node id actually used
    int LOG = 1;
    while ((1 << LOG) < totalUsed + 1) LOG++;
    vector<vector<int>> up(LOG, vector<int>(totalUsed + 1, 0));
    vector<int> depth(totalUsed + 1, 0);

    // iterative pre-order traversal to set depth & up[0]
    {
        vector<int> stk;
        stk.push_back(root);
        depth[root] = 0;
        up[0][root] = 0;
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back();
            if (u <= N) continue; // leaf, no children
            int lc = leftChild[u], rc = rightChild[u];
            depth[lc] = depth[u] + 1; up[0][lc] = u; stk.push_back(lc);
            depth[rc] = depth[u] + 1; up[0][rc] = u; stk.push_back(rc);
        }
    }
    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= totalUsed; v++) {
            up[k][v] = up[k-1][up[k-1][v]];
        }
    }

    auto lca = [&](int u, int v) -> int {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; k++) if ((diff >> k) & 1) u = up[k][u];
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) { u = up[k][u]; v = up[k][v]; }
        }
        return up[0][u];
    };

    string out;
    out.reserve(S * 8);
    for (int i = 0; i < S; i++) {
        int L = readInt(), H = readInt();
        int anc = lca(L, H);
        out += to_string(weightOf[anc]);
        out += "\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}