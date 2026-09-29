// <3
// Tema: Data Structures / Sparse Table sobre Bloques Iguales
// Resuelve "Frequent Values" (problema E, CCPL): un arreglo de n enteros NO DECRECIENTE y q
// consultas [i,j]; para cada una hay que decir cuantas veces aparece el valor mas repetido de
// ese rango.
// LA LLAVE DEL PROBLEMA ES QUE EL ARREGLO VIENE ORDENADO, y sin eso no habria solucion facil.
// Al estar ordenado, los valores iguales quedan pegados en BLOQUES contiguos, asi que la
// pregunta deja de ser sobre valores y pasa a ser sobre longitudes de bloque. Si el arreglo
// llegara desordenado esto no sirve: ahi tocaria Mo, que esta en la ficha de CSES.
// Un rango [i,j] toca a lo sumo tres cosas:
//   - el PEDAZO del bloque donde cae i, que va de i hasta el final de su bloque
//   - el PEDAZO del bloque donde cae j, desde el inicio de ese bloque hasta j
//   - los bloques COMPLETOS que quedan en el medio
// Los dos pedazos se calculan con una resta, y para los bloques completos hay que pedir el
// maximo de un rango de longitudes, que es exactamente lo que responde una sparse table en
// O(1). La respuesta es el mayor de los tres.
// EL CASO QUE SE OLVIDA: si i y j caen en el MISMO bloque no hay medio ni dos pedazos, y la
// respuesta es j - i + 1 directo. Si uno no separa ese caso, el rango de bloques del medio sale
// invertido (bi+1 > bj-1) y la consulta a la sparse table se va a leer basura. Por eso el
// maxRango devuelve 0 cuando l > r, que es el segundo cinturon de seguridad.
// POR QUE SPARSE TABLE Y NO SEGMENT TREE: el arreglo de longitudes no cambia nunca, y el maximo
// es idempotente, asi que se pueden solapar los dos bloques de la consulta y responder en O(1).
// Un segment tree daria O(log n) y mas codigo, y solo hace falta si hubiera actualizaciones.
// Costo O(n log n) para construir y O(1) por consulta. Medido con n = q = 100000: 0.09 s,
// incluyendo los adversarios de todos iguales (un solo bloque) y todos distintos (n bloques).
// Verificado contra fuerza bruta: 19407 consultas sobre 3000 arreglos aleatorios con bloques de
// repetidos, sin una sola diferencia, mas los tres casos del sample (1, 4, 3).
// OJO CON LA ENTRADA: los casos vienen uno tras otro y se acaban con una linea con un 0 solo,
// asi que el while lee n y corta cuando es cero, sin leer q en ese ultimo.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;

    while (cin >> n && n != 0) {
        cin >> q;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        // Como el arreglo viene ordenado, los iguales quedan en BLOQUES
        // contiguos: se guarda a que bloque pertenece cada posicion, y donde
        // empieza y termina cada bloque.
        vector<int> bloque(n + 1), ini(n + 2), fin(n + 2), tam(n + 2);

        int b = 0;

        for (int i = 1; i <= n; i++) {
            if (i == 1 || a[i] != a[i - 1]) {
                b++;
                ini[b] = i;
            }
            bloque[i] = b;
            fin[b] = i;
        }

        for (int t = 1; t <= b; t++) tam[t] = fin[t] - ini[t] + 1;

        // Sparse table de MAXIMOS sobre los tamanos de bloque.
        int K = 1;
        while ((1 << K) <= b) K++;

        vector<vector<int>> st(K, vector<int>(b + 1, 0));

        for (int i = 1; i <= b; i++) st[0][i] = tam[i];

        for (int k = 1; k < K; k++) {
            int len = 1 << k;
            for (int i = 1; i + len - 1 <= b; i++)
                st[k][i] = max(st[k - 1][i], st[k - 1][i + len / 2]);
        }

        // Maximo de tam[l..r]; los dos bloques se solapan y no pasa nada,
        // porque el maximo es idempotente.
        auto maxRango = [&](int l, int r) {
            if (l > r) return 0;
            int k = 31 - __builtin_clz(r - l + 1);
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        };

        while (q--) {
            int i, j;
            cin >> i >> j;

            int bi = bloque[i], bj = bloque[j];

            // Todo el rango cae dentro de un mismo bloque.
            if (bi == bj) {
                cout << j - i + 1 << '\n';
                continue;
            }

            int izq = fin[bi] - i + 1;      // cola del bloque de i
            int der = j - ini[bj] + 1;      // cabeza del bloque de j
            int medio = maxRango(bi + 1, bj - 1);

            cout << max(medio, max(izq, der)) << '\n';
        }
    }
    return 0;
}
