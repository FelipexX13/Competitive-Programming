// <3
// Tema: Math / Game Theory
// Determina el ganador de un juego analizando si N+2 es potencia de 2.
// Si lo es, el segundo jugador gana ("mastermei"), si no, el primero ("the greatest").

#include <bits/stdc++.h>
using namespace std;

bool isPowerOfTwo(long long x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long N;
        cin >> N;

        if (isPowerOfTwo(N + 2)) {
            cout << "the greatest\n";
        } else {
            cout << "mastermei\n";
        }
    }

    return 0;
}