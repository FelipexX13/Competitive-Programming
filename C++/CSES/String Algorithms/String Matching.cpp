// <3
// Tema: CSES / KMP (Busqueda de Patron)
// Resumen: KMP: cuantas veces aparece p en s, en O(n + m)
// O: (n + m), KMP
// Detalle: KMP: cuantas veces aparece p en s, en O(n + m). Primero la funcion de prefijos de p,
// pi[i] = el largo del borde mas largo de p[0..i]. Despues se recorre s manteniendo j, cuanto
// del patron ya coincide; cuando falla, en vez de volver a empezar se retrocede a pi[j-1], que
// es cuanto del patron sigue coincidiendo gratis. DOS DETALLES QUE DECIDEN SI CUENTA BIEN:
// despues de un match se hace j = pi[j-1] y no j = 0, y eso es lo que permite contar
// apariciones SOLAPADAS ("aa" en "aaa" son dos). Y el while de retroceso va ANTES del if que
// avanza, siempre. Por que es lineal: j sube a lo sumo 1 por caracter, y cada retroceso lo
// baja; no puede bajar mas de lo que subio. CUANDO USAR: buscar un patron fijo. Si son muchos
// patrones a la vez, Aho-Corasick; si hay que comparar substrings arbitrarios, hashing; si
// piden los bordes o periodos, la misma pi sirve (ver "Finding Borders" y "Finding Periods").
#include <bits/stdc++.h>
using namespace std;

// Retorna cuantas veces aparece p dentro de s.
// Permite apariciones solapadas.
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

    string s, p;

    cin >> s >> p;

    cout << KMP(s, p) << '\n';

    return 0;
}
