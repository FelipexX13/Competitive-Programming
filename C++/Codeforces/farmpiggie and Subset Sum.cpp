// <3
// Tema: Combinatorics / Construction
// Problema de construccion (el nombre sugiere relacion con subconjuntos de suma prohibida):
// arma una permutacion de 1..n intercambiando cada pareja de consecutivos (p[1]=2, p[2]=1,
// p[3]=4, p[4]=3, ...), de forma que p[i] != i para todo i (derangement simple) y cada indice
// queda emparejado con su vecino inmediato.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
 
        vector<int> p(n + 1);
        for (int i = 1; i <= n; i += 2) {
            p[i] = i + 1;
            p[i + 1] = i;
        }
 
        for (int i = 1; i <= n; i++) {
            cout << p[i];
            if (i != n) cout << ' ';
        }
        cout << "\n";
    }
 
    return 0;
}