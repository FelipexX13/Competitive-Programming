// <3
// Tema: Graph / Tree Degree Analysis
// Calcula cuántos pares de nodos pueden removerse de un árbol para desconectarlo.
// Es n menos la suma de los dos mayores grados de los nodos.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> deg(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;

        deg[a]++;
        deg[b]++;
    }

    int mx1 = 0, mx2 = 0;

    for (int i = 1; i <= n; i++) {
        if (deg[i] >= mx1) {
            mx2 = mx1;
            mx1 = deg[i];
        } else if (deg[i] > mx2) {
            mx2 = deg[i];
        }
    }

    cout << n - mx1 - mx2 << '\n';

    return 0;
}