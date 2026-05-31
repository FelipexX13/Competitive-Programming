// <3
// Tema: Math / Big Exponentiation
// Calcula p^q usando aritmética de precisión arbitraria (boost::multiprecision)
// para manejar resultados con exponentes muy grandes.

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

int main() {
    while (true) {
        long long p, q;
        cin >> p >> q;

        if (p == 0 && q == 0) return 0;

        cpp_int b = 1;

        for (long long i = 0; i < q; i++) {
            b *= p;
        }

        cout << b << "\n";
    }
}