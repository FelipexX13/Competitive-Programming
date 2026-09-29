// <3
// Tema: Implementation / Lectura de Entrada
// Catalogo de patrones para leer entradas "raras": hasta EOF, con centinela, con T casos,
// bloques separados por lineas en blanco, grids de caracteres, tokens con separadores
// mixtos y enteros gigantes como string. La regla practica: si el problema NO da un T
// inicial, piensa en EOF o centinela; si la entrada trae blancos o bloques, usa getline
// mas istringstream en vez de cin >>; y si alternas cin >> con getline, consume siempre
// el salto de linea pendiente con un getline extra o el parseo se descuadra.
// Cada patron esta en su propia funcion para poder copiar solo el que se necesita.

#include <bits/stdc++.h>

using namespace std;

// 1) Hasta EOF: no hay T y el archivo termina sin aviso
void leerHastaEOF()
{
    int a, b;
    while (cin >> a >> b)
    {
        // procesar (a, b)
    }
}

// 2) Hasta centinela (clasico "0 0" para terminar)
void leerHastaCentinela()
{
    int a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0) break;
        // procesar (a, b)
    }
}

// 3) T al inicio y luego T casos
void leerTCasos()
{
    int T;
    if (cin >> T)
    {
        while (T--)
        {
            int n, m;
            cin >> n >> m;
            // procesar
        }
    }
}

// 4) Cabecera por caso: cada caso empieza con "n m" y trae m lineas
void leerCabeceraPorCaso()
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<pair<int,int>> edges;
        edges.reserve(m);
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }
        // procesar caso
    }
}

// 5) Bloques separados por lineas en blanco, sin saber cuantos hay
void leerBloques()
{
    string line;
    while (true)
    {
        // saltar lineas vacias entre bloques
        while (getline(cin, line) && line.empty()) {}
        if (!cin) break;

        vector<string> bloque;
        do
        {
            if (!line.empty()) bloque.push_back(line);
        } while (getline(cin, line) && !line.empty());

        // parsear cada linea del bloque con istringstream
        for (auto &L : bloque)
        {
            istringstream iss(L);
            int x;
            while (iss >> x)
            {
                // procesar x
            }
        }
    }
}

// 6) Mezclar cin >> con getline: hay que consumir el '\n' colgante
void leerLineaConEspacios()
{
    int n;
    cin >> n;
    string line;
    getline(cin, line);   // consume el salto de linea pendiente
    getline(cin, line);   // esta si es la linea util (puede traer espacios)
}

// 7) Leer N numeros aunque vengan repartidos en varias lineas
void leerNNumeros()
{
    int n;
    cin >> n;
    vector<long long> a;
    a.reserve(n);
    while ((int)a.size() < n)
    {
        long long x;
        if (!(cin >> x)) break;
        a.push_back(x);
    }
}

// 8) Grid de caracteres R x C (getline es mas robusto que >> por fila)
void leerGrid()
{
    int R, C;
    cin >> R >> C;
    string dummy;
    getline(cin, dummy);   // consume el '\n'
    vector<string> g(R);
    for (int i = 0; i < R; i++)
    {
        getline(cin, g[i]);
    }
}

// 9) Leer linea por linea y tokenizar, saltando vacias y comentarios
void leerYTokenizar()
{
    string line;
    while (getline(cin, line))
    {
        if (line.empty() || line[0] == '#') continue;
        istringstream iss(line);
        int x;
        while (iss >> x)
        {
            // procesar x
        }
    }
}

// 10) Tokens con separadores mixtos (comas, tabs, espacios)
void leerSeparadoresMixtos()
{
    string line;
    getline(cin, line);
    for (char &c : line)
    {
        if (c == ',' || c == '\t') c = ' ';
    }
    istringstream iss(line);
    vector<string> tok;
    for (string t; iss >> t; ) tok.push_back(t);
}

// 11) Enteros gigantes: leerlos como string para no desbordar
void leerBigInt()
{
    string P;
    while (cin >> P)
    {
        // procesar P digito por digito (ver modString)
    }
}

// 12) Consumir TODO el archivo como un solo string (parser propio)
void leerTodo()
{
    string all((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
}

// 13) Normalizar fin de linea de Windows (CRLF) y espacios finales
void rstrip(string &s)
{
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ' || s.back() == '\t'))
    {
        s.pop_back();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
