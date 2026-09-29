// <3
// Tema: CSES / Rotacion Minima (Dos Punteros)
// La rotacion lexicograficamente menor en O(n) con dos candidatos i y j. Se trabaja sobre s + s
// (asi toda rotacion es un substring de largo n) y se comparan las rotaciones que empiezan en i y
// en j caracter por caracter hasta que difieren en la posicion k.
// EL SALTO QUE HACE QUE SEA LINEAL: si s[i+k] > s[j+k], no solo la rotacion en i pierde; tambien
// pierden las que empiezan en i+1, ..., i+k, porque cada una se puede emparejar con la que
// empieza en j+1, ..., j+k y pierde por la misma posicion. Por eso i salta a i+k+1 de una. Como
// i y j solo avanzan y ninguno pasa de n, el total es O(n).
// Si k llega a n, las dos rotaciones son iguales (la cadena es periodica) y cualquiera sirve.
// El if (i == j) j++ evita comparar un candidato consigo mismo.
// Alternativas: el algoritmo de Booth (con funcion de fallo) o el sufijo minimo de Lyndon. Esta
// version de dos punteros es la mas corta de escribir y la mas facil de recordar.

#include <bits/stdc++.h>
using namespace std;

string minimalRotation(string s) {
    int n = s.size();

    s += s;

    int i = 0, j = 1;

    while (i < n && j < n) {
        int k = 0;

        while (k < n && s[i + k] == s[j + k])
            k++;

        if (k == n)
            break;

        if (s[i + k] > s[j + k])
            i = i + k + 1;
        else
            j = j + k + 1;

        if (i == j)
            j++;
    }

    int pos = min(i, j);

    return s.substr(pos, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    cout << minimalRotation(s) << '\n';
}
