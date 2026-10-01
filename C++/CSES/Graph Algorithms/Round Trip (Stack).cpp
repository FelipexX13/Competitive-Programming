// <3
// Tema: CSES / Deteccion de Ciclo con Pila (DFS Iterativo)
// Resumen: El mismo problema que Round Trip pero cambiando la cola por una PILA, o sea DFS en
// vez de BFS
// O: (n + m), DFS iterativo con pila explicita
// Detalle: El mismo problema que Round Trip pero cambiando la cola por una PILA, o sea DFS en
// vez de BFS, escrito de forma iterativa. Para detectar ciclos da igual cual de los dos se use,
// y esa es la ensenanza: la estructura es lo unico que cambia entre BFS y DFS. Vale tener las
// dos versiones porque a veces el problema pide el ciclo mas corto (BFS ayuda) y a veces
// cualquiera (DFS es mas directo). POR QUE ITERATIVO: con n hasta 10^5 un DFS recursivo se
// arriesga a stack overflow. Pasar la recursion a una pila explicita es la salida estandar, y
// es lo que hace este archivo.

#include <iostream>
#include <vector>
#include <stack>
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
        
        stack<long long> pila;

        recorrido[i] = true;
        pila.push(i);

        while(!pila.empty())
        {
            long long x = pila.top();
            pila.pop();

            for(long long z : matriz[x])
            {
                if(!recorrido[z])
                {
                    recorrido[z] = true;
                    anterior[z] = x;
                    pila.push(z);
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