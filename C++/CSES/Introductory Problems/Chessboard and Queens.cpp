// <3
// Tema: CSES / Backtracking con Poda por Diagonales
// Resumen: Las 8 reinas con backtracking fila por fila, que es lo que baja el espacio de
// busqueda
// Detalle: Las 8 reinas con backtracking fila por fila, que es lo que baja el espacio de
// busqueda: poniendo una reina por fila, las filas ya no hay que revisarlas. LO QUE VALE COPIAR
// SON LOS INDICES DE DIAGONAL, que es donde todo el mundo se equivoca: diag2[row + col] -> las
// diagonales que bajan hacia la derecha, indice 0..2n-2 diag1[row - col + n-1] -> las que bajan
// hacia la izquierda, con el +n-1 para no dar negativo Marcar, bajar, y DESMARCAR al volver:
// los tres arreglos se restauran siempre. CUANDO USAR: colocar piezas u objetos con
// restricciones de conflicto, en tableros chicos. La clave del backtracking util es que la poda
// se pueda verificar en O(1) por candidato, y para eso son estos arreglos de ocupado.

#include <bits/stdc++.h>
using namespace std;

char board[8][8];
bool col[8], diag1[15], diag2[15];
int ans = 0;

void solve(int row) {
    if (row == 8) {
        ans++;
        return;
    }

    for (int c = 0; c < 8; c++) {
        if (board[row][c] == '*')
            continue;

        if (col[c] || diag1[row - c + 7] || diag2[row + c])
            continue;

        col[c] = true;
        diag1[row - c + 7] = true;
        diag2[row + c] = true;

        solve(row + 1);

        col[c] = false;
        diag1[row - c + 7] = false;
        diag2[row + c] = false;
    }
}

int main() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            cin >> board[i][j];

    solve(0);

    cout << ans << '\n';
}
