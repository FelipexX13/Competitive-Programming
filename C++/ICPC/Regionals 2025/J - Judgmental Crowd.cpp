// <3
// Tema: String / KMP para Contar Ocurrencias Solapadas
// Resumen: La reaccion del publico se calcula contando cuantas veces aparecen tres palabras en
// la cadena y...
// O: (|s| + |p|), KMP contando ocurrencias solapadas
// Detalle: Resuelve "Judgmental Crowd" (problema J, Regionals 2025): la reaccion del publico se
// calcula contando cuantas veces aparecen tres palabras en la cadena y combinandolas con pesos,
// ha - boooo + 3 * bravo EL DETALLE QUE DECIDE EL PROBLEMA es contar ocurrencias SOLAPADAS.
// Tras un match no se reinicia j = 0 sino j = pi[j-1], que deja el automata en el sufijo mas
// largo que todavia sirve. Con "haha" hay DOS ocurrencias de "ha" y no una; reiniciando en 0 se
// perderia la segunda cuando los patrones se pisan (con "aa" dentro de "aaa" pasa lo mismo). Se
// llama a la misma funcion KMP tres veces, una por palabra, porque los patrones son fijos y
// cortos. Si fueran muchos patrones convendria Aho-Corasick, que los busca todos en una sola
// pasada. La funcion de prefijos se calcula sobre el PATRON, no sobre el texto: pi[i] es el
// borde mas largo de p[0..i], y es lo que permite retroceder sin volver atras en el texto. Por
// eso todo el conteo es O(|s| + |p|). Comprobado: con "haha" da 2, que son las dos ocurrencias
// de "ha".

#include <bits/stdc++.h>
using namespace std;

int KMP(const string& s, const string& p) {

    int n = s.size();
    int m = p.size();

    // Prefix function del patron
    vector<int> pi(m);

    for (int i = 1; i < m; i++) {

        int j = pi[i - 1];

        while (j > 0 && p[i] != p[j])
            j = pi[j - 1];

        if (p[i] == p[j])
            j++;

        pi[i] = j;
    }

    // Buscar p dentro de s
    int ans = 0;
    int j = 0;

    for (int i = 0; i < n; i++) {

        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];

        if (s[i] == p[j])
            j++;

        if (j == m) {
            ans++;

            // Importante para permitir solapamientos
            j = pi[j - 1];
        }
    }

    return ans;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;

    cin >> s;

    cout << KMP(s, "ha") - KMP(s, "boooo") + 3*KMP(s, "bravo")  << '\n';

    return 0;
}


