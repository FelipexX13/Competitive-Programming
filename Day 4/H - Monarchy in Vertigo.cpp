#include <bits/stdc++.h>
using namespace std;

static int N;
static vector<int> seg;

void update(int node, int lo, int hi, int pos, int val) {
    if (lo == hi) { seg[node] = val; return; }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(node<<1, lo, mid, pos, val);
    else update(node<<1|1, mid+1, hi, pos, val);
    seg[node] = seg[node<<1] | seg[node<<1|1];
}

int queryFirstAlive(int node, int lo, int hi) {
    if (seg[node] == 0) return -1;
    if (lo == hi) return lo;
    int mid = (lo + hi) >> 1;
    int r = queryFirstAlive(node<<1, lo, mid);
    if (r != -1) return r;
    return queryFirstAlive(node<<1|1, mid+1, hi);
}

int main(){
    int Q;
    scanf("%d", &Q);
    vector<int> type(Q), arg(Q);
    for (int i = 0; i < Q; i++) scanf("%d %d", &type[i], &arg[i]);

    int births = 0;
    for (int i = 0; i < Q; i++) if (type[i] == 1) births++;
    N = births + 1;                    // total number of people that will ever exist

    vector<vector<int>> children(N + 1);
    vector<int> childId(Q, -1);
    int nextId = 2;
    for (int i = 0; i < Q; i++) {
        if (type[i] == 1) {
            int cid = nextId++;
            children[arg[i]].push_back(cid);
            childId[i] = cid;
        }
    }

    // Pre-order numbering of the FINAL tree (birth order never changes relative order)
    vector<int> rankOf(N + 1), idAtRank(N + 1);
    vector<int> st; st.reserve(N + 1);
    st.push_back(1);
    int cur = 0;
    while (!st.empty()) {
        int u = st.back(); st.pop_back();
        rankOf[u] = ++cur;
        idAtRank[cur] = u;
        for (int i = (int)children[u].size() - 1; i >= 0; i--) st.push_back(children[u][i]);
    }

    seg.assign(4 * (N + 1), 0);
    update(1, 1, N, rankOf[1], 1);      // Constant starts alive

    string out; out.reserve(Q * 7);
    for (int i = 0; i < Q; i++) {
        if (type[i] == 1) {
            update(1, 1, N, rankOf[childId[i]], 1);
        } else {
            update(1, 1, N, rankOf[arg[i]], 0);
            int pos = queryFirstAlive(1, 1, N);
            out += to_string(idAtRank[pos]);
            out += '\n';
        }
    }
    fputs(out.c_str(), stdout);
    return 0;
}