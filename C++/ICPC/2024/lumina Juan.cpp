// <3
// Tema: Graph / Componentes Fuente con Kosaraju
// Resumen: El minimo de gemas a encender a mano para que la reaccion en cadena las encienda
// todas
// O: (n^2) por armar el grafo; el Kosaraju es (n+m)
// Detalle: La otra solucion del problema J de ICPC 2024 ("Lumina"): el minimo de gemas a
// encender a mano para que la reaccion en cadena las encienda todas. La respuesta es la
// cantidad de componentes fuertemente conexas SIN aristas entrantes desde otra componente. A
// diferencia de "J - Lumina" de esta carpeta, que usa Tarjan, esta usa KOSARAJU: un DFS sobre
// el grafo normal que apila los nodos por orden de terminacion, y despues un DFS sobre el grafo
// INVERSO tomando los nodos en orden inverso de esa pila. Cada arbol del segundo recorrido es
// una componente. CUAL CONVIENE: Kosaraju es mas facil de recordar (dos DFS y un reverse) pero
// necesita construir el grafo inverso, o sea el doble de memoria. Tarjan hace una sola pasada y
// no lo necesita, pero la logica de low[] y la pila es mas facil de escribir mal. Para un
// cuaderno vale tener las dos. OJO CON EL ORDEN DE NUMERACION: Kosaraju numera las componentes
// en orden topologico y Tarjan al reves. Aqui solo se cuentan las fuentes, asi que da igual,
// pero en 2-SAT esa diferencia voltea la regla de asignacion (ver "G - Signal Coverage" de esta
// carpeta). El grafo es DIRIGIDO e IMPLICITO: u alcanza a v si v cae dentro del radio de u, y
// como cada gema tiene su propio radio eso no es simetrico. Las aristas no se guardan, se
// recalculan con dist^2 <= r^2 en enteros. Verificado con los tres casos del sample (1, 2, 2).

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Circulo
{
    long long x;
    long long y;
    long long r;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;

    while(cin >> n && n != 0)
    {
        vector<Circulo> circulos(n);

        for(long long i = 0; i < n; i++)
        {
            cin >> circulos[i].x >> circulos[i].y >> circulos[i].r;
        }

        vector<vector<int>> conexion(n);

        for(long long a = 0; a < n; a++)
        {
            for(long long b = 0; b < n; b++)
            {
                if(a == b)
                {
                    continue;
                }

                long long dx = circulos[a].x - circulos[b].x;
                long long dy = circulos[a].y - circulos[b].y;

                long long distancia = dx * dx + dy * dy;

                if(distancia <= circulos[a].r * circulos[a].r)
                {
                    conexion[a].push_back(b);
                }
            }
        }

        vector<bool> visitado(n, false);
        vector<long long> ordenFinal;

        for(long long i = 0; i < n; i++)
        {
            if(visitado[i])
            {
                continue;
            }

            stack<pair<long long, long long>> pila;
            visitado[i] = true;
            pila.push({i, 0});

            while(!pila.empty())
            {
                long long actual = pila.top().first;
                long long posicion = pila.top().second;

                if(posicion == (long long)conexion[actual].size())
                {
                    ordenFinal.push_back(actual);
                    pila.pop();
                    continue;
                }

                long long siguiente = conexion[actual][posicion];
                pila.top().second++;

                if(!visitado[siguiente])
                {
                    visitado[siguiente] = true;
                    pila.push({siguiente, 0});
                }
            }
        }

        vector<bool> encontrado(n, false);

        long long contador = 0;

        for(long long k = n - 1; k >= 0; k--)
        {
            long long inicio = ordenFinal[k];

            if(encontrado[inicio])
            {
                continue;
            }

            queue<long long> cola;
            cola.push(inicio);
            encontrado[inicio] = true;
            contador++;

            while(!cola.empty())
            {
                long long actual = cola.front();
                cola.pop();

                for(long long siguiente : conexion[actual])
                {
                    if(!encontrado[siguiente])
                    {
                        encontrado[siguiente] = true;
                        cola.push(siguiente);
                    }
                }
            }
        }

        cout << contador << '\n';
    }

    return 0;
}