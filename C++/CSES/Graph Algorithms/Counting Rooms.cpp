// <3
// Tema: CSES / Flood Fill en Grilla (BFS)
// Resumen: Contar componentes conexas en una grilla
// O: (n*m), cada celda se visita una vez
// Detalle: Contar componentes conexas en una grilla. Se barre celda por celda y, al encontrar
// una libre sin visitar, se lanza un BFS que marca todo su cuarto y se suma uno al total.
// Marcar la celda como visitada AL ENCOLARLA (no al sacarla) es lo que evita que entre dos
// veces a la cola. Aqui se reusa la matriz de entrada como arreglo de visitados poniendo 'X':
// ahorra memoria y una estructura aparte. CUANDO USAR: cualquier problema de grilla que
// pregunte cuantas regiones, islas, lagos o manchas hay, o el tamano de la region que contiene
// a una celda. BFS y DFS dan lo mismo aqui; se prefiere BFS iterativo porque con 1000x1000
// celdas un DFS recursivo puede reventar la pila.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    vector<string> matriz(n);

    for(long long i = 0; i < n; i++)
    {
        cin >> matriz[i];
    }

    queue<pair<long long, long long>> cuartos;

    long long numCuartos = 0;

    for(long long i = 0; i < n; i++)
    {
        for(long long j = 0; j < m; j++)
        {
            if(matriz[i][j] == '.')
            {
                matriz[i][j] = 'X';
                cuartos.push({i, j});

                while(!cuartos.empty())
                {
                    long long x = cuartos.front().first;
                    long long y = cuartos.front().second;
                    cuartos.pop();

                    if(x - 1 >= 0 && matriz[x - 1][y] == '.')
                    {
                        matriz[x - 1][y] = 'X';
                        cuartos.push({x - 1, y});
                    }

                    if(x + 1 < n && matriz[x + 1][y] == '.')
                    {
                        matriz[x + 1][y] = 'X';
                        cuartos.push({x + 1, y});
                    }

                    if(y - 1 >= 0 && matriz[x][y - 1] == '.')
                    {
                        matriz[x][y - 1] = 'X';
                        cuartos.push({x, y - 1});
                    }

                    if(y + 1 < m && matriz[x][y + 1] == '.')
                    {
                        matriz[x][y + 1] = 'X';
                        cuartos.push({x, y + 1});
                    }
                }

                numCuartos++;
            }
        }
    }

    cout << numCuartos;

    return 0;
}