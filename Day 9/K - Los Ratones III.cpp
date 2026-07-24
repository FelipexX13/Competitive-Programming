#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007LL;
const int MAXN = 100005;

struct Edge{
    int to;
    ll w;
};

int N,Q;

vector<Edge> g[MAXN];

int parent[MAXN], depth[MAXN], heavy[MAXN], sz[MAXN];
int head[MAXN], pos[MAXN];
ll val[MAXN];
int curPos;

struct Node{
    ll sum,lazy;
};

Node seg[4*MAXN];

int dfs(int v,int p){
    parent[v]=p;
    sz[v]=1;
    heavy[v]=-1;
    int mx=0;
    for(auto e:g[v]){
        if(e.to==p) continue;
        depth[e.to]=depth[v]+1;
        val[e.to]=e.w;
        dfs(e.to,v);
        sz[v]+=sz[e.to];
        if(sz[e.to]>mx){
            mx=sz[e.to];
            heavy[v]=e.to;
        }
    }
    return sz[v];
}

ll base[MAXN];

void decompose(int v,int h){
    head[v]=h;
    pos[v]=++curPos;
    base[curPos]=val[v];

    if(heavy[v]!=-1)
        decompose(heavy[v],h);

    for(auto e:g[v]){
        if(e.to==parent[v] || e.to==heavy[v]) continue;
        decompose(e.to,e.to);
    }
}

void build(int node,int l,int r){
    seg[node].lazy=1;
    if(l==r){
        seg[node].sum=base[l]%MOD;
        return;
    }
    int mid=(l+r)>>1;
    build(node<<1,l,mid);
    build(node<<1|1,mid+1,r);
    seg[node].sum=(seg[node<<1].sum+seg[node<<1|1].sum)%MOD;
}

void push(int node,int l,int r){
    if(seg[node].lazy==1) return;
    ll x=seg[node].lazy;
    seg[node].sum=seg[node].sum*x%MOD;
    if(l!=r){
        seg[node<<1].lazy=seg[node<<1].lazy*x%MOD;
        seg[node<<1|1].lazy=seg[node<<1|1].lazy*x%MOD;
    }
    seg[node].lazy=1;
}

void update(int node,int l,int r,int ql,int qr,ll x){
    push(node,l,r);
    if(r<ql||qr<l) return;
    if(ql<=l&&r<=qr){
        seg[node].lazy=x%MOD;
        push(node,l,r);
        return;
    }
    int mid=(l+r)>>1;
    update(node<<1,l,mid,ql,qr,x);
    update(node<<1|1,mid+1,r,ql,qr,x);
    seg[node].sum=(seg[node<<1].sum+seg[node<<1|1].sum)%MOD;
}

ll query(int node,int l,int r,int ql,int qr){
    push(node,l,r);
    if(r<ql||qr<l) return 0;
    if(ql<=l&&r<=qr) return seg[node].sum;
    int mid=(l+r)>>1;
    return (query(node<<1,l,mid,ql,qr)+
            query(node<<1|1,mid+1,r,ql,qr))%MOD;
}

void path_update(int a,int b,ll x){
    while(head[a]!=head[b]){
        if(depth[head[a]]<depth[head[b]]) swap(a,b);
        update(1,1,N,pos[head[a]],pos[a],x);
        a=parent[head[a]];
    }
    if(depth[a]>depth[b]) swap(a,b);
    if(pos[a]+1<=pos[b])
        update(1,1,N,pos[a]+1,pos[b],x);
}

ll path_query(int a,int b){
    ll ans=0;
    while(head[a]!=head[b]){
        if(depth[head[a]]<depth[head[b]]) swap(a,b);
        ans=(ans+query(1,1,N,pos[head[a]],pos[a]))%MOD;
        a=parent[head[a]];
    }
    if(depth[a]>depth[b]) swap(a,b);
    if(pos[a]+1<=pos[b])
        ans=(ans+query(1,1,N,pos[a]+1,pos[b]))%MOD;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>N>>Q;

    for(int i=1;i<N;i++){
        int u,v;
        ll c;
        cin>>u>>v>>c;
        g[u].push_back({v,c});
        g[v].push_back({u,c});
    }

    depth[1]=0;
    val[1]=0;

    dfs(1,0);
    decompose(1,1);

    build(1,1,N);

    while(Q--){
        int u,v;
        ll x;
        cin>>u>>v>>x;

        path_update(u,v,x);
        cout<<path_query(u,v)%MOD<<"\n";
    }

    return 0;
}