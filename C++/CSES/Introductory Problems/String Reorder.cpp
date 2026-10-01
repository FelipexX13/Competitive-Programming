// <3
// Tema: CSES / Greedy Lexicografico con Cota de Factibilidad
// Resumen: Se arma la respuesta caracter por caracter tomando siempre la letra mas chica
// posible
// Detalle: Se arma la respuesta caracter por caracter tomando siempre la letra mas chica
// posible, pero antes de fijarla se verifica que lo que queda TODAVIA se pueda terminar. La
// cota es la clave: con r caracteres por poner, ninguna letra puede quedar con mas de (r+1)/2
// copias, porque si no dos de ellas quedarian pegadas por fuerza. POR QUE ESTO ES EL PATRON
// GENERAL: un greedy lexicografico solo funciona si se puede decidir en O(1) o O(alfabeto) si
// la eleccion deja el problema resoluble. Sin ese chequeo, tomar siempre la letra mas chica
// lleva a callejones sin salida. La estructura "elegir el menor + verificar factibilidad del
// resto" aparece en un monton de problemas de construccion lexicografica. CUANDO USAR: "la
// cadena lexicograficamente menor que cumple X". Casi nunca hace falta backtracking si se
// encuentra la cota de factibilidad.

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int freq[26] = {};

    for (char c : s)
        freq[c - 'A']++;

    string ans;
    char last = '#';

    for (int pos = 0; pos < s.size(); pos++) {
        bool found = false;

        for (int c = 0; c < 26; c++) {
            if (freq[c] == 0 || 'A' + c == last)
                continue;

            freq[c]--;

            int remaining = s.size() - pos - 1;
            int mx = 0;

            for (int i = 0; i < 26; i++)
                mx = max(mx, freq[i]);

            if (mx <= (remaining + 1) / 2) {
                ans += char('A' + c);
                last = 'A' + c;
                found = true;
                break;
            }

            freq[c]++;
        }

        if (!found) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << ans << '\n';
}
