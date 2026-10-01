// <3
// Tema: Greedy / Interval Scheduling
// Resumen: Maximo de intervalos sin solaparse: ordenar por hora de FIN, no de inicio
// O: (n log n), ordenar por FIN y tomar el que no choque
// Uso: ordenar por v[i].second y avanzar mientras inicio >= ultimo_fin
// Detalle: Maximo numero de intervalos que se pueden elegir sin que se solapen (tareas con hora
// de inicio y fin, salones, reservas). Es el greedy clasico y no debe confundirse con la DP de
// intervalos de "Yuyuan Market", que optimiza otra cosa (cantidad y luego costo). La clave es
// ordenar por hora de FIN, no por inicio ni por duracion: al quedarse siempre con el intervalo
// que termina antes, se deja la mayor cantidad de tiempo libre para los que siguen, y se puede
// probar por intercambio que ninguna otra eleccion mejora el resultado. Ordenar por inicio o
// por duracion da respuestas incorrectas.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
    }

    // ordenar por hora de fin
    sort(v.begin(), v.end(), [](const pair<int,int> &a, const pair<int,int> &b){
        return a.second < b.second;
    });

    int cnt = 0;
    int last = INT_MIN;

    for (auto &it : v)
    {
        if (it.first >= last)
        {
            cnt++;
            last = it.second;
        }
    }

    cout << cnt << "\n";
    return 0;
}
