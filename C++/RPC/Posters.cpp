// <3
// Tema: Greedy / Budget Optimization
// Dado un presupuesto c y costos a, b, calcula el maximo de posters que se pueden comprar
// comprando al menos uno de cada tipo.

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    long long a,b,c;

    cin >> a >> b >> c;

    cout << (min((c-a) / b, (c-b) / a) < 0 ? 0 : min((c-a) / b, (c-b) / a)) << endl;



    return 0;
}