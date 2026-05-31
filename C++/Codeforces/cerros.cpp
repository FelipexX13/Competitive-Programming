// <3
// Tema: Greedy / Segment Counting
// Cuenta la cantidad de segmentos contiguos con elementos >= k en un arreglo.
// Cada vez que encuentra un elemento >= k después de uno < k, incrementa el contador.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n,k;
    cin >> n >> k;
    long long god=0;
    bool abierto = false;
    for(int i = 0; i < n;i++)
    {
        int a; cin >> a;

        if(a>=k&&!abierto)
        {
            god++;
            abierto = true;
        }
        else if(a<k)
        {
            abierto = false;
        }
    }

    cout << god << "\n";

    return 0;
}