// <3
// Tema: Greedy / Sliding Window
// O: (n) amortizado, cada elemento entra y sale una vez
// Uso: exige condicion monotona; con negativos NO sirve, usa prefijos + map
// Ventana de tamano variable para hallar el subarreglo mas largo que cumple una condicion
// monotona (suma <= K, a lo sumo K distintos, etc). Cada elemento entra y sale de la ventana
// a lo sumo una vez, asi que el costo total es O(n) aunque haya dos ciclos anidados.
// La condicion tiene que ser monotona: si un rango cumple, cualquier subrango tambien debe
// cumplir. Por eso funciona con sumas de numeros no negativos, pero NO si el arreglo tiene
// negativos (ahi encoger la ventana no garantiza reducir la suma y hay que usar prefijos con
// un map o un deque monotono).

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long K;
    cin >> n >> K;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 0;
    long long cur = 0, ans = 0;

    for (int r = 0; r < n; r++)
    {
        cur += a[r];
        while (cur > K)
        {
            cur -= a[l];
            l++;
        }
        ans = max(ans, (long long)(r - l + 1));
    }

    cout << ans << "\n";
    return 0;
}
