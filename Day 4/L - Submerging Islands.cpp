#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

vector<int> adj[MAXN];
int disc[MAXN], low[MAXN], timer;
bool visited[MAXN], articulation[MAXN];

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    int children = 0;

    for (int v : adj[u]) {
        if (!visited[v]) {
            children++;
            dfs(v, u);

            low[u] = min(low[u], low[v]);

            if (parent != -1 && low[v] >= disc[u])
                articulation[u] = true;
        }
        else if (v != parent) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (parent == -1 && children > 1)
        articulation[u] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;

    while (cin >> N >> M && (N || M)) {

        for (int i = 1; i <= N; i++) {
            adj[i].clear();
            visited[i] = false;
            articulation[i] = false;
        }

        timer = 0;

        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Por si el grafo no fuera conexo.
        for (int i = 1; i <= N; i++)
            if (!visited[i])
                dfs(i, -1);

        int ans = 0;
        for (int i = 1; i <= N; i++)
            if (articulation[i])
                ans++;

        cout << ans << '\n';
    }

    return 0;
}