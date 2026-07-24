#include <bits/stdc++.h>
using namespace std;

using ll = long long;



const int MX = 100000000;



vector<bool> marked(MX + 1,false);
int cont = 0;


void sieve(int uwu) {
        marked[0] = marked[1] = true;
    
        for (int i = 2; i <= MX; i++) {
            if (marked[i]) continue;

            if(i <= uwu)
            {
                cont++;
            }
            if (1LL * i * i > MX) continue;
            for (ll j = 1LL * i * i; j <= MX; j += i)
                marked[j] = true;
        }
    }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;

    sieve(t);
    
    int n; cin >> n;
    cout << cont << endl;
    while (n--) {
        int aa; cin >> aa;
        
        if(marked[aa]==false)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }

    return 0;
}