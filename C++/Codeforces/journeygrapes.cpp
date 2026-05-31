// <3
// Tema: Math / GCD and LCM
// Calcula a dividido entre mcd(a,b), que es el multiplicador para obtener mcm(a,b) desde b.

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    //c++17
    cout << a / gcd(a, b) << endl;

    return 0;
}