// <3
// Tema: Graph / Max Flow
// Resuelve "March of the Penguins": hay N tempanos de hielo con coordenadas (x,y), cada uno con
// n_i pinguinos y un limite m_i de saltos que se pueden dar desde el (un pinguino puede saltar
// de un tempano a otro si la distancia entre ellos es <= D); hay que hallar todos los tempanos
// donde TODOS los pinguinos puedan terminar reunidos sin que ningun tempano se quede sin saltos.
// Para cada tempano candidato t, arma una red de flujo con nodos entrada/salida por tempano
// (in=i, out=N+i) donde la arista in->out tiene capacidad m_i (presupuesto de saltos), una
// fuente S conectada a cada tempano con capacidad n_i (pinguinos que parten de ahi), y aristas
// de capacidad infinita entre tempanos alcanzables saltando; corre Dinic (maxflow) de S a t y,
// si el flujo maximo iguala al total de pinguinos, t es una respuesta valida.

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to; int cap; int flow; };
    int n;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> level, it;
    Dinic(int n=0): n(n), g(n) {}
    int addEdge(int from,int to,int cap){
        g[from].push_back((int)edges.size());
        edges.push_back({to,cap,0});
        g[to].push_back((int)edges.size());
        edges.push_back({from,0,0});
        return (int)edges.size()-2;
    }
    void resetFlow(){ for(auto &e: edges) e.flow = 0; }
    bool bfs(int s,int t){
        level.assign(n,-1);
        queue<int>q; level[s]=0;q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int id: g[u]){
                auto &e=edges[id];
                if(e.cap - e.flow>0 && level[e.to]<0){
                    level[e.to]=level[u]+1;
                    q.push(e.to);
                }
            }
        }
        return level[t]>=0;
    }
    int dfs(int u,int t,int f){
        if(u==t) return f;
        for(int &i=it[u]; i<(int)g[u].size(); i++){
            int id=g[u][i];
            auto &e=edges[id];
            if(e.cap-e.flow>0 && level[e.to]==level[u]+1){
                int d=dfs(e.to,t,min(f,e.cap-e.flow));
                if(d>0){ e.flow+=d; edges[id^1].flow-=d; return d; }
            }
        }
        return 0;
    }
    int maxflow(int s,int t){
        int flow=0;
        while(bfs(s,t)){
            it.assign(n,0);
            int f;
            while((f=dfs(s,t,INT_MAX))>0) flow+=f;
        }
        return flow;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if(!(cin >> T)) return 0;
    while(T--){
        int N; double D;
        cin >> N >> D;
        vector<double> x(N), y(N);
        vector<int> n(N), m(N);
        for(int i=0;i<N;i++) cin >> x[i] >> y[i] >> n[i] >> m[i];

        int totalPenguins = 0;
        for(int i=0;i<N;i++) totalPenguins += n[i];

        vector<vector<bool>> canJump(N, vector<bool>(N,false));
        const double eps = 1e-6;
        for(int i=0;i<N;i++)
            for(int j=i+1;j<N;j++){
                double dx = x[i]-x[j], dy = y[i]-y[j];
                double dist = sqrt(dx*dx+dy*dy);
                if(dist <= D + eps) canJump[i][j] = canJump[j][i] = true;
            }

        // in_node(i)=i, out_node(i)=N+i, S=2N
        int S = 2*N;
        int numNodes = 2*N+1;
        Dinic dinic(numNodes);

        for(int i=0;i<N;i++) dinic.addEdge(i, N+i, m[i]);   // presupuesto de saltos
        for(int i=0;i<N;i++) dinic.addEdge(S, i, n[i]);      // pingüinos que parten de i

        const int INF = 1000000;
        for(int i=0;i<N;i++)
            for(int j=i+1;j<N;j++)
                if(canJump[i][j]){
                    dinic.addEdge(N+i, j, INF);
                    dinic.addEdge(N+j, i, INF);
                }

        vector<int> answer;
        for(int t=0;t<N;t++){
            dinic.resetFlow();
            int f = dinic.maxflow(S, t); // sink = in_node(t)
            if(f == totalPenguins) answer.push_back(t);
        }

        if(answer.empty()) cout << -1 << "\n";
        else {
            for(size_t i=0;i<answer.size();i++){
                if(i) cout << ' ';
                cout << answer[i];
            }
            cout << "\n";
        }
    }
    return 0;
}