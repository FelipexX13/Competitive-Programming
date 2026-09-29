// <3
// Tema: Number Theory / Factorizacion en Digitos
// Halla el menor numero cuyos digitos multiplicados dan N. La idea greedy: dividir siempre
// por el mayor factor posible entre 9 y 2, porque usar factores grandes minimiza la cantidad
// de digitos, y al final ordenar los digitos de menor a mayor da el numero mas chico posible
// con esa multiset de digitos. Si al terminar el producto de los digitos no coincide con N,
// es que N tiene un factor primo mayor que 9 (11, 13, ...) y la respuesta es -1.
// Casos borde: N < 2 se responde con el propio N.

#include <bits/stdc++.h>

using namespace std;

string recursive(long long num, string sol = "")
{
    for (int i = 9; i > 1; --i)
    {
        if (num % i == 0)
        {
            return recursive(num / i, sol + to_string(i));
        }
    }
    return sol;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;

        if (n < 2)
        {
            cout << n << "\n";
            continue;
        }

        string factors = recursive(n);

        long long mult = 1;
        for (char ch : factors)
        {
            mult *= (ch - '0');
        }

        if (mult == n)
        {
            sort(factors.begin(), factors.end());
            cout << factors << "\n";
        }
        else
        {
            cout << -1 << "\n";
        }
    }

    return 0;
}
