// <3
// Tema: Implementation / Template Base
// Resumen: Plantilla de arranque: fast IO, alias, constantes, macros y los utiles que se olvidan
// O: (1), es el esqueleto
// Uso: punto de partida: fast IO, lectura de matriz, gcd/lcm, setprecision
// Detalle: Plantilla de arranque para cualquier problema: includes, alias de tipos, constantes
// (MOD, INF, LLINF, EPS, PI), macros de recorrido (all, forn, forr, ford) y la desincronizacion
// de cin/cout que hace la lectura casi tan rapida como scanf. Incluye ademas los utilitarios
// que mas se olvidan en competencia: crear una matriz, imprimir con decimales fijos, borrar un
// rango de un vector, y obtener el indice (no el valor) del maximo o minimo. Ojo: __gcd /
// std::gcd y std::lcm ya vienen en la STL, no hace falta escribirlos a mano.

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const double EPS = 1e-9;
const double PI = acos(-1.0);

#define all(x) (x).begin(), (x).end()
#define forn(i, n) for(int i = 0; i < int(n); i++)
#define forr(i, a, b) for(int i = a; i <= b; i++)
#define ford(i, n) for(int i = int(n) - 1; i >= 0; i--)
#define endl '\n'

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int filas = 3, columnas = 4;
    vector<vector<int>> matriz(filas, vector<int>(columnas, 0));

    vector<int> v = {5, 1, 9, 3, 7};

    // indice del maximo y del minimo (no el valor)
    int idx_max = max_element(all(v)) - v.begin();
    int idx_min = min_element(all(v)) - v.begin();
    cout << idx_max << " " << idx_min << endl;

    // borrar desde el indice 1 hasta el 3 (sin incluir el 3)
    v.erase(v.begin() + 1, v.begin() + 3);

    // imprimir con decimales fijos
    double value = 1.0 / 3.0;
    cout << fixed << setprecision(6) << value << endl;

    // gcd ya viene en la STL (__gcd, o std::gcd/std::lcm si el juez tiene C++17).
    // Para el lcm, dividir ANTES de multiplicar evita desbordar.
    int a = 4, b = 6;
    cout << __gcd(12, 18) << " " << (a / __gcd(a, b)) * b << endl;

    return 0;
}
