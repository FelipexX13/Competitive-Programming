// <3
// Tema: CSES / Floyd-Warshall
// Resumen: Floyd-Warshall, la solucion canonica de todos-contra-todos
// Detalle: Floyd-Warshall, la solucion canonica de todos-contra-todos: tres for anidados donde
// el de AFUERA es el nodo intermedio k. Ese orden no es negociable, y es el error numero uno de
// esta plantilla: si k va por dentro, el algoritmo no considera caminos con varios intermedios
// y da respuestas mal. La invariante es que despues de la iteracion k ya estan todos los
// caminos que solo usan {0..k} como intermedios, y de ahi sale la induccion. Se inicializa
// dist[i][i] = 0 y se guarda la arista MAS BARATA entre cada par, porque puede haber carreteras
// repetidas. El continue cuando dist[i][k] es infinito no es solo optimizacion: evita que se
// sumen dos infinitos y se desborde. ESTE ARCHIVO ES LA OTRA SOLUCION del mismo problema que
// "Shortest Routes II", que ahi esta resuelto con n Dijkstras. Vale la pena tener las dos y ver
// la diferencia: Floyd es O(n^3) y se escribe en tres lineas, n Dijkstras es O(n*m log n) y
// gana solo si el grafo es disperso. Con n <= 500, que es el limite tipico, Floyd es lo que uno
// escribe. CUANDO USAR: n <= 500 y hacen falta todos los pares. Tambien sirve para cierre
// transitivo (cambiando min y + por or y and) y para el cuello de botella minimax (cambiando +
// por max). Aguanta pesos negativos siempre que no haya ciclos negativos.

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, q;
    cin >> n >> m >> q;

    const long long INF = 1e18;

    vector<vector<long long>> dist(n, vector<long long>(n, INF));

    for(long long i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }

    for(long long i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        a--;
        b--;

        // puede haber varias carreteras entre a y b: me quedo con la menor
        if(c < dist[a][b])
        {
            dist[a][b] = c;
            dist[b][a] = c;
        }
    }

    // Floyd-Warshall
    for(long long k = 0; k < n; k++)              // nodo intermedio
    {
        for(long long i = 0; i < n; i++)
        {
            if(dist[i][k] == INF)                 // no llego a k desde i
            {
                continue;
            }

            for(long long j = 0; j < n; j++)
            {
                if(dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(long long i = 0; i < q; i++)
    {
        long long a, b;
        cin >> a >> b;

        a--;
        b--;

        if(dist[a][b] == INF)
        {
            cout << -1 << '\n';
        }
        else
        {
            cout << dist[a][b] << '\n';
        }
    }

    return 0;
}