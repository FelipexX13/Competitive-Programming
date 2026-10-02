// <3
// Tema: CSES / Dos Punteros sobre Dos Listas Ordenadas
// Resumen: Cuantos solicitantes se pueden emparejar con un apartamento dentro de una tolerancia k
// O: (n log n + m log m) por los dos sort; el barrido es lineal
// Uso: ordenar los dos; avanzar el puntero del que no puede emparejarse
// Detalle: Se ordenan las dos listas y se barren con dos punteros. Si la pareja actual calza
// (la diferencia no pasa de k) se cuenta y avanzan los dos; si no, se descarta el que NO tiene
// arreglo: si el apartamento es muy chico para este solicitante, tampoco le sirve a ninguno mas
// grande, asi que se bota el apartamento. Ese razonamiento de 'cual de los dos no puede
// mejorar' es lo que hace valido el greedy.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), b(m);

    for(int &x : a)
        cin >> x;

    for(int &x : b)
        cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0;
    int j = 0;
    int ans = 0;

    while(i < n && j < m)
    {
        if(abs(a[i] - b[j]) <= k)
        {
            ans++;
            i++;
            j++;
        }
        else if(b[j] < a[i] - k)
        {
            // El apartamento es demasiado pequeno
            j++;
        }
        else
        {
            // El apartamento es demasiado grande
            i++;
        }
    }

    cout << ans << '\n';
}
