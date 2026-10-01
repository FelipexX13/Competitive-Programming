// <3
// Tema: CSES / BFS de Bicoloreo (Bipartito)
// Resumen: Bicoloreo por BFS: se pinta el primer nodo de 1 y cada vecino del color opuesto
// O: (n + m), BFS pintando dos colores
// Detalle: Bicoloreo por BFS: se pinta el primer nodo de 1 y cada vecino del color opuesto. Si
// en algun momento aparece una arista entre dos nodos del MISMO color, el grafo tiene un ciclo
// impar y no es bipartito. El for de afuera reinicia el BFS en cada componente, que es lo que
// se olvida. CUANDO USAR: cada vez que un problema pida partir en DOS grupos con "estos dos no
// pueden ir juntos", o preguntar si se puede 2-colorear. Bipartito equivale a no tener ciclos
// de longitud impar. Y es el prerrequisito para matching bipartito: si el problema habla de
// emparejar dos conjuntos, lo primero es verificar que el grafo sea bipartito.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    long long n, m;

    cin >> n >> m;

    vector<vector<long long>> vecinos(n + 1);

    long long a, b;

    while(m--)
    {
        cin >> a >> b;

        vecinos[a].push_back(b);
        vecinos[b].push_back(a);
    }

    vector<long long> valores(n + 1, -1);

    for(long long i = 1; i <= n; i++)
    {
        if(valores[i] == -1)
        {
            queue<long long> cola;

            valores[i] = 1;
            cola.push(i);

            while(!cola.empty())
            {
                long long actual = cola.front();
                cola.pop();

                for(long long conexion : vecinos[actual])
                {
                    if(valores[conexion] == -1)
                    {
                        if(valores[actual] == 1)
                        {
                            valores[conexion] = 2;
                        }
                        else
                        {
                            valores[conexion] = 1;
                        }

                        cola.push(conexion);
                    }
                    else if(valores[conexion] == valores[actual])
                    {
                        cout << "IMPOSSIBLE\n";
                        return 0;
                    }
                }
            }
        }
    }

    for(long long i = 1; i <= n; i++)
    {
        cout << valores[i];

        if(i < n)
        {
            cout << ' ';
        }
    }

    cout << '\n';

    return 0;
}