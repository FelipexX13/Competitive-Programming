// <3
// Tema: Math / Sieve of Eratosthenes
// Resuelve "Prime Sieve" (Kattis): dado un limite n (hasta 10^8) y q consultas x, pide primero
// cuantos numeros primos hay menores o iguales a n, y luego para cada consulta si x es primo
// (1) o compuesto (0). Implementa una criba de Eratosthenes clasica sobre el vector `marked`
// (marca compuestos empezando en i*i para evitar overflow con 1LL*i*i), contando los primos
// menores o iguales al limite pedido en la variable `cont` mientras criba, y responde cada
// consulta en O(1) revisando `marked[aa]`.

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