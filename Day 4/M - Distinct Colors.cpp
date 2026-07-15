#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) cin >> color[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.reserve(n);

    // DFS iterativo (evita overflow de pila en arboles muy profundos, tipo cadena)
    vector<int> stck;
    stck.reserve(n);
    vector<char> visited(n + 1, 0);
    stck.push_back(1);
    visited[1] = 1;
    while (!stck.empty()) {
        int u = stck.back();
        stck.pop_back();
        order.push_back(u);
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                stck.push_back(v);
            }
        }
    }

    // Invertimos el preorder: en este orden, cada hijo aparece antes que su padre,
    // asi que al procesar u, todos sus hijos ya estan listos.
    reverse(order.begin(), order.end());

    vector<set<int>> colorSet(n + 1);
    vector<int> ans(n + 1, 0);

    for (int u = 1; u <= n; u++) colorSet[u].insert(color[u]);

    // Small-to-large merging: siempre fusionamos el set mas chico dentro del mas grande
    for (int u : order) {
        for (int v : adj[u]) {
            if (v != parent[u]) { // v es hijo de u
                if (colorSet[u].size() < colorSet[v].size())
                    colorSet[u].swap(colorSet[v]); // swap de sets es O(1), no copia elementos
                colorSet[u].insert(colorSet[v].begin(), colorSet[v].end());
                colorSet[v].clear(); // liberamos memoria que ya no se necesita
            }
        }
        ans[u] = (int)colorSet[u].size();
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i];
        cout << (i < n ? ' ' : '\n');
    }

    return 0;
}