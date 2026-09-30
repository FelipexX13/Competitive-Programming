// <3
// Tema: Binary Search / Two Pointers
// Resuelve "Black Hills golden jewels" (Contest 05 [Avanzados], problema B): dado el precio a_i
// de cada una de N categorias de joyas, un cliente debe elegir dos categorias distintas, y
// ningun cliente puede repetir una combinacion ya elegida por otro; hay que hallar el monto
// minimo que garantiza que el K-esimo cliente en la fila pueda comprar, es decir, la K-esima
// suma de pares (a_i + a_j) mas pequena entre todos los pares posibles.
// Hace busqueda binaria sobre la respuesta (variable mid entre lo y hi) y para cada candidato
// cuenta, con dos punteros (i creciente, j decreciente) sobre el arreglo ordenado, cuantos
// pares tienen suma <= mid, ajustando el rango hasta converger al K-esimo valor.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K;
    cin >> N >> K;

    vector<ll> a(N);

    for (int i = 0; i < N; i++)
        cin >> a[i];

    sort(a.begin(), a.end());

    // La respuesta está entre la suma mínima y máxima posibles.
    ll lo = a[0] + a[1];
    ll hi = a[N - 1] + a[N - 2];

    while (lo < hi) {

        ll mid = (lo + hi) / 2;

        /*
            Contaremos cuántos pares tienen suma <= mid.

            Usamos dos punteros.

            Para cada i, buscamos el mayor j tal que

                a[i] + a[j] <= mid

            Entonces todos los índices entre
            (i+1 ... j) también sirven.
        */
        ll cnt = 0;

        int j = N - 1;

        for (int i = 0; i < N; i++) {

            while (j > i && a[i] + a[j] > mid)
                j--;

            if (j <= i)
                break;

            cnt += (j - i);
        }

        if (cnt >= K)
            hi = mid;
        else
            lo = mid + 1;
    }

    cout << lo << '\n';

    return 0;
}