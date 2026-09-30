// <3
// Tema: Graph / Circuito Euleriano (Algoritmo de Hierholzer)
// Resuelve "Mail Delivery" (Contest 05 [Avanzados], problema J): dado un plano de n cruces y m
// calles bidireccionales, hay que encontrar una ruta que empiece y termine en la oficina postal
// (cruce 1) y recorra cada calle exactamente una vez, o determinar que es imposible.
// Primero verifica las condiciones de existencia de un circuito euleriano: todo vertice debe
// tener grado par, y todos los vertices con aristas deben ser alcanzables desde el vertice 1
// (BFS). Luego construye el circuito con el algoritmo de Hierholzer de forma iterativa (pila st
// y arreglo ptr por vertice, marcando usedEdge), y revierte el resultado para obtener la ruta
// final.

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1); // (to, edge_id)
    vector<int> deg(n + 1, 0);

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        deg[a]++;
        deg[b]++;
    }

    // 1) every vertex must have even degree
    for(int v = 1; v <= n; v++){
        if(deg[v] % 2 != 0){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // 2) all vertices that have edges must be reachable from vertex 1
    //    (this also catches the case where vertex 1 itself has no edges but m > 0)
    vector<bool> visited(n + 1, false);
    queue<int> bfsQ;
    bfsQ.push(1);
    visited[1] = true;
    int reached = 0;
    while(!bfsQ.empty()){
        int u = bfsQ.front(); bfsQ.pop();
        reached++;
        for(auto &pr : adj[u]){
            int v = pr.first;
            if(!visited[v]){
                visited[v] = true;
                bfsQ.push(v);
            }
        }
    }

    int totalWithEdges = 0;
    for(int v = 1; v <= n; v++){
        if(deg[v] > 0) totalWithEdges++;
    }

    if(reached < totalWithEdges){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // 3) Hierholzer's algorithm (iterative) to build the Eulerian circuit
    vector<int> ptr(n + 1, 0);
    vector<bool> usedEdge(m, false);
    vector<int> circuit;
    circuit.reserve(m + 1);

    vector<int> st;
    st.reserve(m + 1);
    st.push_back(1);

    while(!st.empty()){
        int v = st.back();
        if(ptr[v] < (int)adj[v].size()){
            auto [to, eid] = adj[v][ptr[v]];
            ptr[v]++;
            if(usedEdge[eid]) continue;
            usedEdge[eid] = true;
            st.push_back(to);
        } else {
            circuit.push_back(v);
            st.pop_back();
        }
    }

    reverse(circuit.begin(), circuit.end());

    // circuit must use exactly m edges -> m+1 vertices, and start/end at 1
    if((int)circuit.size() != m + 1 || circuit.front() != 1 || circuit.back() != 1){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for(int i = 0; i < (int)circuit.size(); i++){
        cout << circuit[i];
        if(i + 1 < (int)circuit.size()) cout << ' ';
    }
    cout << "\n";

    return 0;
}