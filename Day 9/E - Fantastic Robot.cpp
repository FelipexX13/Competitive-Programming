#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
const ll INF = 1e18;
 
 
int n,m;
 
vector<vector<int>> mat;
vector<string> comandos;
 
 
vector<tuple<int,int,int>> generar_vecinos(int x, int y){
 
    vector<tuple<int,int,int>> vecinos;
 
 
    for(string &cmd : comandos){
 
        int xi=x;
        int yi=y;
        int pasos=0;
 
 
        for(char c: cmd){
 
            if(c=='U'){
                pasos++;
                xi--;
 
                if(xi<0 || mat[xi][yi]==1){
                    pasos--;
                    xi++;
                }
 
            }else if(c=='D'){
 
                pasos++;
                xi++;
 
                if(xi>=n || mat[xi][yi]==1){
                    pasos--;
                    xi--;
                }
 
            }else if(c=='L'){
 
                pasos++;
                yi--;
 
                if(yi<0 || mat[xi][yi]==1){
                    pasos--;
                    yi++;
                }
 
            }else{
 
                pasos++;
                yi++;
 
                if(yi>=m || mat[xi][yi]==1){
                    pasos--;
                    yi--;
                }
            }
        }
 
 
        vecinos.push_back({xi,yi,pasos});
    }
 
 
    return vecinos;
}
 
 
 
int main(){
 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
 
    cin>>n>>m;
 
 
    mat.assign(n,vector<int>(m));
 
 
    for(int i=0;i<n;i++){
 
        string s;
        cin>>s;
 
        for(int j=0;j<m;j++)
            mat[i][j]=s[j]-'0';
 
    }
 
 
    int sx,sy;
    cin>>sx>>sy;
 
 
    int tx,ty;
    cin>>tx>>ty;
 
 
    int k;
    cin>>k;
 
 
    comandos.resize(k);
 
    for(auto &x:comandos)
        cin>>x;
 
 
 
    vector<vector<ll>> dist(n, vector<ll>(m,INF));
 
 
    priority_queue<
        tuple<ll,int,int>,
        vector<tuple<ll,int,int>>,
        greater<tuple<ll,int,int>>
    > pq;
 
 
    dist[sx][sy]=0;
 
    pq.push({0,sx,sy});
 
 
    while(!pq.empty()){
 
 
        auto [d,x,y]=pq.top();
        pq.pop();
 
 
        if(d!=dist[x][y])
            continue;
 
 
        if(x==tx && y==ty)
            break;
 
 
 
        for(auto [nx,ny,costo] : generar_vecinos(x,y)){
 
 
            if(dist[nx][ny] > d+costo){
 
                dist[nx][ny]=d+costo;
 
                pq.push({
                    dist[nx][ny],
                    nx,
                    ny
                });
            }
        }
 
    }
 
 
    if(dist[tx][ty]==INF)
        cout<<-1<<"\n";
    else
        cout<<dist[tx][ty]<<"\n";
 
}