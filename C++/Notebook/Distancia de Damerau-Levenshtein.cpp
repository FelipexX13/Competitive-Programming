// <3
// Tema: Dynamic Programming / Distancia de Damerau-Levenshtein
// Resumen: Minimo numero de operaciones para convertir a en b, con CUATRO operaciones de costo
// 1
// O: (n*m) tiempo y memoria
// Uso: lee dos cadenas por stdin; la DP esta en main, extraer el doble for
// Detalle: Minimo numero de operaciones para convertir a en b, con CUATRO operaciones de costo
// 1: insertar, borrar, sustituir e intercambiar dos caracteres ADYACENTES. Es la distancia de
// edicion de toda la vida mas la transposicion, que es justo lo que modela los errores de
// tipeo. OJO, que aqui esta la trampa: casi todo el mundo escribe la version "facil" (OSA,
// Optimal String Alignment), que es la tabla de Levenshtein con un if extra para el swap. Esa
// version prohibe editar lo que quedo entre los dos caracteres intercambiados, y da respuestas
// mas grandes. El ejemplo que las separa es "ca" -> "abc": esta rutina responde 2 (intercambiar
// c y a, insertar la b), mientras que OSA responde 3. Si el problema pide la distancia REAL (la
// que cumple desigualdad triangular), toca esta version. Verificado contra busqueda exhaustiva.
// Los dos arreglos auxiliares son lo que permite la version irrestricta: da[c] = ultima FILA i
// donde aparecio la letra c en a (se actualiza al cerrar la fila i, asi que durante la fila i
// solo ve filas anteriores) db = ultima COLUMNA j de esta fila donde a[i] == b[j] (se lee antes
// de actualizarlo) Con k = da[b[j]] y l = db, el par (a[k], b[l]) es el candidato a
// intercambiar. Su costo es H[k][l] + (i-k-1) + 1 + (j-l-1): lo de antes, borrar los (i-k-1)
// sobrantes de a, pagar 1 por el intercambio, e insertar los (j-l-1) que faltan de b. Esa es la
// libertad que OSA no tiene. El desplazamiento en 1 no es capricho: el termino de intercambio
// necesita una fila y una columna "menos uno" donde caer cuando la letra nunca aparecio (k = 0)
// o no hubo match en la fila (l = 0). Esas casillas valen INF = n+m, mas que cualquier
// distancia posible, asi que el min las descarta solas y no hay que escribir ningun if. Costo
// O(n*m) tiempo y O(n*m) memoria. Si solo hace falta el numero y no reconstruir la edicion, se
// puede bajar a O(m) guardando tres filas, pero hay que arrastrar tambien la fila del
// intercambio, asi que rara vez vale la pena. LIMITES de esta implementacion: da[26] con
// b[j]-'a' asume MINUSCULAS a-z; con mayusculas o digitos se sale del arreglo. Y H es 1005x1005
// usando indices hasta n+1, o sea n, m <= 1003. Entrada: pares de palabras, una por linea,
// hasta la linea "* *".

#include <bits/stdc++.h>
using namespace std;

static int H[1005][1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    while (cin >> a >> b) {
        if (a == "*" && b == "*") break;

        int n = a.size(), m = b.size();
        int INF = n + m;

        // H desplazada en 1: H[i+1][j+1] = distancia entre a[0..i) y b[0..j)
        H[0][0] = INF;
        for (int i = 0; i <= n; i++) { H[i + 1][0] = INF; H[i + 1][1] = i; }
        for (int j = 0; j <= m; j++) { H[0][j + 1] = INF; H[1][j + 1] = j; }

        int da[26] = {0}; // ultima fila donde aparecio cada letra en a

        for (int i = 1; i <= n; i++) {
            int db = 0; // ultima columna en esta fila donde a[i]==b[j]
            for (int j = 1; j <= m; j++) {
                int k = da[b[j - 1] - 'a'];
                int l = db;
                int cost = 1;
                if (a[i - 1] == b[j - 1]) { cost = 0; db = j; }

                H[i + 1][j + 1] = min({
                    H[i][j] + cost,                         // sustituir/igual
                    H[i + 1][j] + 1,                        // insertar
                    H[i][j + 1] + 1,                        // borrar
                    H[k][l] + (i - k - 1) + 1 + (j - l - 1) // intercambiar
                });
            }
            da[a[i - 1] - 'a'] = i;
        }

        cout << H[n + 1][m + 1] << '\n';
    }
    return 0;
}
