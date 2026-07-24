#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;
    const int INF = INT_MAX;
    HopcroftKarp(int n=0, int m=0): n(n), m(m), adj(n), matchL(n,-1), matchR(m,-1), dist(n) {}
    void addEdge(int u,int v){ adj[u].push_back(v); }
    bool bfs(){
        queue<int> q;
        for(int u=0;u<n;u++){
            if(matchL[u]==-1){ dist[u]=0; q.push(u); }
            else dist[u]=INF;
        }
        bool found=false;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v: adj[u]){
                int w = matchR[v];
                if(w==-1){ found=true; }
                else if(dist[w]==INF){ dist[w]=dist[u]+1; q.push(w); }
            }
        }
        return found;
    }
    bool dfs(int u){
        for(int v: adj[u]){
            int w = matchR[v];
            if(w==-1 || (dist[w]==dist[u]+1 && dfs(w))){
                matchL[u]=v; matchR[v]=u;
                return true;
            }
        }
        dist[u]=INF;
        return false;
    }
    int maxMatching(){
        int result=0;
        while(bfs()){
            for(int u=0;u<n;u++){
                if(matchL[u]==-1){
                    if(dfs(u)) result++;
                }
            }
        }
        return result;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while(cin >> N){
        vector<string> grid(N);
        for(auto &s: grid) cin >> s;

        vector<vector<int>> rowId(N, vector<int>(N,-1));
        vector<vector<int>> colId(N, vector<int>(N,-1));
        int R=0, C=0;

        // etiqueta cada tramo horizontal de casillas vacías
        for(int i=0;i<N;i++){
            int j=0;
            while(j<N){
                if(grid[i][j]=='X'){ j++; continue; }
                while(j<N && grid[i][j]=='.'){ rowId[i][j]=R; j++; }
                R++;
            }
        }
        // etiqueta cada tramo vertical de casillas vacías
        for(int j=0;j<N;j++){
            int i=0;
            while(i<N){
                if(grid[i][j]=='X'){ i++; continue; }
                while(i<N && grid[i][j]=='.'){ colId[i][j]=C; i++; }
                C++;
            }
        }

        HopcroftKarp hk(R,C);
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                if(grid[i][j]=='.')
                    hk.addEdge(rowId[i][j], colId[i][j]);

        cout << hk.maxMatching() << "\n";
    }
    return 0;
}