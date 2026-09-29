// <3
// Tema: Greedy / Puente y Linterna
// Resuelve "The Bridge At Night" (problema B, ICPC 2024), el clasico del puente con una sola
// linterna: cruzan a lo sumo dos a la vez, al paso del mas lento, y alguien tiene que devolver la
// linterna. El codigo calcula el tiempo minimo para pasar a todos.
// Se ordenan los tiempos y, mientras queden mas de 3, se mandan al otro lado LOS DOS MAS LENTOS
// (y, z) con la mejor de dos estrategias, siendo a y b los dos mas rapidos:
//     a + 2b + z   cruzan a y b, vuelve a, cruzan y y z juntos, vuelve b
//     2a + y + z   a acompana a z, vuelve; a acompana a y, vuelve
// La primera gana cuando los lentos son MUY lentos, porque paga z una sola vez para los dos; la
// segunda cuando no, porque solo usa al mas rapido de ida y vuelta. Cada ronda deja el problema
// igual pero con dos personas menos.
// Casos base: con 3 quedan a + b + c (a acompana a c, vuelve, cruza con b); con 2, el mas lento;
// con 1, el unico.
// Con 1, 2, 5 y 10, que es el acertijo famoso, da 17 (comprobado corriendo este codigo): la
// estrategia ingenua de que el rapido acompane a todos da 19.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    while (cin >> n && n != 0) {

        vector<int> t(n);

        for (int &x : t)
            cin >> x;

        sort(t.begin(), t.end());

        int ans = 0;

        while (n > 3) {

            int a = t[0];
            int b = t[1];
            int y = t[n - 2];
            int z = t[n - 1];

            int option1 = a + 2 * b + z;
            int option2 = 2 * a + y + z;

            ans += min(option1, option2);

            n -= 2;
        }

        // Quedan 1, 2 o 3 personas
        if (n == 3) {
            ans += t[0] + t[1] + t[2];
        }
        else if (n == 2) {
            ans += t[1];
        }
        else if (n == 1) {
            ans += t[0];
        }

        cout << ans << '\n';
    }

    return 0;
}
