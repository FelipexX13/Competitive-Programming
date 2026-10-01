// <3
// Tema: CSES / Manacher
// Resumen: Manacher: el palindromo mas largo en O(n)
// O: (n), Manacher
// Detalle: Manacher: el palindromo mas largo en O(n). Se intercala '#' entre letras para que
// los palindromos pares y los impares se vuelvan todos impares, y para cada centro se guarda
// p[i], el radio del palindromo mas largo ahi. LO QUE LO HACE LINEAL: se mantiene el palindromo
// que llega mas a la derecha (center, right). Si i cae dentro de el, su espejo 2*center - i ya
// se calculo, y p[i] arranca en min(right - i, p[espejo]) en vez de en 0. Solo se expande lo
// que sobresale de right, y right nunca retrocede. Para volver a la cadena original: con
// separadores, el palindromo de radio p[i] centrado en i mide p[i] letras reales y empieza en
// (i - p[i]) / 2. OJO, ESTE ARCHIVO TIENE UN BUCLE DE DEPURACION AL FINAL: despues de imprimir
// la respuesta recorre p e imprime p[i] para cada i impar. Con la entrada "aybabtu" sale "bab"
// y 7 lineas de mas (comprobado). En CSES eso es Wrong Answer; hay que borrar ese for antes de
// enviar.

#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(string s) {
    string t = "#";

    for (char c : s) {
        t += c;
        t += '#';
    }

    int n = t.size();

    vector<int> p(n);

    int center = 0;
    int right = 0;

    for (int i = 0; i < n; i++) {
        int mirror = 2 * center - i;

        if (i < right)
            p[i] = min(right - i, p[mirror]);

        while (i + 1 + p[i] < n &&
               i - 1 - p[i] >= 0 &&
               t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<int> p = manacher(s);

    int pos = max_element(p.begin(), p.end()) - p.begin();
    int len = p[pos];

    int start = (pos - len) / 2;

    cout << s.substr(start, len) << '\n';

    for(int i = 0 ; i < p.size();i++)
    {
        if(i%2!=0)
        {
            cout << p[i] << endl;
        }

    }

    return 0;
}
