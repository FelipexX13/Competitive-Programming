// <3
// Tema: CSES / Transformada de Burrows-Wheeler Inversa
// O: (n log n) por el stable_sort, (n) con counting sort
// Uso: ordenar estable por caracter da nxt; seguir la cadena desde pos 0 y voltear
// Deshacer la transformada de Burrows-Wheeler: dada la ultima columna de las rotaciones
// ordenadas, recuperar la cadena original.
// La propiedad que lo resuelve: la i-esima aparicion de una letra en la ULTIMA columna es la
// misma que la i-esima aparicion de esa letra en la PRIMERA columna. Por eso basta ordenar de
// forma ESTABLE los indices por caracter: eso construye la primera columna conservando el orden
// relativo, y nxt[] queda siendo el enlace de cada posicion a la siguiente.
// Que el sort sea ESTABLE no es opcional, es lo que hace que la propiedad valga.
// Se recorre la cadena saltando por nxt y al final se invierte, porque el recorrido la va
// sacando al reves.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    int n = s.size();

    vector<int> orden(n);
    iota(orden.begin(), orden.end(), 0);

    stable_sort(orden.begin(), orden.end(), [&](int a, int b)
    {
        return s[a] < s[b];
    });

    vector<int> nxt(n);

    for(int i = 0; i < n; i++)
        nxt[orden[i]] = i;

    int pos = 0;
    string ans;

    for(int i = 0; i < n - 1; i++)
    {
        ans += s[pos];
        pos = nxt[pos];
    }

    reverse(ans.begin(), ans.end());

    cout << ans << '\n';
}
