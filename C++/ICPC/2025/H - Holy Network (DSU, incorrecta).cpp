// <3
// Tema: Graph / DSU (enfoque INCORRECTO para este problema)
// Intento del problema H de ICPC 2025 ("Holy Network") con DSU: une dos numeros cuando comparten un
// factor, y responde el tamano de la componente mas grande.
// ESTA VERSION ESTA MAL Y SE GUARDA JUSTAMENTE POR ESO. El enunciado pide que CADA PAR del grupo
// comparta un factor, no que el grupo este conectado. El contraejemplo minimo es {6, 10, 35}: 6-10
// comparten el 2 y 10-35 comparten el 5, asi que la componente mide 3, pero 6 y 35 son coprimos y
// el grupo valido mide 2. Medido: falla 872 de 1500 casos aleatorios contra fuerza bruta, aunque
// pasa los tres casos del sample, donde ambas cosas coinciden.
// La leccion que vale guardar: "todos conectados" y "todos compatibles entre si" son cosas
// distintas. Lo primero es una componente conexa (facil, DSU o BFS); lo segundo es un CLIQUE
// (NP-dificil en general). Si un enunciado dice "cada par", "todos con todos" o "mutuamente", casi
// seguro es clique y DSU no sirve.
// La version correcta esta en "H - Holy Network" (Bron-Kerbosch con pivote) y en
// "H - Holy Network (clique iterativo)", ambas en esta carpeta.
// Lo unico reutilizable de aqui es como se arman las aristas: en vez de comparar todos los pares
// con gcd, se factoriza cada numero probando divisores hasta la raiz y se une cada numero con sus
// factores, usando un map para los primos que aparecen. Eso da O(n * sqrt(V)) en vez de O(n^2 log V),
// que ayuda cuando n es grande, aunque aqui n <= 50 y no hace falta.

#include <iostream>
#include <vector>
#include <map>

using namespace std;

long long buscar(map<long long, long long>& padre, long long x)
{
    if(padre[x] == x)
    {
        return x;
    }

    return padre[x] = buscar(padre, padre[x]);
}

void unir(map<long long, long long>& padre, map<long long, long long>& tam, long long a, long long b)
{
    a = buscar(padre, a);
    b = buscar(padre, b);

    if(a == b)
    {
        return;
    }

    if(tam[a] < tam[b])
    {
        swap(a, b);
    }

    padre[b] = a;
    tam[a] += tam[b];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;

    while(cin >> n && n != 0)
    {
        vector<long long> numeros(n);

        map<long long, bool> esInput;
        map<long long, long long> padre;
        map<long long, long long> tam;

        for(long long i = 0; i < n; i++)
        {
            cin >> numeros[i];

            esInput[numeros[i]] = true;
            padre[numeros[i]] = numeros[i];
            tam[numeros[i]] = 1;
        }

        for(long long x : numeros)
        {
            for(long long i = 2; i * i <= x; i++)
            {
                if(x % i == 0)
                {
                    long long z = x / i;

                    if(!padre.count(i))
                    {
                        padre[i] = i;
                        tam[i] = 1;
                    }

                    if(!padre.count(z))
                    {
                        padre[z] = z;
                        tam[z] = 1;
                    }

                    unir(padre, tam, x, i);
                    unir(padre, tam, x, z);
                }
            }
        }

        map<long long, long long> familias;
        long long maxValor = 0;

        for(long long x : numeros)
        {
            long long raiz = buscar(padre, x);

            familias[raiz]++;

            maxValor = max(maxValor, familias[raiz]);
        }

        cout << maxValor << '\n';
    }

    return 0;
}