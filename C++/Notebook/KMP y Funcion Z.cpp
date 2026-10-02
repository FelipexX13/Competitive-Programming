// <3
// Tema: String / KMP y Funcion Z
// Resumen: Todas las apariciones de un patron en O(n + m), bordes, periodo minimo y funcion Z
// O: (n + m)
// Uso: buscar(texto, patron) -> inicios, con solapamiento; prefijo(s); funcionZ(s)
// Detalle: pi[i] (funcion de prefijo) es el largo del prefijo propio mas largo de s[0..i]
// que tambien es sufijo de s[0..i]. KMP recorre el texto y cuando falla retrocede a pi en
// vez de volver a empezar, asi que nunca retrocede en el texto. Cuenta apariciones
// SOLAPADAS ("aa" en "aaa" son 2): Judgmental Crowd (Regional 2025) era esto.
// Periodo minimo de s: p = n - pi[n-1]; s es una repeticion exacta de su prefijo de largo
// p si y solo si p divide a n (si no, el menor periodo sigue siendo p pero no cierra justo).
// Todos los bordes (prefijos que tambien son sufijos): n, pi[n-1], pi[pi[n-1]-1], ...
// z[i] es el largo del prefijo comun mas largo entre s y s[i..]; z[0] = 0 por convencion.
// Buscar con Z: calcular Z de patron + '#' + texto (con '#' que no aparezca en ninguno) y
// mirar donde z == largo del patron.

#include <bits/stdc++.h>

using namespace std;

vector<int> prefijo(const string &s)
{
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++)
    {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

vector<int> buscar(const string &t, const string &p)
{
    vector<int> res;
    if (p.empty()) return res;
    vector<int> pi = prefijo(p);
    int k = 0;
    for (int i = 0; i < (int)t.size(); i++)
    {
        while (k > 0 && t[i] != p[k]) k = pi[k - 1];
        if (t[i] == p[k]) k++;
        if (k == (int)p.size())
        {
            res.push_back(i - k + 1);
            k = pi[k - 1];
        }
    }
    return res;
}

vector<int> funcionZ(const string &s)
{
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
