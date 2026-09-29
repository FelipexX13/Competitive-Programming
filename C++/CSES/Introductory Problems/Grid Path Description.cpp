// <3
// Tema: CSES / Backtracking con Poda de Zona Encerrada
// Backtracking sobre las 48 posiciones del camino, con los '?' abriendo las 4 direcciones y las
// letras fijas forzando una sola. Sin poda esto no pasa ni de lejos.
// LA PODA ES TODO EL PROBLEMA: si la celda actual tiene libres arriba y abajo pero ocupadas
// izquierda y derecha (o al reves), el camino acaba de partir el tablero en dos y una de las
// mitades queda inalcanzable. Se corta ahi mismo. Esa sola condicion baja el arbol de busqueda de
// inviable a instantaneo.
// CUANDO USAR ESTE TIPO DE PODA: en caminos hamiltonianos o recorridos que deben cubrir todo, la
// poda util casi siempre es de CONECTIVIDAD, o sea detectar temprano que quedo una region a la que
// ya no se puede llegar. La version fuerte es correr un flood fill en cada nodo; esta version
// barata mira solo los cuatro vecinos y alcanza.

#include <bits/stdc++.h>
using namespace std;

string s;
bool vis[7][7];
int ans = 0;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void dfs(int x, int y, int pos) {
    if (x == 6 && y == 0) {
        if (pos == 48)
            ans++;
        return;
    }

    if (pos == 48)
        return;

    // Si estamos encerrando una zona, no sirve continuar
    if (x > 0 && x < 6 && !vis[x - 1][y] && !vis[x + 1][y] &&
        (y == 0 || vis[x][y - 1]) && (y == 6 || vis[x][y + 1]))
        return;

    if (y > 0 && y < 6 && !vis[x][y - 1] && !vis[x][y + 1] &&
        (x == 0 || vis[x - 1][y]) && (x == 6 || vis[x + 1][y]))
        return;

    for (int d = 0; d < 4; d++) {
        if (s[pos] != '?' && s[pos] != "DURL"[d])
            continue;

        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx < 0 || nx >= 7 || ny < 0 || ny >= 7)
            continue;

        if (vis[nx][ny])
            continue;

        vis[nx][ny] = true;
        dfs(nx, ny, pos + 1);
        vis[nx][ny] = false;
    }
}

int main() {
    cin >> s;

    vis[0][0] = true;

    dfs(0, 0, 0);

    cout << ans << '\n';
}
