// <3
// Tema: CSES / Formula por Capas
// Resumen: La espiral se lee por CAPAS: la capa k son las celdas con max(fila, columna) = k
// O: (1) por consulta, formula por capas
// Detalle: La espiral se lee por CAPAS: la capa k son las celdas con max(fila, columna) = k, y
// toda la capa va entre (k-1)^2+1 y k^2. Segun la paridad de k la capa se recorre en un sentido
// o en el otro, y de ahi salen las cuatro formulas de los ifs. CUANDO USAR: el problema pide el
// valor en una coordenada de un patron infinito, con t consultas y coordenadas hasta 10^9.
// Construir la tabla es imposible, asi que hay que encontrar la formula. COMO SE ENCUENTRA:
// dibujar los primeros 4x4 o 5x5 a mano y buscar que se repite. Aqui lo que se ve es que los
// cuadrados perfectos caen en la diagonal y que la direccion alterna con la paridad. Sin
// dibujarlo no sale. long long: y^2 con y = 10^9 es 10^18.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long y, x;
        cin >> y >> x;

        if (y > x) {
            if (y % 2 == 0)
                cout << y * y - x + 1 << '\n';
            else
                cout << (y - 1) * (y - 1) + x << '\n';
        } else {
            if (x % 2 == 0)
                cout << (x - 1) * (x - 1) + y << '\n';
            else
                cout << x * x - y + 1 << '\n';
        }
    }
}
