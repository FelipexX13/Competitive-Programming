// <3
// Tema: Number Theory / Modulo de Entero Gigante
// O: (largo de la cadena)
// Uso: modString(P,N) con P el numero como string y N el modulo
// Cuando el numero de entrada tiene miles de digitos no cabe en long long, asi que se lee
// como string y se calcula el resto digito por digito con la regla de Horner: se arrastra
// el resto parcial y en cada paso se hace rem = (rem*10 + digito) % N. Como rem siempre es
// menor que N, el producto rem*10 nunca desborda mientras N quepa comodo en long long.
// Sirve para problemas de divisibilidad con numeros gigantes, o como paso previo antes de
// aplicar exponenciacion modular sobre un exponente enorme.

#include <bits/stdc++.h>

using namespace std;

long long modString(const string& P, long long N)
{
    long long rem = 0;
    for (char c : P)
    {
        int d = c - '0';
        rem = (rem * 10 + d) % N;
    }
    return rem;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string P;
    long long N;
    while (cin >> P >> N)
    {
        cout << modString(P, N) << "\n";
    }

    return 0;
}
