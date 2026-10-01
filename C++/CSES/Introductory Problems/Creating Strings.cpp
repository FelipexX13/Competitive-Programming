// <3
// Tema: CSES / Backtracking sobre Frecuencias
// Resumen: Generar todas las permutaciones DISTINTAS
// O: (cantidad de permutaciones * n)
// Detalle: Generar todas las permutaciones DISTINTAS, y el truco esta en recorrer el ALFABETO
// en cada posicion en vez de recorrer las posiciones del string. Como se elige "cual letra va
// aqui" y cada letra se considera una sola vez por nivel, las repetidas no generan duplicados:
// no hay que filtrar nada despues. El freq[i]-- antes de bajar y el freq[i]++ al volver es el
// patron de prestamo de siempre. Y como el alfabeto se recorre de la 'a' a la 'z', las salidas
// ya vienen en orden lexicografico. ALTERNATIVA: ordenar la cadena y usar next_permutation en
// un do-while, que tambien salta duplicados y es mas corto. Esta version se prefiere cuando hay
// que podar por algo. CUANDO USAR: "todas las permutaciones distintas" con letras repetidas.
// Permutar posiciones y meter en un set funciona pero desperdicia trabajo.

#include <bits/stdc++.h>
using namespace std;

vector<string> ans;
string s;
int freq[26];

void solve(string cur) {
    if (cur.size() == s.size()) {
        ans.push_back(cur);
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) continue;

        freq[i]--;
        solve(cur + char('a' + i));
        freq[i]++;
    }
}

int main() {
    cin >> s;

    for (char c : s)
        freq[c - 'a']++;

    solve("");

    cout << ans.size() << '\n';

    for (auto &x : ans)
        cout << x << '\n';
}
