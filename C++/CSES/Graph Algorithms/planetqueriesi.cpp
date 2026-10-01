// <3
// Tema: CSES / Binary Lifting sobre Grafo Funcional
// Resumen: Cada planeta tiene EXACTAMENTE un teletransporte de salida, asi que la estructura es
// un grafo funcional
// O: (n log k) de tabla y (log k) por consulta
// Detalle: Cada planeta tiene EXACTAMENTE un teletransporte de salida, asi que la estructura es
// un grafo funcional: una funcion x -> siguiente[x]. Las consultas piden donde se termina tras
// k saltos, con k hasta 10^9. BINARY LIFTING: siguiente[j][i] es a donde se llega desde i con
// 2^j saltos, y se construye con siguiente[j][i] = siguiente[j-1][siguiente[j-1][i]] (dar 2^j
// saltos es dar 2^(j-1) dos veces). Despues cada consulta descompone k en binario y aplica los
// saltos de los bits encendidos: O(log k) por consulta en vez de caminar k pasos. POR QUE NO
// HACE FALTA DETECTAR CICLOS: aunque el grafo funcional siempre acaba en un ciclo, el doubling
// lo atraviesa sin enterarse. La alternativa (hallar el ciclo y usar modulo) es mas rapida en
// memoria pero mucho mas facil de romper en los bordes. LOG = 31 cubre k hasta 2^31 - 1,
// suficiente para 10^9. Si k fuera mayor hay que subirlo, y ese es el error silencioso de esta
// plantilla: con un LOG corto los bits altos de k se ignoran y la respuesta sale mal sin ningun
// aviso. La tabla ocupa LOG * n; con n = 2*10^5 son unos 6 millones de long long, asi que si
// aprieta la memoria conviene guardarla en int. Es el mismo mecanismo de "Visible Building
// Queries" y "Movie Festival Queries" de este cuaderno: si un puntero define una funcion, sus
// potencias se precalculan con doubling.

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, q;
    cin >> n >> q;

    const long long LOG = 31;

    vector<vector<long long>> siguiente(LOG, vector<long long>(n));

    for(long long i = 0; i < n; i++)
    {
        cin >> siguiente[0][i];
        siguiente[0][i]--;
    }

    for(long long j = 1; j < LOG; j++)
    {
        for(long long i = 0; i < n; i++)
        {
            siguiente[j][i] = siguiente[j - 1][siguiente[j - 1][i]];
        }
    }

    while(q--)
    {
        long long x, k;
        cin >> x >> k;

        x--;

        for(long long j = 0; j < LOG; j++)
        {
            if(k & (1LL << j))
            {
                x = siguiente[j][x];
            }
        }

        cout << x + 1 << '\n';
    }

    return 0;
}