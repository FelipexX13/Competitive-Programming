// <3
// Tema: CSES / Camino Mas Largo en DAG (DFS con Memo)
// Resumen: Camino con mas nodos de 1 a n en un DAG, con DFS memoizado: mejor[u] = 1 + max de
// mejor[hijo]
// O: (n + m), DFS con memo sobre el DAG
// Detalle: Camino con mas nodos de 1 a n en un DAG, con DFS memoizado: mejor[u] = 1 + max de
// mejor[hijo]. En un grafo cualquiera el camino mas largo es NP-dificil; aqui es lineal SOLO
// porque no hay ciclos, y eso hay que tenerlo presente antes de intentarlo en otro problema. EL
// TRUCO DEL CERO: mejor[u] = 0 significa "desde u no se llega a n". Por eso un hijo solo se
// toma si camino > 0; asi los callejones sin salida no contaminan el maximo, y si al final
// mejor[0] vale 0 la respuesta es IMPOSSIBLE. El arreglo siguiente[] guarda por donde se fue el
// maximo, y con eso se reconstruye la ruta. OJO CON LA RECURSION: con un camino de 10^5 nodos
// la pila de llamadas llega a esa profundidad. En CSES pasa, pero en un juez con pila chica
// puede dar error de ejecucion. La version sin riesgo es la misma DP recorriendo en orden
// topologico con Kahn, como "Game Routes".

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long n, m;

vector<vector<long long>> conexiones;
vector<long long> mejor;
vector<long long> siguiente;

long long dfs(long long actual)
{
    if(actual == n - 1)
        return 1;

    if(mejor[actual] != -1)
        return mejor[actual];

    mejor[actual] = 0;

    for(long long hijo : conexiones[actual])
    {
        long long camino = dfs(hijo);

        if(camino > 0 && camino + 1 > mejor[actual])
        {
            mejor[actual] = camino + 1;
            siguiente[actual] = hijo;
        }
    }

    return mejor[actual];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    conexiones.resize(n);

    for(long long i = 0; i < m; i++)
    {
        long long a, b;
        cin >> a >> b;

        conexiones[a - 1].push_back(b - 1);
    }

    mejor.assign(n, -1);
    siguiente.assign(n, -1);

    long long largo = dfs(0);

    if(largo == 0)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << largo << '\n';

    long long actual = 0;

    while(actual != -1)
    {
        cout << actual + 1 << ' ';

        if(actual == n - 1)
            break;

        actual = siguiente[actual];
    }

    cout << '\n';

    return 0;
}