// <3
// Tema: Graph / Biconnected Components (Block-Cut Tree) + LCA
// Resuelve "Hedge Mazes" (Training Camp 2026, Day 4 problema N): dado un laberinto de R salas y C
// corredores, para cada consulta (S, T) hay que decidir si existe exactamente un camino simple
// entre S y T (si hay un ciclo en el medio, existiria mas de un camino simple).
// Construye las componentes biconexas (buildBiconnected, via low-link) y arma el arbol de bloques
// y puntos de corte (block-cut tree), donde cada bloque de tamano >= 3 vertices representa un
// ciclo; usando LCA con binary lifting (bfsBuildLCA/queryPath) calcula el maximo tamano de bloque
// en el camino entre S y T, y responde 'Y' solo si ese maximo es <= 2 (solo aristas, sin ciclos).

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

int R, C, Q;
vector<pair<int,int>> edges;              // edge id -> (u,v)
vector<vector<pair<int,int>>> adj;        // adj[u] -> list of (v, edgeId)
vector<int> disc_, low_;
vector<char> visited_, isCut;
int timer_;

vector<int> posOfVertex;   // "position" node id in block-cut tree for each original vertex
                            // for a cut vertex v: position = v itself (1..R)
                            // for a non-cut vertex v: position = its unique block's node id (R+1..R+numBlocks)
vector<int> blockWeight;   // weight[nodeId] : block-size for block nodes, 0 for cut-vertex nodes (irrelevant)
vector<vector<int>> treeAdj; // adjacency list over node ids 1..(R+numBlocks)
vector<int> treeCompId;      // which tree (of the block-cut forest) each node belongs to
int numBlocks;

vector<int> lastMarked; // lastMarked[v] = block index that last touched vertex v (avoids duplicate adds)

void buildBiconnected() {
    disc_.assign(R + 1, -1);
    low_.assign(R + 1, -1);
    visited_.assign(R + 1, 0);
    isCut.assign(R + 1, 0);
    posOfVertex.assign(R + 1, -1);
    lastMarked.assign(R + 1, -1);
    timer_ = 0;
    numBlocks = 0;

    vector<vector<int>> blockVerts; // blockVerts[b] = list of vertices in block b (0-indexed b)
    vector<int> edgeStack;

    for (int s = 1; s <= R; s++) {
        if (visited_[s]) continue;
        // iterative DFS
        vector<array<int,4>> stk; // {u, nextIdx, parentEdge, parentVertex}
        visited_[s] = 1;
        disc_[s] = low_[s] = timer_++;
        stk.push_back({s, 0, -1, -1});
        int rootChildren = 0;

        while (!stk.empty()) {
            auto &fr = stk.back();
            int u = fr[0];
            if (fr[1] < (int)adj[u].size()) {
                int v = adj[u][fr[1]].first;
                int eid = adj[u][fr[1]].second;
                fr[1]++;
                if (eid == fr[2]) continue; // skip edge back to parent
                if (!visited_[v]) {
                    visited_[v] = 1;
                    disc_[v] = low_[v] = timer_++;
                    edgeStack.push_back(eid);
                    if (u == s) rootChildren++;
                    stk.push_back({v, 0, eid, u});
                } else if (disc_[v] < disc_[u]) {
                    edgeStack.push_back(eid);
                    low_[u] = min(low_[u], disc_[v]);
                }
            } else {
                int parentEdge = fr[2];
                int parentVertex = fr[3];
                int uLow = low_[u];
                stk.pop_back();
                if (!stk.empty()) {
                    int p = parentVertex;
                    low_[p] = min(low_[p], uLow);
                    if (uLow >= disc_[p]) {
                        if (p != s) isCut[p] = 1;
                        // pop edges up to and including parentEdge -> forms one block
                        int b = numBlocks++;
                        blockVerts.push_back({});
                        while (!edgeStack.empty()) {
                            int e = edgeStack.back();
                            edgeStack.pop_back();
                            int a1 = edges[e].first, a2 = edges[e].second;
                            if (lastMarked[a1] != b) { lastMarked[a1] = b; blockVerts[b].push_back(a1); }
                            if (lastMarked[a2] != b) { lastMarked[a2] = b; blockVerts[b].push_back(a2); }
                            if (e == parentEdge) break;
                        }
                    }
                }
            }
        }
        if (rootChildren > 1) isCut[s] = 1;
    }

    // assign block weights and non-cut vertex positions
    blockWeight.assign(1 + R + numBlocks, 0);
    for (int b = 0; b < numBlocks; b++) {
        int nodeId = R + 1 + b;
        blockWeight[nodeId] = (int)blockVerts[b].size();
        for (int v : blockVerts[b]) {
            if (!isCut[v]) {
                posOfVertex[v] = nodeId;
            }
        }
    }
    for (int v = 1; v <= R; v++) {
        if (isCut[v]) posOfVertex[v] = v;
        else if (posOfVertex[v] == -1) {
            // isolated vertex (no edges at all) -> give it its own trivial "block" node conceptually.
            // We reuse it as its own position id (acts like a size-1 pseudo node, weight 0, never matches
            // any other vertex's position unless that vertex IS this same isolated vertex, which can't
            // happen for a distinct query since S != T is guaranteed... but S or T might independently
            // be isolated vertices in different queries).
            posOfVertex[v] = v; // treat as its own node; weight will be 0 (irrelevant) and it will simply
                                  // have no tree edges, forming its own singleton tree.
        }
    }

    // Build tree adjacency
    treeAdj.assign(1 + R + numBlocks, {});
    for (int b = 0; b < numBlocks; b++) {
        int nodeId = R + 1 + b;
        for (int v : blockVerts[b]) {
            if (isCut[v]) {
                treeAdj[v].push_back(nodeId);
                treeAdj[nodeId].push_back(v);
            }
        }
    }
}

// LCA with binary lifting, tracking max blockWeight along the path (node weights only matter for block nodes;
// cut-vertex nodes / isolated singleton nodes have weight 0 which never triggers the "bad" condition).
int LOG_;
vector<vector<int>> up_;
vector<vector<int>> upMax_; // upMax_[k][v] = max weight among the 2^k nodes starting at v going upward (v itself
                             // included at k=0 as weight[v], combined appropriately)
vector<int> depth_;

void bfsBuildLCA(int totalNodes) {
    LOG_ = 1;
    while ((1 << LOG_) < totalNodes + 1) LOG_++;
    up_.assign(LOG_, vector<int>(totalNodes + 1, 0));
    upMax_.assign(LOG_, vector<int>(totalNodes + 1, 0));
    depth_.assign(totalNodes + 1, -1);
    treeCompId.assign(totalNodes + 1, -1);

    int curComp = -1;
    for (int start = 1; start <= totalNodes; start++) {
        if (depth_[start] != -1) continue;
        curComp++;
        queue<int> bfsq;
        depth_[start] = 0;
        up_[0][start] = 0; // root's parent = 0 (sentinel "no parent")
        upMax_[0][start] = blockWeight[start];
        treeCompId[start] = curComp;
        bfsq.push(start);
        while (!bfsq.empty()) {
            int u = bfsq.front(); bfsq.pop();
            for (int w : treeAdj[u]) {
                if (depth_[w] == -1) {
                    depth_[w] = depth_[u] + 1;
                    up_[0][w] = u;
                    upMax_[0][w] = max(blockWeight[w], blockWeight[u]);
                    treeCompId[w] = curComp;
                    bfsq.push(w);
                }
            }
        }
    }

    for (int k = 1; k < LOG_; k++) {
        for (int v = 1; v <= totalNodes; v++) {
            int mid = up_[k-1][v];
            if (mid == 0) { up_[k][v] = 0; upMax_[k][v] = upMax_[k-1][v]; }
            else {
                up_[k][v] = up_[k-1][mid];
                upMax_[k][v] = max(upMax_[k-1][v], upMax_[k-1][mid]);
            }
        }
    }
}

// returns {lca, maxWeightOnPath} or {-1, -1} if different components
pair<int,int> queryPath(int u, int v) {
    if (treeCompId[u] != treeCompId[v]) return {-1, -1};
    int best = max(blockWeight[u], blockWeight[v]);
    if (depth_[u] < depth_[v]) swap(u, v);
    int diff = depth_[u] - depth_[v];
    for (int k = 0; k < LOG_; k++) {
        if ((diff >> k) & 1) {
            best = max(best, upMax_[k][u]);
            u = up_[k][u];
        }
    }
    if (u == v) return {u, best};
    for (int k = LOG_ - 1; k >= 0; k--) {
        if (up_[k][u] != up_[k][v]) {
            best = max({best, upMax_[k][u], upMax_[k][v]});
            u = up_[k][u];
            v = up_[k][v];
        }
    }
    best = max({best, blockWeight[up_[0][u]], upMax_[0][u], upMax_[0][v]});
    return {up_[0][u], best};
}

int main() {
    while (true) {
        R = readInt(); C = readInt(); Q = readInt();
        if (R == 0 && C == 0 && Q == 0) break;

        edges.assign(C, {0,0});
        adj.assign(R + 1, {});
        for (int i = 0; i < C; i++) {
            int a = readInt(), b = readInt();
            edges[i] = {a, b};
            adj[a].push_back({b, i});
            adj[b].push_back({a, i});
        }

        buildBiconnected();
        int totalNodes = R + numBlocks;
        bfsBuildLCA(totalNodes);

        string out;
        for (int q = 0; q < Q; q++) {
            int s = readInt(), t = readInt();
            int ps = posOfVertex[s], pt = posOfVertex[t];
            auto [lca, mx] = queryPath(ps, pt);
            if (lca == -1) {
                out += "N\n";
            } else {
                out += (mx <= 2) ? "Y\n" : "N\n";
            }
        }
        out += "-\n";
        fwrite(out.data(), 1, out.size(), stdout);
    }
    return 0;
}