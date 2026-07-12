#include <bits/stdc++.h>
using namespace std;

/*
    Calcula el mínimo número de swaps necesarios para convertir
    una permutación en la identidad.

    Si una permutación tiene un ciclo de tamaño k,
    se necesitan k-1 intercambios para corregirlo.
*/
int minSwaps(vector<int> &perm) {

    int n = perm.size();

    vector<bool> vis(n, false);

    int ans = 0;

    for (int i = 0; i < n; i++) {

        // Si ya fue visitado o ya está en su lugar
        if (vis[i] || perm[i] == i)
            continue;

        int cur = i;
        int cycleSize = 0;

        // Recorremos el ciclo completo
        while (!vis[cur]) {
            vis[cur] = true;
            cur = perm[cur];
            cycleSize++;
        }

        // Un ciclo de tamaño k necesita k-1 swaps
        ans += cycleSize - 1;
    }

    return ans;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, C;
    cin >> L >> C;

    // Matriz con la configuración actual
    vector<vector<int>> a(L, vector<int>(C));

    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
            cin >> a[i][j];

    /*
        rowPerm[i] = fila ORIGINAL a la que realmente pertenece
        la fila actual i.

        Ejemplo:
            rowPerm = [3,1,2,0]

        significa:
            la fila actual 0 debería ser la fila 3,
            la fila actual 1 debería ser la fila 1,
            etc.
    */
    vector<int> rowPerm(L, -1);

    // Revisamos fila por fila
    for (int i = 0; i < L; i++) {

        /*
            La fila original de un contenedor se obtiene como

                (id-1)/C

            porque cada fila contiene exactamente C elementos.
        */
        int expectedRow = (a[i][0] - 1) / C;

        // Todos los elementos de la fila deben pertenecer
        // a la misma fila original.
        for (int j = 1; j < C; j++) {

            if ((a[i][j] - 1) / C != expectedRow) {
                cout << "*\n";
                return 0;
            }
        }

        rowPerm[i] = expectedRow;
    }

    /*
        Además debe ser una permutación válida.

        No pueden existir dos filas actuales que correspondan
        a la misma fila original.
    */
    vector<bool> used(L, false);

    for (int x : rowPerm) {

        if (used[x]) {
            cout << "*\n";
            return 0;
        }

        used[x] = true;
    }

    /*
        colPerm[j] = columna ORIGINAL a la que corresponde
        la columna actual j.
    */
    vector<int> colPerm(C, -1);

    // Revisamos columna por columna
    for (int j = 0; j < C; j++) {

        /*
            La columna correcta de un contenedor es

                (id-1)%C
        */
        int expectedCol = (a[0][j] - 1) % C;

        // Todos los elementos de la columna deben pertenecer
        // a la misma columna original.
        for (int i = 1; i < L; i++) {

            if ((a[i][j] - 1) % C != expectedCol) {
                cout << "*\n";
                return 0;
            }
        }

        colPerm[j] = expectedCol;
    }

    // Verificamos nuevamente que sea una permutación válida
    used.assign(C, false);

    for (int x : colPerm) {

        if (used[x]) {
            cout << "*\n";
            return 0;
        }

        used[x] = true;
    }

    /*
        Si llegamos aquí, existe una secuencia de intercambios.

        El número mínimo es:

            swaps para ordenar las filas
            +
            swaps para ordenar las columnas
    */
    cout << minSwaps(rowPerm) + minSwaps(colPerm) << "\n";

    return 0;
}