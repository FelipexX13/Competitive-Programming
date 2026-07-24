#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = (ll)4e18;

int main(){
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    
    // C[i][j]: piso i (1..n), habitacion j (0..k-1)
    vector<vector<ll>> C(n+1, vector<ll>(k));
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < k; j++)
            scanf("%lld", &C[i][j]);
    
    // adjOut[i][j]: mascara de habitaciones del piso i+1 alcanzables desde la habitacion j del piso i
    vector<vector<int>> adjOut(n+1, vector<int>(k, 0));
    for(int c = 0; c < m; c++){
        int f, u, v;
        scanf("%d %d %d", &f, &u, &v);
        adjOut[f][u-1] |= (1 << (v-1));
    }
    
    int SZ = 1 << k;
    int full = SZ - 1;
    
    vector<ll> r(SZ), h(SZ), g(SZ);
    vector<int> Nmask(SZ);
    
    // r[mask] para el piso 1: suma de C[1][j] para j en mask (sin cuello de botella, fuente directa)
    r[0] = 0;
    for(int mask = 1; mask < SZ; mask++){
        int lb = mask & (-mask);
        int j = __builtin_ctz(lb);
        r[mask] = r[mask ^ lb] + C[1][j];
    }
    
    vector<ll> ans(n+1);
    ans[1] = r[full];
    
    for(int i = 1; i <= n-1; i++){
        // h[B] = r[complemento de B] = flujo maximo usando SOLO las habitaciones de B
        for(int B = 0; B < SZ; B++) h[B] = r[full ^ B];
        
        // Nmask[B] = union de vecinos (piso i+1) de las habitaciones en B
        Nmask[0] = 0;
        for(int B = 1; B < SZ; B++){
            int lb = B & (-B);
            int j = __builtin_ctz(lb);
            Nmask[B] = Nmask[B ^ lb] | adjOut[i][j];
        }
        
        // g[N] = mejor (min) h[B] entre los B cuya vecindad es exactamente N
        fill(g.begin(), g.end(), INF);
        for(int B = 0; B < SZ; B++){
            int N = Nmask[B];
            if(h[B] < g[N]) g[N] = h[B];
        }
        
        // transformada tipo SOS: de g a r_{i+1}, procesando cada bit (habitacion del piso i+1)
        for(int mask = 0; mask < SZ; mask++) r[mask] = g[mask];
        for(int b = 0; b < k; b++){
            int bit = 1 << b;
            ll cap = C[i+1][b];
            for(int mask = 0; mask < SZ; mask++){
                if(mask & bit){
                    int m0 = mask ^ bit;
                    ll old0 = r[m0], old1 = r[mask];
                    r[m0] = min(old0, old1);
                    r[mask] = min(old0, old1 + cap);
                }
            }
        }
        
        ans[i+1] = r[full];
    }
    
    for(int t = 1; t <= n; t++){
        printf("%lld%c", ans[t], t==n?'\n':' ');
    }
    
    return 0;
}