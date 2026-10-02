// <3
// Tema: CSES / Dos Barridos sobre Rangos Ordenados
// Resumen: Para cada rango, si contiene a otro y si esta contenido en otro
// O: (n log n) por el sort; los dos barridos son lineales
// Uso: ordenar por (l creciente, r DECRECIENTE); un barrido con max r y otro con min r
// Detalle: Ordenado por inicio creciente, un rango esta CONTENIDO si algun rango anterior tiene
// un fin mayor o igual, asi que basta llevar el maximo r visto. Y CONTIENE a otro si algun
// rango posterior tiene fin menor o igual, que es el mismo barrido al reves con el minimo r. EL
// DESEMPATE ES LO QUE SE OLVIDA: con inicios iguales hay que ordenar por fin DECRECIENTE, para
// que el rango mas largo quede primero y se cuente como contenedor y no como contenido. Se
// guarda el id original porque la salida va en el orden de entrada, no en el ordenado.

#include <bits/stdc++.h>
using namespace std;

struct Range
{
    int l, r, id;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Range> a(n);

    for(int i = 0; i < n; i++)
    {
        cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }

    sort(a.begin(), a.end(), [](Range A, Range B)
    {
        if(A.l != B.l)
            return A.l < B.l;

        return A.r > B.r;
    });

    vector<int> contains(n, 0);
    vector<int> contained(n, 0);

    // Esta contenido por otro?
    int maxR = -1;

    for(int i = 0; i < n; i++)
    {
        if(maxR >= a[i].r)
            contained[a[i].id] = 1;

        maxR = max(maxR, a[i].r);
    }

    // Contiene a otro?
    int minR = INT_MAX;

    for(int i = n - 1; i >= 0; i--)
    {
        if(minR <= a[i].r)
            contains[a[i].id] = 1;

        minR = min(minR, a[i].r);
    }

    for(int x : contains)
        cout << x << ' ';

    cout << '\n';

    for(int x : contained)
        cout << x << ' ';

    cout << '\n';
}
