// <3
// Tema: CSES / Contar Descensos en las Posiciones
// Resumen: Cuantas pasadas hacen falta para recoger 1..n en orden, avanzando siempre a la derecha
// O: (n), una pasada
// Uso: pos[x] = donde esta x; respuesta = 1 + cuantas veces pos[i] > pos[i+1]
// Detalle: Tres lineas, y toda la gracia esta en darle la vuelta al arreglo: en vez de guardar
// que numero hay en cada posicion, se guarda en que POSICION esta cada numero. Con eso, hace
// falta una pasada nueva exactamente cuando el numero i+1 esta ANTES que el i, porque ya se
// paso de largo. La respuesta es 1 mas la cantidad de esos descensos. Pasar de 'valor en la
// posicion' a 'posicion del valor' es un cambio de punto de vista que resuelve muchos problemas
// de permutaciones.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> pos(n + 1);

    for(int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        pos[x] = i;
    }

    int ans = 1;

    for(int i = 1; i < n; i++)
    {
        if(pos[i] > pos[i + 1])
            ans++;
    }

    cout << ans << '\n';
}
