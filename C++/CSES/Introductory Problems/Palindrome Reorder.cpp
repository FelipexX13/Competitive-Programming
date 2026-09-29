// <3
// Tema: CSES / Conteo de Frecuencias
// Un palindromo se puede armar si y solo si a lo sumo UNA letra tiene frecuencia impar, la que
// quedaria en el centro. Se cuentan frecuencias, se cuentan las impares y si hay mas de una no
// hay solucion.
// Para construirlo: media frecuencia de cada letra en orden va a la primera mitad, la letra impar
// al centro, y la primera mitad invertida al final. Recorrer el alfabeto en orden da la
// lexicograficamente menor gratis.
// CUANDO USAR: cualquier problema de anagramas o reordenar caracteres. La frecuencia es lo unico
// que importa, el orden original de la cadena se puede tirar. El criterio de "a lo sumo una
// impar" es el que hay que tener memorizado.

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    vector<int> freq(26);

    for (char c : s)
        freq[c - 'A']++;

    int odd = 0;
    for (int x : freq)
        odd += x % 2;

    if (odd > 1) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    string half, mid;

    for (int i = 0; i < 26; i++) {
        half += string(freq[i] / 2, 'A' + i);

        if (freq[i] % 2)
            mid += char('A' + i);
    }

    string rev = half;
    reverse(rev.begin(), rev.end());

    cout << half << mid << rev << '\n';
}
