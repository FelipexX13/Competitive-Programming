// <3
// Tema: CSES / Bellman-Ford (Ciclo Negativo)
// Bellman-Ford usado no para hallar distancias sino para DETECTAR un ciclo negativo y devolverlo.
// Se relaja n veces; si en la ultima pasada todavia hubo una mejora, esa mejora solo pudo venir de
// un ciclo negativo, y el nodo donde ocurrio queda guardado.
// EL TRUCO DE LA RECONSTRUCCION, que es lo que hay que copiar: el nodo donde se detecto la mejora
// NO tiene por que estar dentro del ciclo, puede ser uno colgado mas adelante. La solucion es subir
// n veces por el arreglo de padres: despues de n saltos es seguro que ya se entro al ciclo, porque
// la cadena de padres tiene a lo sumo n nodos antes de enrollarse. Desde ahi se sigue a los padres
// hasta volver al mismo nodo y ese es el ciclo.
// Aqui las distancias arrancan TODAS en 0, no en infinito, y es a proposito: equivale a poner un
// origen virtual conectado a todos con peso 0, asi se encuentran ciclos negativos en cualquier
// componente y no solo en la que alcanza el nodo 1.
// CUANDO USAR: detectar ciclos negativos, que es lo unico que Dijkstra no puede hacer. Aparece en
// arbitraje de monedas (con logaritmos negados) y en sistemas de restricciones de diferencias.
// OJO: usa structured bindings (auto [a, b]), que piden C++17. En CSES compila, pero con
// un g++ viejo hay que volver a .first y .second.

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    vector<vector<pair<long long, long long>>> conexion(n);

    for(long long i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        conexion[--a].push_back({--b, c});
    }

    vector<long long> distancia(n, 0);
    vector<long long> padre(n, -1);

    long long ciclo = -1;

    for(long long i = 0; i < n; i++)
    {
        ciclo = -1;

        for(long long a = 0; a < n; a++)
        {
            for(auto [b, c] : conexion[a])
            {
                if(distancia[a] + c < distancia[b])
                {
                    distancia[b] = distancia[a] + c;
                    padre[b] = a;
                    ciclo = b;
                }
            }
        }

        if(ciclo == -1)
            break;
    }

    if(ciclo == -1)
    {
        cout << "NO\n";
        return 0;
    }

    for(long long i = 0; i < n; i++)
        ciclo = padre[ciclo];

    vector<long long> respuesta;

    long long actual = ciclo;

    do
    {
        respuesta.push_back(actual);
        actual = padre[actual];
    }
    while(actual != ciclo);

    respuesta.push_back(ciclo);

    cout << "YES\n";

    for(long long i = respuesta.size() - 1; i >= 0; i--)
        cout << respuesta[i] + 1 << ' ';

    cout << '\n';

    return 0;
}