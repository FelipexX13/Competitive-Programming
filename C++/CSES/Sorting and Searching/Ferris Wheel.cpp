// <3
// Tema: CSES / Dos Punteros desde los Extremos
// Resumen: Minimo de gondolas para subir a todos, con dos personas por gondola y limite de peso
// O: (n log n) por el sort; el barrido es lineal
// Uso: ordenar; si a[l] + a[r] <= x suben juntos, si no el grande sube solo
// Detalle: Se ordena y se mira al MAS PESADO: o le cabe el mas liviano al lado, o sube solo. No
// hay tercera opcion, porque si el mas liviano no le cabe, ningun otro tampoco. Ese argumento
// es el que vuelve correcto el greedy, y es el mismo de casi todos los problemas de emparejar
// con tope: mirar el elemento mas restringido primero.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;

    vector<int> a(n);

    for(int &v : a)
        cin >> v;

    sort(a.begin(), a.end());

    int l = 0;
    int r = n - 1;
    int ans = 0;

    while(l <= r)
    {
        if(a[l] + a[r] <= x)
        {
            // El mas pequeno y el mas grande caben juntos
            l++;
            r--;
        }
        else
        {
            // El mas grande necesita una gondola solo
            r--;
        }

        ans++;
    }

    cout << ans << '\n';
}
