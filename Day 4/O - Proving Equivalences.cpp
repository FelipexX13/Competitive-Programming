#include <bits/stdc++.h>
using namespace std;

static char buf_[1 << 20];
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

int n, m;
vector<vector<int>> adj;
vector<int> disc_, low_, comp_;
vector<char> onStack_;
vector<int> tarjanStack;
int timer_, sccCount;

// Iterative Tarjan's SCC algorithm.
void tarjanSCC() {
    disc_.assign(n + 1, -1);
    low_.assign(n + 1, -1);
    comp_.assign(n + 1, -1);
    onStack_.assign(n + 1, 0);
    tarjanStack.clear();
    timer_ = 0;
    sccCount = 0;

    for (int s = 1; s <= n; s++) {
        if (disc_[s] != -1) continue;
        vector<array<int,2>> stk; // {vertex, nextIdx}
        stk.push_back({s, 0});
        disc_[s] = low_[s] = timer_++;
        tarjanStack.push_back(s);
        onStack_[s] = 1;

        while (!stk.empty()) {
            auto &fr = stk.back();
            int u = fr[0];
            if (fr[1] < (int)adj[u].size()) {
                int v = adj[u][fr[1]];
                fr[1]++;
                if (disc_[v] == -1) {
                    disc_[v] = low_[v] = timer_++;
                    tarjanStack.push_back(v);
                    onStack_[v] = 1;
                    stk.push_back({v, 0});
                } else if (onStack_[v]) {
                    low_[u] = min(low_[u], disc_[v]);
                }
            } else {
                stk.pop_back();
                if (!stk.empty()) {
                    int p = stk.back()[0];
                    low_[p] = min(low_[p], low_[u]);
                }
                if (low_[u] == disc_[u]) {
                    // pop the SCC
                    while (true) {
                        int w = tarjanStack.back();
                        tarjanStack.pop_back();
                        onStack_[w] = 0;
                        comp_[w] = sccCount;
                        if (w == u) break;
                    }
                    sccCount++;
                }
            }
        }
    }
}

int main() {
    int T = readInt();
    string out;
    while (T--) {
        n = readInt(); m = readInt();
        adj.assign(n + 1, {});
        vector<pair<int,int>> rawEdges(m);
        for (int i = 0; i < m; i++) {
            int a = readInt(), b = readInt();
            rawEdges[i] = {a, b};
            adj[a].push_back(b);
        }

        tarjanSCC();

        vector<char> hasIn(sccCount, 0), hasOut(sccCount, 0);
        for (auto &e : rawEdges) {
            int ca = comp_[e.first], cb = comp_[e.second];
            if (ca != cb) {
                hasOut[ca] = 1;
                hasIn[cb] = 1;
            }
        }

        int ans;
        if (sccCount <= 1) {
            ans = 0;
        } else {
            int sources = 0, sinks = 0;
            for (int i = 0; i < sccCount; i++) {
                if (!hasIn[i]) sources++;
                if (!hasOut[i]) sinks++;
            }
            ans = max(sources, sinks);
        }
        out += to_string(ans);
        out += "\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}