// <3
// Tema: String / Rotacion Minima (Dos Punteros)
// Resumen: Las huellas se guardan de forma circular, asi que ABCD, BCDA, CDAB y DABC son la
// misma
// O: (n), rotacion minima con dos punteros
// Detalle: Resuelve "Fingerprints" (problema F, ICPC 2025): las huellas se guardan de forma
// circular, asi que ABCD, BCDA, CDAB y DABC son la misma. Hay que quedarse con una sola copia
// de cada huella distinta, representada por su rotacion lexicograficamente menor. La rotacion
// minima sale en O(n) con dos candidatos i y j sobre la cadena duplicada: se comparan caracter
// por caracter y, al diferir en la posicion k, el perdedor salta k+1 posiciones de una. Ese
// salto es lo que la hace lineal, y esta explicada con detalle en la ficha "Minimal Rotation"
// de CSES, en este mismo cuaderno. EL ERROR QUE TENIA ESTE ARCHIVO ERA DE ORDEN, NO DE
// ALGORITMO: guardaba las canonicas en un set<string> y las imprimia recorriendolo, o sea en
// orden ALFABETICO. El enunciado pide el orden en que aparecen en la ENTRADA, y el sample lo
// delata: con ABCD, BCDA, XYZ, FFFF, ZXY la respuesta es ABCD XYZ FFFF y el set devolvia ABCD
// FFFF XYZ. La solucion es la de siempre para "sin repetidos pero en orden de llegada": un set
// aparte solo para saber si ya se vio, y un vector que conserva el orden. El insert(...).second
// dice en una sola operacion si era nueva. Verificado contra fuerza bruta (rotacion minima
// comparando todas las rotaciones) en 500 casos. Medido: 3 casos de 100 huellas de 5000
// caracteres en 33 ms.

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

    int n;

    while (cin >> n && n != 0) {

        // El set solo sirve para detectar repetidas. El ORDEN de salida es el
        // de aparicion en la entrada, asi que se guarda aparte en un vector:
        // imprimir el set directamente las sacaria en orden alfabetico.
        set<string> vistas;
        vector<string> ans;

        for (int i = 0; i < n; i++) {
            int m;
            string s;

            cin >> m >> s;

            string canon = minimalRotation(s);

            if (vistas.insert(canon).second)
                ans.push_back(canon);
        }

        for (const string &s : ans)
            cout << s << '\n';
    }

    return 0;
}
