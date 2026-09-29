// <3
// Tema: Math / Numeros Romanos
// Convierte un entero a numeral romano con un greedy sobre una tabla de valores ordenada de
// mayor a menor. El truco esta en incluir en la tabla los seis casos sustractivos (CM, CD,
// XC, XL, IX, IV) como si fueran simbolos propios: asi el greedy de "restar el mayor valor
// que quepa" nunca se equivoca y no hace falta ningun caso especial. Funciona para 1..3999.

#include <bits/stdc++.h>

using namespace std;

string toRoman(int num)
{
    vector<pair<int, string>> roman = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100,  "C"}, {90,  "XC"}, {50,  "L"}, {40,  "XL"},
        {10,   "X"}, {9,   "IX"}, {5,   "V"}, {4,   "IV"},
        {1,    "I"}
    };
    string res;
    for (const auto &p : roman)
    {
        while (num >= p.first)
        {
            res += p.second;
            num -= p.first;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n)
    {
        cout << toRoman(n) << "\n";
    }

    return 0;
}
