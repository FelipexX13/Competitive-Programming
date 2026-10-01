// <3
// Tema: CSES / Greedy Local con 4 Colores
// Resumen: Greedy celda por celda: se prueba A, B, C
// O: (n*m), greedy local con 4 colores
// Detalle: Greedy celda por celda: se prueba A, B, C, D y se toma el primero que no choque con
// el color ORIGINAL de la celda, con la celda de arriba y con la de la izquierda. POR QUE NUNCA
// SE ATASCA: son 3 restricciones y 4 colores, asi que por conteo siempre queda al menos uno
// libre. Ese argumento es el que hace que no haga falta backtracking. Y por que basta mirar
// arriba e izquierda: las celdas de abajo y de la derecha todavia no se han decidido, y cuando
// les toque van a mirar hacia aca. Cada pareja de vecinos se revisa una sola vez, desde el que
// va despues. CUANDO USAR: coloreos y asignaciones donde el numero de colores supera al de
// restricciones locales. Si los colores fueran 3 con 3 restricciones, esto ya no cerraria y
// habria que probar con busqueda.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);

    for (auto &row : grid)
        cin >> row;

    string colors = "ABCD";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            for (char c : colors) {
                if (c == grid[i][j])
                    continue;

                if (i > 0 && c == grid[i - 1][j])
                    continue;

                if (j > 0 && c == grid[i][j - 1])
                    continue;

                grid[i][j] = c;
                break;
            }
        }
    }

    for (auto row : grid)
        cout << row << '\n';
}
