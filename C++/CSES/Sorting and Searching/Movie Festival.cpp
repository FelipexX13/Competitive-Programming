// <3
// Tema: CSES / Interval Scheduling (Ordenar por FIN)
// Resumen: Maximo de peliculas que se pueden ver completas sin solaparse
// O: (n log n) por el sort; el barrido es lineal
// Uso: ordenar por el FIN y tomar toda pelicula que empiece despues del ultimo fin
// Detalle: El greedy clasico, y lo unico que hay que acordarse es que se ordena por hora de
// FIN, no de inicio. La razon: terminar lo antes posible es lo que deja mas espacio para lo que
// viene, y una pelicula que empieza temprano pero termina tardisimo bloquea a varias. Ordenar
// por inicio, o por duracion, da respuestas peores. OJO: usa auto [a,b], que pide C++17.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int,int>> movies(n);

    for(auto &[a,b] : movies)
        cin >> a >> b;

    sort(movies.begin(), movies.end(),
        [](auto &a, auto &b)
        {
            return a.second < b.second;
        });

    int ans = 0;
    int last = 0;

    for(auto [start, finish] : movies)
    {
        if(start >= last)
        {
            ans++;
            last = finish;
        }
    }

    cout << ans << '\n';
}
