// <3
// Tema: CSES / BFS con Reconstruccion de Camino
// Resumen: BFS en grilla guardando de donde vino cada celda en la matriz anterior[][]
// O: (n*m), BFS guardando de donde se llego a cada celda
// Detalle: BFS en grilla guardando de donde vino cada celda en la matriz anterior[][], y al
// final se sube desde el destino hasta el origen leyendo esos padres y se invierte. La
// direccion de cada paso se deduce comparando coordenadas con el padre. CUANDO USAR: cuando el
// problema no pide solo la DISTANCIA sino el camino en si. La regla es que BFS da el camino
// minimo solo si todas las aristas pesan lo mismo; con pesos distintos toca Dijkstra, y con
// pesos 0 y 1 la version barata es 0-1 BFS con deque. Ojo con marcar: aqui se marca al encolar,
// y la celda 'B' se detecta ANTES de pisarla para no perder el destino.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    vector<string> matriz(n);

    long long Ax = -1;
    long long Ay = -1;

    for(long long i = 0; i < n; i++)
    {
        cin >> matriz[i];

        if(Ax == -1)
        {
            for(long long j = 0; j < m; j++)
            {
                if(matriz[i][j] == 'A')
                {
                    Ax = i;
                    Ay = j;
                    break;
                }
            }
        }
    }

    vector<vector<pair<long long, long long>>> anterior(
        n,
        vector<pair<long long, long long>>(m, {-1, -1})
    );

    queue<pair<long long, long long>> bfs;

    bfs.push({Ax, Ay});

    bool encontrado = false;

    long long Bx = -1;
    long long By = -1;

    while(!bfs.empty() && !encontrado)
    {
        long long x = bfs.front().first;
        long long y = bfs.front().second;

        bfs.pop();

        if(x > 0 && (matriz[x - 1][y] == '.' || matriz[x - 1][y] == 'B'))
        {
            anterior[x - 1][y] = {x, y};

            if(matriz[x - 1][y] == 'B')
            {
                Bx = x - 1;
                By = y;
                encontrado = true;
                break;
            }

            matriz[x - 1][y] = 'X';
            bfs.push({x - 1, y});
        }

        if(x + 1 < n && (matriz[x + 1][y] == '.' || matriz[x + 1][y] == 'B'))
        {
            anterior[x + 1][y] = {x, y};

            if(matriz[x + 1][y] == 'B')
            {
                Bx = x + 1;
                By = y;
                encontrado = true;
                break;
            }

            matriz[x + 1][y] = 'X';
            bfs.push({x + 1, y});
        }

        if(y > 0 && (matriz[x][y - 1] == '.' || matriz[x][y - 1] == 'B'))
        {
            anterior[x][y - 1] = {x, y};

            if(matriz[x][y - 1] == 'B')
            {
                Bx = x;
                By = y - 1;
                encontrado = true;
                break;
            }

            matriz[x][y - 1] = 'X';
            bfs.push({x, y - 1});
        }

        if(y + 1 < m && (matriz[x][y + 1] == '.' || matriz[x][y + 1] == 'B'))
        {
            anterior[x][y + 1] = {x, y};

            if(matriz[x][y + 1] == 'B')
            {
                Bx = x;
                By = y + 1;
                encontrado = true;
                break;
            }

            matriz[x][y + 1] = 'X';
            bfs.push({x, y + 1});
        }
    }

    if(!encontrado)
    {
        cout << "NO\n";
        return 0;
    }

    string recorrido = "";

    long long x = Bx;
    long long y = By;

    while(x != Ax || y != Ay)
    {
        long long anteriorX = anterior[x][y].first;
        long long anteriorY = anterior[x][y].second;

        if(x - anteriorX > 0)
        {
            recorrido += "D";
        }
        else if(x - anteriorX < 0)
        {
            recorrido += "U";
        }
        else if(y - anteriorY > 0)
        {
            recorrido += "R";
        }
        else
        {
            recorrido += "L";
        }

        x = anteriorX;
        y = anteriorY;
    }
    
    reverse(recorrido.begin(), recorrido.end());

    cout << "YES\n";
    cout << recorrido.size() << '\n';
    cout << recorrido << '\n';

    return 0;
}