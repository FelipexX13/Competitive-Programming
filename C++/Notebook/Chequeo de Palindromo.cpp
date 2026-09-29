// <3
// Tema: String / Chequeo de Palindromo
// Las tres formas de preguntar "esto es palindromo", segun cuantas veces lo vayas a preguntar.
// Para una consulta suelta basta el chequeo de dos punteros en O(n) y sin memoria extra. Si el
// problema pregunta por muchos rangos [l,r] distintos, conviene precalcular la tabla pal[i][j]
// en O(n^2) y responder cada consulta en O(1). Y si n es grande y hace falta el palindromo mas
// largo, ahi ya toca Manacher en O(n).
// La regla para elegir: cuenta cuantas consultas vas a hacer. Una sola, dos punteros; muchas
// sobre n <= 2000, la tabla; n de 10^5 o mas, Manacher.

#include <bits/stdc++.h>
using namespace std;

// 1) Consulta suelta: O(n) tiempo, O(1) memoria.
//    Se pasa por referencia para no copiar el string en cada llamada.
bool esPalindromo(string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

// El string completo, con la STL:
//    equal(s.begin(), s.begin() + s.size() / 2, s.rbegin())

// 2) Muchas consultas de rango: tabla O(n^2), cada consulta O(1).
//    pal[i][j] depende del interior [i+1][j-1], asi que i va de DERECHA a
//    IZQUIERDA para que ese interior ya este resuelto.
vector<vector<bool>> tablaPalindromos(const string &s) {
    int n = s.size();
    vector<vector<bool>> pal(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; i--)
        for (int j = i; j < n; j++)
            if (s[i] == s[j] && (j - i < 2 || pal[i + 1][j - 1]))
                pal[i][j] = true;
    return pal;
}

// 3) Palindromo mas largo con n grande: Manacher, O(n).
//    d1[i] = cuantos palindromos IMPARES centrados en i
//    d2[i] = cuantos palindromos PARES centrados entre i-1 e i
//    El impar mas largo centrado en i mide 2*d1[i]-1, el par mide 2*d2[i].
pair<vector<int>, vector<int>> manacher(const string &s) {
    int n = s.size();
    vector<int> d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) { l = i - k; r = i + k; }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) { l = i - k - 1; r = i + k; }
    }
    return {d1, d2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (cin >> s) {
        int n = s.size();
        cout << (esPalindromo(s, 0, n - 1) ? "SI" : "NO") << "\n";
    }
    return 0;
}

// OJO con los casos borde del chequeo de dos punteros: con l == r (un solo
// caracter) el while no entra y devuelve true, que es lo correcto; con un
// rango vacio (l > r) tambien devuelve true. Si en tu problema el palindromo
// vacio NO cuenta, filtra el largo ANTES de llamar a la funcion.
