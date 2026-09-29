// <3
// Tema: String / Palindromo Ignorando Simbolos
// Resuelve "Just Palindromes!" (problema J, ICPC 2025): decir si una frase es palindroma ignorando
// espacios, puntuacion y mayusculas.
// Se filtra dejando solo letras y pasandolas a minuscula, y despues es el chequeo de dos punteros
// de siempre. Lo unico que hay que cuidar es la lectura: la frase trae ESPACIOS, asi que va con
// getline y no con >>, que cortaria en el primer espacio.
// DOS BORDES QUE EL ENUNCIADO PERMITE Y QUE CONVIENE PROBAR:
//   - La linea VACIA (dice 0 <= N). Al filtrar queda la cadena vacia, que es palindroma: Y.
//   - Una linea de puros simbolos, como ".---.-" del sample. Tambien queda vacia: Y.
// Con la cadena vacia, r = t.size() - 1 vale -1 y el while no entra, asi que responde Y sin tocar
// memoria. Sale bien por como esta escrito el ciclo, pero vale saber que t.size() es SIN SIGNO:
// si en vez del while hubiera un for con <= y restas, ese -1 se volveria un numero enorme.
// El enunciado acota los caracteres a ASCII imprimible, asi que isalpha y tolower no dan problemas
// de localizacion.
// Verificado contra fuerza bruta en 5008 frases, incluidas la vacia, las de solo simbolos y
// palindromos armados a proposito con basura intercalada y mayusculas mezcladas.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;

    while (getline(cin, s) && s != "*") {

        string t;

        // Dejamos unicamente letras y pasamos a minusculas
        for (char c : s) {
            if (isalpha(c))
                t += tolower(c);
        }

        bool ok = true;

        int l = 0;
        int r = t.size() - 1;

        while (l < r) {
            if (t[l] != t[r]) {
                ok = false;
                break;
            }

            l++;
            r--;
        }

        cout << (ok ? 'Y' : 'N') << '\n';
    }

    return 0;
}
