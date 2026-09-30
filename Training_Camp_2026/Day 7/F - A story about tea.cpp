// <3
// Tema: Recursion / Constructive
// Resuelve "A story about tea": N botes deben viajar de Portugal a Inglaterra usando China como
// puerto auxiliar, siguiendo las reglas de las Torres de Hanoi (cada viaje mueve el bote mas
// chico entre las dos pilas involucradas, y nunca hay dos viajes simultaneos), en exactamente K
// viajes; hay que decidir si es posible y, de serlo, imprimir la secuencia de K viajes.
// El minimo de viajes es 2^N - 1 (funcion h, la recursion clasica de Hanoi); si K es mayor,
// completa la diferencia con pares de movimientos "de relleno" A-B-A que no cambian el estado
// (delta/2 veces) y, si sobra un viaje impar, usa la variante g que gasta un movimiento extra
// en el ultimo bote; si K < 2^N - 1 no hay solucion posible ("N").

#include <bits/stdc++.h>
using namespace std;

string out;

inline void addMove(char from, char to) {
    out += from;
    out += ' ';
    out += to;
    out += '\n';
}

// mueve n botes de X a Y usando Z como auxiliar, minimal (2^n - 1 movimientos)
void h(int n, char X, char Y, char Z) {
    if (n == 0) return;
    h(n - 1, X, Z, Y);
    addMove(X, Y);
    h(n - 1, Z, Y, X);
}

// mueve n botes de X a Y usando Z como auxiliar, con exactamente 1 movimiento extra (2^n movimientos)
void g(int n, char X, char Y, char Z) {
    if (n == 1) {
        addMove(X, Z);
        addMove(Z, Y);
        return;
    }
    h(n - 1, X, Z, Y);
    addMove(X, Y);
    g(n - 1, Z, Y, X);
}

int main() {
    long long N, K;
    cin >> N >> K;

    long long minK = (1LL << N) - 1;

    if (K < minK) {
        cout << "N\n";
        return 0;
    }

    long long delta = K - minK;
    bool useG = (delta % 2 == 1);
    long long padCount = useG ? (delta - 1) / 2 : delta / 2;

    out.reserve((size_t)K * 4 + 16);

    for (long long i = 0; i < padCount; i++) {
        addMove('A', 'B');
        addMove('B', 'A');
    }

    if (useG) {
        g((int)N, 'A', 'C', 'B');
    } else {
        h((int)N, 'A', 'C', 'B');
    }

    cout << "Y\n";
    cout << out;
    return 0;
}