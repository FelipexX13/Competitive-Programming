// <3
// Tema: CSES / Deteccion de Ciclo con BFS
// Resumen: Hallar un ciclo en grafo no dirigido y reconstruirlo subiendo por los padres
// O: (n + m), BFS excluyendo al padre inmediato
// Detalle: Se busca un ciclo en grafo no dirigido: si durante el recorrido aparece una arista
// hacia un nodo YA visitado que no es el padre inmediato, ahi se cierra un ciclo, y se
// reconstruye subiendo por los padres desde los dos extremos de esa arista. La trampa del no
// dirigido es justamente excluir al padre: si no, toda arista u-v se ve como ciclo de largo 2
// apenas se vuelve a mirar. CUANDO USAR: "existe un ciclo", "hay que devolverlo". En grafo
// DIRIGIDO esto no aplica: ahi se usa DFS con tres colores (blanco, gris, negro) y el ciclo es
// una arista hacia un gris.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;

    cin >> n >> m;

    vector<vector<long long>> matriz(n + 1);

    long long a, b;

    while(m--)
    {
        cin >> a >> b;

        matriz[a].push_back(b);
        matriz[b].push_back(a);
    }
    
    vector<long long> anterior(n + 1, -1);
    vector<bool> recorrido(n + 1, false);

    for(long long i = 1; i <= n; i++)
    {
        if(recorrido[i]) continue;
        
        queue<long long> cola;

        recorrido[i] = true;
        cola.push(i);

        while(!cola.empty())
        {
            long long x = cola.front();
            cola.pop();

            for(long long z : matriz[x])
            {
                if(!recorrido[z])
                {
                    recorrido[z] = true;
                    anterior[z] = x;
                    cola.push(z);
                }
                else if(anterior[x] != z)
                {
                    vector<long long> recorridoX;
                    vector<long long> recorridoZ;

                    long long actual = x;

                    while(actual != -1)
                    {
                        recorridoX.push_back(actual);

                        if(actual == i)
                        {
                            break;
                        }

                        actual = anterior[actual];
                    }

                    actual = z;

                    while(actual != -1)
                    {
                        recorridoZ.push_back(actual);

                        if(actual == i)
                        {
                            break;
                        }

                        actual = anterior[actual];
                    }

                    reverse(recorridoX.begin(), recorridoX.end());
                    reverse(recorridoZ.begin(), recorridoZ.end());

                    long long posicion = 0;

                    while(posicion < recorridoX.size() &&
                          posicion < recorridoZ.size() &&
                          recorridoX[posicion] == recorridoZ[posicion])
                    {
                        posicion++;
                    }

                    posicion--;

                    cout << recorridoX.size() + recorridoZ.size()
                            - 2 * posicion << '\n';

                    for(long long j = posicion; j < recorridoX.size(); j++)
                    {
                        cout << recorridoX[j] << ' ';
                    }

                    for(long long j = recorridoZ.size() - 1; j >= posicion; j--)
                    {
                        cout << recorridoZ[j] << ' ';
                    }

                    cout << '\n';

                    return 0;
                }
            }
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}