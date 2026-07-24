#include <bits/stdc++.h>
using namespace std;

using pii = pair<long long, int>;

const long long INF = 1e18;

long long dijkstra(unordered_map<int, vector<pair<int, int>>> &graph, int start, int target) {
    unordered_map<int, long long> dist;
    unordered_set<int> visited;

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited.count(u))
            continue;
        visited.insert(u);

        if (u == target)
            return d;

        for (auto [v, w] : graph[u]) {

            long long nd = d + w;

            if (!dist.count(v) || nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    if (dist.count(target))
        return dist[target];
    return INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    unordered_map<int, vector<pair<int, int>>> graph;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    for (int i = 1; i <= n; i++) {
        int tel;
        cin >> tel;

        for (int j = 0; j < tel; j++) {
            int t, w;
            cin >> t >> w;

            int virtual_node = n + t;

            graph[i].push_back({virtual_node, w});
            graph[virtual_node].push_back({i, 0});
        }
    }

    long long costo = dijkstra(graph, 1, n);
    cout << costo << "\n";

    return 0;
}