// <3
// Tema: CSES / BFS en Grilla
// BFS de caballo sobre la grilla: la distancia en SALTOS es el numero de aristas, y BFS la da
// porque todos los movimientos cuestan lo mismo. Los 8 movimientos van en los arreglos dx y dy,
// que es como se evitan 8 bloques de codigo repetido.
// Se usa dist inicializada en -1 haciendo doble papel de distancia y de visitado, y se marca al
// ENCOLAR.
// CUANDO USAR: distancia minima en grilla con pasos de costo uniforme. Si los pasos costaran
// distinto seria Dijkstra, y con costos 0 y 1 seria 0-1 BFS con deque.
// OJO: usa auto [x, y] (structured bindings), que necesita C++17. Con un compilador viejo hay que
// volver a q.front().first y .second.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n, -1));

    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

    queue<pair<int, int>> q;

    q.push({0, 0});
    dist[0][0] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                continue;

            if (dist[nx][ny] != -1)
                continue;

            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << dist[i][j] << ' ';
        cout << '\n';
    }
}
