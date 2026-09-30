// <3
// Tema: Graph / Existencia de Camino Euleriano con Aristas Ocultas
// Resuelve "Apple Pie" (problema A, Regionals 2025). Se conoce un prefijo L y un sufijo R de una
// secuencia, y la parte del medio quedo tapada por la torta: hay que decidir si existe alguna forma
// de completarla.
// EL MODELO: cada elemento consecutivo de la secuencia es una ARISTA entre dos valores, asi que la
// secuencia entera es un camino en un multigrafo. Lo conocido (L y R) fija unas aristas; lo tapado
// tiene que ser un camino que use EXACTAMENTE las aristas restantes. O sea, la pregunta es si las
// aristas que sobran forman un CAMINO EULERIANO entre dos extremos dados.
// LAS CONDICIONES DE EULER, que es lo que hay que tener a mano:
//   - camino cerrado (circuito): todos los grados son PARES y el grafo es conexo sobre las aristas
//   - camino abierto: exactamente DOS vertices de grado impar, y son los extremos
// La funcion canEuler separa cuatro casos segun cuantos extremos se conocen (los dos, solo el
// inicio, solo el final, ninguno), porque en cada uno la paridad que hay que exigir cambia.
// EL CHEQUEO DE CONEXIDAD NO ES OPCIONAL: los grados pueden cuadrar perfectamente y aun asi el
// grafo estar partido en dos componentes con aristas, y entonces no hay camino. Se revisa solo
// sobre los vertices que tienen alguna arista; los aislados no estorban.
// El caso de 0 elementos tapados va aparte: ahi basta pegar L y R y ver si la secuencia resultante
// es valida, sin nada de Euler.

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

bool used[MAXN][MAXN];
int usedDegree[MAXN];

bool addPart(const vector<int>& a)
{
    for(int i = 1; i < (int)a.size(); i++)
    {
        int u = a[i - 1];
        int v = a[i];

        if(u == v)
            return false;

        if(used[u][v])
            return false;

        used[u][v] = used[v][u] = true;

        usedDegree[u]++;
        usedDegree[v]++;
    }

    return true;
}

bool connected(int n, const vector<int>& degree)
{
    int s = -1;

    for(int i = 1; i <= n; i++)
    {
        if(degree[i] > 0)
        {
            s = i;
            break;
        }
    }

    if(s == -1)
        return true;

    vector<bool> vis(n + 1);

    queue<int> q;
    q.push(s);
    vis[s] = true;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v = 1; v <= n; v++)
        {
            if(u == v)
                continue;

            if(!used[u][v] && !vis[v])
            {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    for(int i = 1; i <= n; i++)
    {
        if(degree[i] > 0 && !vis[i])
            return false;
    }

    return true;
}

bool canEuler(int n, int start, int finish, int remainingEdges)
{
    if(remainingEdges == 0)
        return false;

    vector<int> degree(n + 1);

    for(int i = 1; i <= n; i++)
        degree[i] = n - 1 - usedDegree[i];

    // Si conocemos un extremo, debe poder salir/entrar
    // por alguna arista restante.
    if(start != -1 && degree[start] == 0)
        return false;

    if(finish != -1 && degree[finish] == 0)
        return false;

    vector<int> odd;

    for(int i = 1; i <= n; i++)
    {
        if(degree[i] & 1)
            odd.push_back(i);
    }

    // Ambos extremos conocidos.
    if(start != -1 && finish != -1)
    {
        if(start == finish)
        {
            // Euler cerrado.
            if(!odd.empty())
                return false;
        }
        else
        {
            // Euler abierto.
            if(odd.size() != 2)
                return false;

            if(!((odd[0] == start && odd[1] == finish) ||
                 (odd[0] == finish && odd[1] == start)))
                return false;
        }
    }

    // Solo conocemos el inicio.
    else if(start != -1)
    {
        if(odd.size() == 0)
        {
            // Puede terminar donde empezo.
        }
        else if(odd.size() == 2)
        {
            if(odd[0] != start && odd[1] != start)
                return false;
        }
        else
        {
            return false;
        }
    }

    // Solo conocemos el final.
    else if(finish != -1)
    {
        if(odd.size() == 0)
        {
            // Puede empezar donde termina.
        }
        else if(odd.size() == 2)
        {
            if(odd[0] != finish && odd[1] != finish)
                return false;
        }
        else
        {
            return false;
        }
    }

    // Ningun extremo conocido.
    else
    {
        if(odd.size() != 0 && odd.size() != 2)
            return false;
    }

    return connected(n, degree);
}


// Caso en el que la torta cubrio 0 elementos.
// Entonces simplemente tenemos L + R.
bool zeroCovered(int n,
                 const vector<int>& L,
                 const vector<int>& R)
{
    int E = n * (n - 1) / 2;

    if((int)L.size() + (int)R.size() != E + 1)
        return false;

    vector<int> a;

    for(int x : L)
        a.push_back(x);

    for(int x : R)
        a.push_back(x);

    bool seen[MAXN][MAXN] = {};

    for(int i = 1; i < (int)a.size(); i++)
    {
        int u = a[i - 1];
        int v = a[i];

        if(u == v)
            return false;

        if(seen[u][v])
            return false;

        seen[u][v] = seen[v][u] = true;
    }

    return true;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int p;
    cin >> p;

    vector<int> L(p);

    for(int &x : L)
        cin >> x;

    int q;
    cin >> q;

    vector<int> R(q);

    for(int &x : R)
        cin >> x;


    // -----------------------------------------
    // Caso: no hubo elementos cubiertos
    // -----------------------------------------

    if(zeroCovered(n, L, R))
    {
        cout << "Y\n";
        return 0;
    }


    // -----------------------------------------
    // Marcar las aristas conocidas
    // -----------------------------------------

    if(!addPart(L))
    {
        cout << "N\n";
        return 0;
    }

    if(!addPart(R))
    {
        cout << "N\n";
        return 0;
    }


    int totalEdges = n * (n - 1) / 2;

    int usedEdges = 0;

    for(int i = 1; i <= n; i++)
        usedEdges += usedDegree[i];

    usedEdges /= 2;

    int remainingEdges = totalEdges - usedEdges;


    // -----------------------------------------
    // Determinar extremos de la parte cubierta
    // -----------------------------------------

    int start = -1;
    int finish = -1;

    if(!L.empty())
        start = L.back();

    if(!R.empty())
        finish = R.front();


    // -----------------------------------------
    // Las aristas restantes pueden formar
    // el camino que falta?
    // -----------------------------------------

    if(canEuler(n, start, finish, remainingEdges))
        cout << "Y\n";
    else
        cout << "N\n";

    return 0;
}
