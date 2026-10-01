// <3
// Tema: CSES / DSU (Union-Find)
// Resumen: DSU con compresion de camino y union por tamano, que juntas dan casi O(1) amortizado
// por operacion
// Detalle: DSU con compresion de camino y union por tamano, que juntas dan casi O(1) amortizado
// por operacion. Se unen todas las aristas dadas y despues se recorre 1..n preguntando quien es
// su propio padre: esos son los representantes, uno por componente. Con c componentes hacen
// falta c-1 aristas nuevas, y basta encadenar los representantes en fila. CUANDO USAR DSU:
// cuando la pregunta es "estos dos estan conectados" o "cuantas componentes hay" y las aristas
// solo se AGREGAN, nunca se quitan. Si hay que quitar aristas, DSU no sirve tal cual y toca
// procesar al reves en el tiempo, o irse a link-cut trees. Para solo contar componentes un BFS
// o DFS tambien alcanza; DSU gana cuando las consultas se intercalan con las uniones, o cuando
// es la base de Kruskal.

#include <bits/stdc++.h>
using namespace std;

vector<long long> padre;
vector<long long> tamano;

long long encontrar(long long x)
{
    if(padre[x] == x)
    {
        return x;
    }

    return padre[x] = encontrar(padre[x]);
}

void unir(long long a, long long b)
{
    a = encontrar(a);
    b = encontrar(b);

    if(a == b)
    {
        return;
    }

    if(tamano[a] < tamano[b])
    {
        swap(a, b);
    }

    padre[b] = a;
    tamano[a] += tamano[b];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    padre.resize(n + 1);
    tamano.resize(n + 1, 1);

    for(long long i = 1; i <= n; i++)
    {
        padre[i] = i;
    }

    long long a, b;

    for(long long i = 0; i < m; i++)
    {
        cin >> a >> b;
        unir(a, b);
    }

    vector<long long> familias;

    for(long long i = 1; i <= n; i++)
    {
        if(encontrar(i) == i)
        {
            familias.push_back(i);
        }
    }

    cout << (familias.size()-1) << '\n';

    for(long long i = 0; i + 1 < familias.size(); i++)
    {
        cout << familias[i] << ' ' << familias[i + 1] << '\n';
    }

    return 0;
}