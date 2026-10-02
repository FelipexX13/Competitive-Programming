// <3
// Tema: CSES / Recalcular Solo lo que Cambia
// Resumen: Collecting Numbers con m intercambios, respondiendo tras cada uno
// O: ((n + m) log n), cada swap toca a lo sumo seis vecindades
// Uso: tras el swap solo se revisan los pares (v-1,v) y (v,v+1) de los dos valores
// Detalle: Rehacer la cuenta entera despues de cada swap seria O(n*m) y no pasa. La observacion
// que lo salva: al intercambiar dos posiciones, los UNICOS descensos que pueden cambiar son los
// que involucran a los valores de esas dos casillas y a sus vecinos inmediatos en VALOR (v-1 y
// v+1). Todo lo demas sigue igual. Entonces se restan esos pocos pares de la respuesta, se hace
// el swap, y se vuelven a sumar. El set de cuales revisar es para no contar dos veces cuando
// los dos valores son vecinos. El patron (mantener una respuesta global y tocar solo el
// vecindario afectado) sirve para muchisimos problemas de actualizaciones puntuales.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    vector<int> pos(n + 1);

    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }

    int rounds = 1;

    for(int i = 1; i < n; i++)
    {
        if(pos[i] > pos[i + 1])
            rounds++;
    }

    while(m--)
    {
        int x, y;
        cin >> x >> y;

        int vx = a[x];
        int vy = a[y];

        set<int> check;

        check.insert(vx - 1);
        check.insert(vx);
        check.insert(vy - 1);
        check.insert(vy);

        for(int i : check)
        {
            if(i >= 1 && i < n)
            {
                if(pos[i] > pos[i + 1])
                    rounds--;
            }
        }

        swap(a[x], a[y]);

        pos[vx] = y;
        pos[vy] = x;

        for(int i : check)
        {
            if(i >= 1 && i < n)
            {
                if(pos[i] > pos[i + 1])
                    rounds++;
            }
        }

        cout << rounds << '\n';
    }

    return 0;
}
