// <3
// Tema: CSES / Exponenciacion Modular Rapida
// Resumen: 2^n mod (10^9+7) con exponenciacion binaria
// O: (log n), exponenciacion rapida
// Detalle: 2^n mod (10^9+7) con exponenciacion binaria: se eleva al cuadrado y se va
// recorriendo el exponente bit por bit, O(log n) multiplicaciones. POR QUE NO pow(2, n): pow es
// de double, pierde precision pasando de 2^53 y no sabe de modulos. Para exponentes grandes con
// modulo SIEMPRE esta plantilla. DETALLE DEL TIPO: res * a puede llegar a (10^9)^2 = 10^18, que
// cabe en long long pero NO en int. Si a y res fueran int el producto se desborda antes del
// modulo. Esta es la razon de que todo en la funcion sea long long. CUANDO USAR: cualquier
// respuesta "modulo 10^9+7" que involucre potencias, y es la base del inverso modular por
// Fermat, a^(p-2) mod p.

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long modpow(long long a, long long b) {
    long long res = 1;

    while (b) {
        if (b & 1)
            res = res * a % MOD;

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int main() {
    long long n;
    cin >> n;

    cout << modpow(2, n) << '\n';
}
