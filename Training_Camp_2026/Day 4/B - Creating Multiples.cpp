// <3
// Tema: Math / Modular Arithmetic
// Resuelve "Creating Multiples" (Training Camp 2026, Day 4 problema B): dado un numero N de L
// digitos en base B, hay que reducir (nunca aumentar) como mucho un digito para que el numero
// resultante M sea multiplo de B+1, eligiendo la solucion que minimice M.
// Usa que B es congruente con -1 modulo B+1, por lo que el resto de N modulo B+1 es la suma
// alternada de sus digitos (variable rem); recorre los digitos de izquierda a derecha calculando
// cuanto hay que restarle a cada uno (delta) para anular ese resto, y toma la primera posicion
// valida, que por ser la mas significativa da el M mas chico posible.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int B, L;
    cin >> B >> L;

    vector<int> D(L);
    for (int &x : D) cin >> x;

    int mod = B + 1;

    // Calculate N modulo (B + 1).
    // B ≡ -1 (mod B+1), so powers alternate.
    int rem = 0;
    for (int i = 0; i < L; i++) {
        if ((L - 1 - i) % 2 == 0)
            rem += D[i];
        else
            rem -= D[i];
        rem %= mod;
    }
    if (rem < 0) rem += mod;

    if (rem == 0) {
        cout << "0 0\n";
        return 0;
    }

    // Try positions from left to right. The first possible position
    // gives the smallest resulting number.
    for (int i = 0; i < L; i++) {
        int sign = ((L - 1 - i) % 2 == 0) ? 1 : -1;

        // Need a decrease delta such that:
        // rem - delta * sign ≡ 0 (mod B+1)
        int delta;
        if (sign == 1)
            delta = rem;
        else
            delta = (mod - rem) % mod;

        // Digits are smaller than B+1, so this is the only possible delta.
        if (delta <= D[i] && delta > 0) {
            cout << i + 1 << ' ' << D[i] - delta << '\n';
            return 0;
        }
    }

    cout << "-1 -1\n";
    return 0;
}