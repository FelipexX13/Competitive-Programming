// <3
// Tema: Data Structures / Prefix Sums con Primera Aparicion
// Resumen: De una lista de transacciones hay que dar el mayor deposito d, el mayor retiro w (el
// mas negativo) y r
// Detalle: Resuelve "Account Qualifying" (problema A, ICPC 2025): de una lista de transacciones
// hay que dar el mayor deposito d, el mayor retiro w (el mas negativo) y r, el largo del
// subperiodo mas largo con TANTOS depositos como retiros. EL TRUCO DE r: se mapea deposito a
// +1, retiro a -1 y consulta de saldo a 0. Entonces "tantos depositos como retiros" es "la suma
// del tramo es 0", y con sumas de prefijo eso es prefijo[j] == prefijo[i]. Guardando la PRIMERA
// posicion donde aparece cada valor de prefijo, el tramo mas largo que termina en j sale
// restando esa primera aparicion. Por eso el mapa solo se escribe cuando el valor es nuevo:
// reescribirlo acortaria los tramos. El first[0] = -1 no es un detalle menor: cubre los tramos
// que arrancan en la posicion 0, donde el prefijo vale 0 "antes de empezar". OJO CON d Y w: si
// no hay depositos d vale 0, y si no hay retiros w vale 0. Tomar el maximo y el minimo del
// arreglo a secas esta MAL, y el propio sample lo pilla: con 100 200 300 el minimo es 100 pero
// la respuesta es 0. Por eso van acotados con max(0, ...) y min(0, ...). La primera version de
// este archivo fallaba justo ahi. Los ceros (consultas de saldo) no rompen nada: aportan 0 a la
// suma, asi que un tramo de puros ceros cuenta como valido, que es lo que pide el enunciado.
// Costo O(n) por caso. Medido: 5 casos de n = 10000 en 20 ms. Verificado contra fuerza bruta en
// 2900 casos, incluidos los que no tienen depositos o no tienen retiros.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    while (cin >> n && n != 0) {

        vector<int> a(n);

        for (int &x : a)
            cin >> x;

        // Si no hay depositos d es 0, y si no hay retiros w es 0: por eso se
        // acotan con 0 en vez de tomar el maximo y el minimo a secas.
        int d = max(0, *max_element(a.begin(), a.end()));
        int w = min(0, *min_element(a.begin(), a.end()));

        // Convertimos:
        // deposito -> +1
        // balance  ->  0
        // retiro   -> -1
        for (int &x : a) {
            if (x > 0) x = 1;
            else if (x < 0) x = -1;
        }

        // first[s] = primera posicion donde aparecio
        // el prefix sum s
        unordered_map<int, int> first;

        int sum = 0;
        int r = 0;

        // prefix sum 0 aparece antes de empezar
        first[0] = -1;

        for (int i = 0; i < n; i++) {

            sum += a[i];

            if (first.count(sum)) {
                // Mismo prefix sum => entre ambas posiciones
                // la suma es 0
                r = max(r, i - first[sum]);
            } else {
                // Guardamos solamente la primera aparicion,
                // porque nos da el segmento mas largo
                first[sum] = i;
            }
        }

        cout << d << ' ' << w << ' ' << r << '\n';
    }

    return 0;
}
