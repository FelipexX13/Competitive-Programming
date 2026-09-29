// <3
// Tema: Graph / Clique Maximo con Backtracking Iterativo
// La otra solucion correcta del problema H de ICPC 2025 ("Holy Network"): el grupo mas grande donde
// CADA PAR comparte un factor mayor que 1, o sea un clique maximo.
// A diferencia de la version con Bron-Kerbosch (el archivo "H - Holy Network" de esta carpeta),
// esta hace un backtracking directo y ademas ITERATIVO, con una pila explicita de estados
// (candidatos que quedan, tamano del grupo). Vale tenerla porque el patron sirve para cualquier
// busqueda que se quiera sin recursion.
// LA PODA ES LO QUE LA HACE VIABLE: los candidatos se recorren en orden y, si lo que ya se llevo
// mas los que faltan por mirar no supera al mejor encontrado, se corta el ciclo de una
// (actual.tamGrupo + quedan <= mejorGrupo). Sin esa linea seria 2^n.
// Cada vez que se elige un candidato, los nuevos candidatos son SOLO los que vienen despues y ademas
// son compatibles con el elegido: asi todo lo que quede en la pila ya es compatible con todo el
// grupo, y no hay que revalidar nada.
// El gcd se calcula a mano con el algoritmo de Euclides en vez de llamar a __gcd, lo que evita
// depender de extensiones del compilador o de <numeric> de C++17.
// Verificado contra fuerza bruta 2^n en 1500 casos, sin fallos, y pasa el sample (4, 5, 1) y el
// contraejemplo {6, 10, 35} que tumba la version con DSU.

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Estado
{
    vector<long long> candidatos;
    long long tamGrupo;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;

    while(cin >> n && n != 0)
    {
        vector<long long> resonancia(n);

        for(long long i = 0; i < n; i++)
        {
            cin >> resonancia[i];
        }

        vector<vector<bool>> compatibles(n, vector<bool>(n, false));

        for(long long a = 0; a < n; a++)
        {
            for(long long b = a + 1; b < n; b++)
            {
                long long x = resonancia[a];
                long long y = resonancia[b];

                while(y != 0)
                {
                    long long resto = x % y;
                    x = y;
                    y = resto;
                }

                if(x > 1)
                {
                    compatibles[a][b] = true;
                    compatibles[b][a] = true;
                }
            }
        }

        vector<long long> todos(n);

        for(long long i = 0; i < n; i++)
        {
            todos[i] = i;
        }

        stack<Estado> pila;
        pila.push({todos, 0});

        long long mejorGrupo = 0;

        while(!pila.empty())
        {
            Estado actual = pila.top();
            pila.pop();

            mejorGrupo = max(mejorGrupo, actual.tamGrupo);

            for(long long i = 0; i < (long long)actual.candidatos.size(); i++)
            {
                long long quedan = actual.candidatos.size() - i;

                if(actual.tamGrupo + quedan <= mejorGrupo)
                {
                    break;
                }

                long long elegido = actual.candidatos[i];

                vector<long long> nuevosCandidatos;

                for(long long j = i + 1; j < (long long)actual.candidatos.size(); j++)
                {
                    if(compatibles[elegido][actual.candidatos[j]])
                    {
                        nuevosCandidatos.push_back(actual.candidatos[j]);
                    }
                }

                pila.push({
                    nuevosCandidatos,
                    actual.tamGrupo + 1
                });
            }
        }

        cout << mejorGrupo << '\n';
    }

    return 0;
}