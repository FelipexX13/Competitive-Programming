// <3
// Tema: Math / Tecnica de Contribucion
// Resuelve "Bytelandia's stones": dado un arreglo a_1..a_n, se pide la suma de
// S(L,R) = suma de a_i en [L,R] sobre TODOS los pares (L,R) posibles. En vez
// de calcular cada subarreglo, usa la tecnica de contribucion: cada elemento
// a_i aparece en exactamente i*(n-i+1) subarreglos [L,R] (eligiendo L en
// [1,i] y R en [i,n]), asi que la respuesta es la suma de x * i * (n-i+1)
// para cada valor x leido en la posicion i, acumulada en O(n).

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long ans = 0;

    for (int i = 1; i <= n; i++) 
    {
        long long x;
        cin >> x;
        ans += x * 1LL * i * (n - i + 1);
    }

    cout << ans << endl;
    return 0;
}