// <3
// Tema: CSES / BFS Multifuente + BFS de Escape
// Resumen: Dos BFS encadenados, y el primero es el truco que vale aprender
// Detalle: Dos BFS encadenados, y el primero es el truco que vale aprender: un BFS MULTIFUENTE,
// con TODOS los monstruos encolados con distancia 0 a la vez. Eso da, en una sola pasada
// O(n*m), la distancia de cada celda al monstruo mas cercano, que es lo mismo que correr un BFS
// por monstruo pero sin pagar el costo de cada uno. Despues va el BFS del jugador, que solo
// entra a una celda si llega ESTRICTAMENTE antes que el monstruo mas cercano. Guardando la
// direccion de llegada se reconstruye la salida. CUANDO USAR EL MULTIFUENTE: siempre que la
// pregunta sea "distancia al mas cercano de un conjunto" en vez de "distancia desde un punto".
// Aparece en incendios que se propagan, celdas contaminadas, o el tipico "cuanto tarda en
// llenarse todo".

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

    vector<string> matriz(n);

    vector<pair<long long, long long>> monstruos;

    long long Ax = -1;
    long long Ay = -1;

    for(long long i = 0; i < n; i++)
    {
        cin >> matriz[i];

        for(long long j = 0; j < m; j++)
        {
            if(matriz[i][j] == 'M')
            {
                monstruos.push_back({i, j});
            }
            else if(matriz[i][j] == 'A')
            {
                Ax = i;
                Ay = j;
            }
        }
    }

    if(Ax == 0 || Ax == n - 1 || Ay == 0 || Ay == m - 1)
    {
        cout << "YES\n";
        cout << "0\n";
        cout << '\n';
        return 0;
    }

    long long dx[4] = {-1, 1, 0, 0};
    long long dy[4] = {0, 0, -1, 1};

    vector<vector<long long>> distanciaM(n, vector<long long>(m, -1));

    queue<pair<long long, long long>> cola;

    for(pair<long long, long long> monstruo : monstruos)
    {
        distanciaM[monstruo.first][monstruo.second] = 0;
        cola.push(monstruo);
    }

    while(!cola.empty())
    {
        long long x = cola.front().first;
        long long y = cola.front().second;
        cola.pop();

        for(long long k = 0; k < 4; k++)
        {
            long long nx = x + dx[k];
            long long ny = y + dy[k];

            if(nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }

            if(matriz[nx][ny] == '#')
            {
                continue;
            }

            if(distanciaM[nx][ny] == -1)
            {
                distanciaM[nx][ny] = distanciaM[x][y] + 1;
                cola.push({nx, ny});
            }
        }
    }

    vector<vector<long long>> distanciaA(n, vector<long long>(m, -1));
    vector<vector<char>> direccion(n, vector<char>(m));

    distanciaA[Ax][Ay] = 0;
    cola.push({Ax, Ay});

    long long salidaX = -1;
    long long salidaY = -1;

    while(!cola.empty())
    {
        long long x = cola.front().first;
        long long y = cola.front().second;
        cola.pop();

        for(long long k = 0; k < 4; k++)
        {
            long long nx = x + dx[k];
            long long ny = y + dy[k];

            if(nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }

            if(matriz[nx][ny] == '#')
            {
                continue;
            }

            if(distanciaA[nx][ny] != -1)
            {
                continue;
            }

            long long nuevaDistancia = distanciaA[x][y] + 1;

            if(distanciaM[nx][ny] != -1 &&
               nuevaDistancia >= distanciaM[nx][ny])
            {
                continue;
            }

            distanciaA[nx][ny] = nuevaDistancia;

            if(k == 0)
            {
                direccion[nx][ny] = 'U';
            }
            else if(k == 1)
            {
                direccion[nx][ny] = 'D';
            }
            else if(k == 2)
            {
                direccion[nx][ny] = 'L';
            }
            else
            {
                direccion[nx][ny] = 'R';
            }

            if(nx == 0 || nx == n - 1 || ny == 0 || ny == m - 1)
            {
                salidaX = nx;
                salidaY = ny;
                break;
            }

            cola.push({nx, ny});
        }

        if(salidaX != -1)
        {
            break;
        }
    }

    if(salidaX == -1)
    {
        cout << "NO\n";
        return 0;
    }

    string recorridoFinal;

    long long x = salidaX;
    long long y = salidaY;

    while(x != Ax || y != Ay)
    {
        char movimiento = direccion[x][y];

        recorridoFinal += movimiento;

        if(movimiento == 'R')
        {
            y--;
        }
        else if(movimiento == 'L')
        {
            y++;
        }
        else if(movimiento == 'D')
        {
            x--;
        }
        else
        {
            x++;
        }
    }

    reverse(recorridoFinal.begin(), recorridoFinal.end());

    cout << "YES\n";
    cout << recorridoFinal.size() << '\n';
    cout << recorridoFinal << '\n';

    return 0;
}