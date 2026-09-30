// <3
// Tema: Math / Number Theory (Criba y Factorizacion)
// Resuelve "Counting Divisors": dados n enteros, imprime la cantidad de divisores de
// cada uno. Precomputa con una criba de Eratosthenes (sieve) la lista de primos hasta
// MX=1e6; para cada consulta k, la funcion divisors factoriza k probando solo los
// primos precomputados (hasta sqrt(n)) y acumula el conteo de divisores con la formula
// producto de (exponente_i + 1) para cada primo, multiplicando por 2 al final si queda
// un factor primo residual mayor a 1 (el propio n si es primo grande).

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MX = 1000000;

bool marked[MX + 1];
vector<int> primes;

void sieve() {
    marked[0] = marked[1] = true;

    for (int i = 2; i <= MX; i++) {
        if (marked[i]) continue;

        primes.push_back(i);

        if (1LL * i * i > MX) continue;
        for (ll j = 1LL * i * i; j <= MX; j += i)
            marked[j] = true;
    }
}

ll divisors(ll n) {
    ll ans = 1;

    for (ll p : primes) {
        if (p * p > n) break;

        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                cnt++;
            }
            ans *= (cnt + 1);
        }
    }

    if (n > 1) ans *= 2;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int t;
    cin >> t;

    while (t--) {
        ll k;
        cin >> k;
        cout << divisors(k) << '\n';
    }

    return 0;
}