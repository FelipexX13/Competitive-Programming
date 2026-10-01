// <3
// Tema: Implementation / Fuerza Bruta O(n^2) sobre Subperiodos
// Resumen: Contar subperiodos con tantos depositos como retiros, por fuerza bruta O(n^2)
// O: (n^2); medido, 5 casos de 10000 en 94 ms
// Detalle: La otra forma de resolver "Account Qualifying" (problema A, ICPC 2025): probar TODOS
// los subperiodos. Se mapea deposito a +1, retiro a -1 y saldo a 0, y cada tramo con suma 0
// tiene tantos depositos como retiros. Es O(n^2), que con n = 10000 son 10^8 sumas. Medido: 5
// casos del tamano maximo en 94 ms, o sea que pasa, pero la version con sumas de prefijo (el
// otro archivo A de esta carpeta) hace lo mismo en O(n) y tarda 20 ms. POR QUE NO TIENE PODAS:
// la primera version de este archivo intentaba cortar el ciclo interno contando cuantos
// positivos y negativos quedaban disponibles, y estaba mal: el break se evaluaba ANTES de
// comprobar si la suma era 0, asi que descartaba tramos validos. Con el primer caso del sample
// daba r = 3 en vez de 4. Una fuerza bruta sin podas es corta y no se equivoca; si hace falta
// velocidad, lo que corresponde es cambiar de algoritmo, no parchear el ciclo. Lo de d y w es
// igual que en la otra version: si no hay depositos d es 0 y si no hay retiros w es 0, de ahi
// el max(0, ...) y el min(0, ...). Verificado contra fuerza bruta en 2900 casos, sin fallos.

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

        // +1 = deposito
        //  0 = balance
        // -1 = retiro
        for (int &x : a) {
            if (x > 0) x = 1;
            else if (x < 0) x = -1;
        }

        int r = 0;

        // Todos los subperiodos, sin podas: si la suma de signos es 0, hay
        // tantos depositos como retiros.
        for (int i = 0; i < n; i++) {

            int sum = 0;

            for (int j = i; j < n; j++) {

                sum += a[j];

                if (sum == 0)
                    r = max(r, j - i + 1);
            }
        }

        cout << d << ' ' << w << ' ' << r << '\n';
    }

    return 0;
}
