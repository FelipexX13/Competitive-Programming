// <3
// Tema: Math / Divisors
// Resuelve "Aesthetics in poetry": dado un poema de N versos con longitudes l_1..l_N, hay que
// hallar el menor entero K>1 (K-elegante) tal que N sea multiplo de K y, para cada resto
// i=0..K-1 al dividir las longitudes por K, haya exactamente N/K versos con ese resto (o -1 si
// no existe tal K).
// Genera todos los divisores de N (funcion divisores), los ordena ascendentemente y para cada
// candidato k>=2 cuenta en cont[v%k] cuantos versos caen en cada resto, verificando que todos
// los conteos sean iguales a n/k; el primer k que cumple es la respuesta minima.

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<ll> divisores(ll n) 
{
    vector<ll> div;
    for(ll i = 1; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            div.push_back(i);
            if(i != n/i) div.push_back(n/i);
        }
    }
    return div;
}

int main()
{
    ll n; cin >> n;
    vector<ll> xd(n);
    for(int i = 0; i < n; i++) 
    {
        cin >> xd[i];
    }
    
    vector<ll> juan = divisores(n); 
    sort(juan.begin(), juan.end());
    
    for(ll k : juan)
    {
        if(k >= 2) 
        {
        
            vector<ll> cont(k, 0);
            for(ll v : xd) 
            {
                cont[v % k]++;
            }
            
            bool ok = true;
            for(ll c : cont)
            {
                if(c != n/k) { ok = false; break; }
            }
            
            if(ok)
            {
                cout << k << endl;
                return 0;
            }
        }
    }
    
    cout << -1 << endl;
    return 0;
}