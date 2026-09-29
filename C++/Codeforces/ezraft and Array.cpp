// <3
// Tema: Math / Construction
// Problema de construccion estilo Codeforces: para cada n, imprime un arreglo de n enteros
// positivos (o -1 si n=2, caso imposible). Para n=1 usa [1]; para n>=3 arranca con [1,2,3] y
// cada elemento siguiente se hace igual a la suma acumulada de todos los anteriores
// (duplicandola en cada paso), construyendo una secuencia donde cada nuevo termino "rompe" el
// balance de las sumas de prefijos previas.

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
 
        if (n == 2) {
            cout << -1 << "\n";
            continue;
        }
 
        vector<long long> a;
        if (n == 1) {
            a = {1};
        } else {
            a = {1, 2, 3};
            long long S = 6;
            for (int i = 4; i <= n; i++) {
                a.push_back(S);
                S *= 2;
            }
        }
 
        for (size_t i = 0; i < a.size(); i++) {
            cout << a[i];
            if (i + 1 != a.size()) cout << ' ';
        }
        cout << "\n";
    }
    return 0;
}