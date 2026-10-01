// <3
// Tema: CSES / Fenwick 2D
// Resumen: Fenwick en dos dimensiones: un for anidado dentro de otro, cada uno con el mismo i &
// -i de siempre
// Detalle: Fenwick en dos dimensiones: un for anidado dentro de otro, cada uno con el mismo i &
// -i de siempre. Actualizar una celda y consultar el rectangulo de (1,1) a (x,y) cuestan
// O(log^2 n), y un rectangulo cualquiera sale por inclusion-exclusion con las cuatro esquinas,
// igual que en las sumas prefijas 2D. COMPARAR CON "Forest Queries": aquella no tenia cambios y
// le bastaban sumas prefijas 2D con consulta O(1). Aqui los arboles se cortan y se plantan, y
// ese cambio es lo que obliga a pasar a Fenwick: las sumas prefijas se tendrian que reconstruir
// enteras, O(n^2) por actualizacion. El toggle se maneja guardando el estado actual en a[][]
// para saber si sumar +1 o -1. Sin ese arreglo no hay forma de saber que hay en una celda sin
// hacer una consulta. CUANDO USAR: sumas sobre rectangulos con actualizaciones puntuales y n de
// hasta unos 1000 (la memoria es n^2). Si hay que actualizar RECTANGULOS enteros, esto no
// alcanza.

#include <bits/stdc++.h>
using namespace std;

int n, q;
int bit[1005][1005];
bool a[1005][1005];

void add(int x, int y, int v) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= n; j += j & -j)
            bit[i][j] += v;
}

int sum(int x, int y) {
    int ans = 0;

    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            ans += bit[i][j];

    return ans;
}

int query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2)
         - sum(x1 - 1, y2)
         - sum(x2, y1 - 1)
         + sum(x1 - 1, y1 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        for (int j = 1; j <= n; j++) {
            if (s[j - 1] == '*') {
                a[i][j] = true;
                add(i, j, 1);
            }
        }
    }

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int y, x;
            cin >> y >> x;

            if (a[y][x]) {
                a[y][x] = false;
                add(y, x, -1);
            } else {
                a[y][x] = true;
                add(y, x, 1);
            }
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;

            cout << query(y1, x1, y2, x2) << '\n';
        }
    }
}

