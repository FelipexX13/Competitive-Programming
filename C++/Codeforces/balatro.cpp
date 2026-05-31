// <3
// Tema: Greedy / Sorted Pairing
// Calcula la suma de diferencias absolutas entre pares ordenados de dos arreglos.
// Ordena ambos y suma las diferencias elemento a elemento.

#include <bits/stdc++.h>

using namespace std;

int main() {
    
    long long n;
    cin >> n;
    vector<long long > yo(n);
    vector<long long > atk(n);

    for(int i = 0; i<n ; i++)
    {
        long long a;
        cin >> a;
        yo[i] = a;
    }
    
    for(int i = 0; i<n ; i++)
    {
        long long a;
        cin >> a;
        atk[i] = a;
    }

    long long ans = 0;
    
    sort(yo.begin(), yo.end());
    sort(atk.begin(), atk.end());

    for(int i = 0; i<n ; i++)
    {
        ans+= abs(atk[i] - yo[i]);
    }
    
    cout << ans << endl;
    
    return 0;
}