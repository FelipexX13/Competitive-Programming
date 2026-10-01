// <3
// Tema: CSES / Funcion Z y Funcion de Prefijos
// Resumen: Funcion Z y funcion de prefijos, las dos lado a lado
// O: (n) cada una
// Uso: zFunction(s) -> z; prefixFunction(s) -> pi  // ambos 0-indexados
// Detalle: Las dos funciones basicas de cadenas, una al lado de la otra. z[i] = largo del
// prefijo comun mas largo entre s y s[i..]. La ventana [l, r] es el truco: es la coincidencia
// mas a la derecha que se conoce, y mientras i cae adentro se reusa el valor ya calculado z[i -
// l] en vez de comparar desde cero. Eso es lo que la deja lineal. pi[i] = largo del borde mas
// largo de s[0..i], o sea el prefijo propio mas largo que tambien es sufijo. El while que baja
// j = pi[j-1] es el mismo salto de fallo de KMP. LAS DOS SIRVEN PARA LO MISMO casi siempre, y
// cual usar es cuestion de gusto: la funcion Z se lee mas facil para 'donde aparece el patron'
// (se busca z[i] == |patron| en patron + '#' + texto) y la de prefijos es la que sirve para
// periodos, bordes y el automata de KMP. OJO: aca z[0] se fuerza a 0. La convencion comun es
// z[0] = n; el juez de este problema pide 0.

#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(string s)
{
    int n = s.size();

    vector<int> z(n);
    int l = 0;
    int r = 0;

    for(int i = 1; i < n; i++)
    {
        if(i <= r)
        {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while(i + z[i] < n &&
              s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }

        if(i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }

    z[0] = 0;

    return z;
}

vector<int> prefixFunction(string s)
{
    int n = s.size();

    vector<int> pi(n);

    for(int i = 1; i < n; i++)
    {
        int j = pi[i - 1];

        while(j > 0 && s[i] != s[j])
        {
            j = pi[j - 1];
        }

        if(s[i] == s[j])
        {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<int> z = zFunction(s);
    vector<int> pi = prefixFunction(s);

    for(int i = 0; i < (int)s.size(); i++)
    {
        cout << z[i];

        if(i + 1 < (int)s.size())
            cout << ' ';
    }

    cout << '\n';

    for(int i = 0; i < (int)s.size(); i++)
    {
        cout << pi[i];

        if(i + 1 < (int)s.size())
            cout << ' ';
    }

    cout << '\n';

    return 0;
}
