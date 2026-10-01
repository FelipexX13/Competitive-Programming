// <3
// Tema: CSES / Fuerza Bruta 2^n
// Resumen: N <= 20, o sea 2^20 = ~10^6 subconjuntos: cabe de sobra, asi que se prueban todos
// O: (2^n), todos los subconjuntos
// Detalle: n <= 20, o sea 2^20 = ~10^6 subconjuntos: cabe de sobra, asi que se prueban todos.
// La recursion decide para cada posicion si el elemento va a un grupo o al otro. EL DETALLE
// BONITO: no hace falta llevar las dos sumas. Con el total fijo, la diferencia entre grupos es
// |total - 2*sum|, asi que basta una sola variable. COMO RECONOCER QUE CABE LA FUERZA BRUTA:
// mirar n en las restricciones. n <= 20 grita 2^n (o bitmask DP); n <= 10 grita n!
// (permutaciones); n <= 40 grita meet in the middle. Ese mapeo de n a tecnica es de lo mas
// rentable que hay en competitiva. La version con mascara de bits (for mask = 0 hasta 1<<n)
// hace lo mismo sin recursion.

#include <bits/stdc++.h>
using namespace std;

long long ans = LLONG_MAX;
long long total = 0;
vector<long long> a;

void solve(int pos, long long sum) {
    if (pos == a.size()) {
        ans = min(ans, abs(total - 2 * sum));
        return;
    }

    solve(pos + 1, sum + a[pos]);
    solve(pos + 1, sum);
}

int main() {
    int n;
    cin >> n;

    a.resize(n);

    for (auto &x : a) {
        cin >> x;
        total += x;
    }

    solve(0, 0);

    cout << ans << '\n';
}
