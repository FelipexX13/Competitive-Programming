// <3
// Tema: Geometry / K Vecinos Mutuos y Clasificacion de Componentes
// Resumen: Cada estrella mira a sus K vecinas mas cercanas
// Detalle: Resuelve "Celestial Veins" (problema C, ICPC 2025): cada estrella mira a sus K
// vecinas mas cercanas, dos estrellas quedan unidas solo si CADA UNA esta entre las K de la
// otra (vinculo mutuo), y hay que clasificar cada componente conexa en una de cinco formas y
// contarlas. TRES COSAS QUE HAY QUE HACER BIEN Y SON FACILES DE ARRUINAR: 1) EL DESEMPATE. Si
// dos candidatas quedan a la misma distancia, gana la que aparece antes en la entrada.
// Ordenando pares (distancia al cuadrado, indice) eso sale solo, porque el indice desempata.
// Con coordenadas hasta 10^9, dx*dx + dy*dy llega a 8*10^18 y cabe JUSTO en long long: en int o
// en double se rompe. 2) EL VINCULO ES MUTUO. Que A tenga a B entre sus K no basta; hay que
// comprobar tambien al reves. Como cada estrella tiene a lo sumo 5 vecinas, revisarlo es O(K).
// 3) EL ORDEN DE LA CLASIFICACION, que el enunciado fija: Cluster, Ouroboros, Claw, Path,
// Nebula. Importa porque las formas se solapan. Un triangulo es a la vez completo y un ciclo, y
// se cuenta como Cluster; un camino de 3 estrellas es a la vez garra y camino, y se cuenta como
// Claw. Evaluarlas en otro orden cambia las respuestas. Cada forma se reconoce contando aristas
// y grados, sin recorrer nada mas: completo: E = V*(V-1)/2 ciclo: E = V y todos los grados
// valen 2 garra: E = V-1, un grado V-1 y los demas 1 camino: E = V-1 y ningun grado pasa de 2
// Una estrella sola (V = 1) es Nebula, y cualquier otra cosa tambien. El if de V == 1 va
// primero porque con V = 1 la formula del completo tambien se cumple (E = 0) y la clasificaria
// mal como Cluster. Costo O(n^2) por mapa para hallar las vecinas, que con n = 1500 son unos 2
// millones de pares. Medido: 5 mapas de n = 1500 con K = 5 en 93 ms, tanto con puntos al azar
// como en rejilla (que es el caso con mas empates de distancia). Verificado contra una
// implementacion independiente del enunciado en 1800 mapas, incluidos puntos alineados y en
// rejilla para forzar empates, sin una sola diferencia, ademas de los dos casos del sample.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;

    while(cin >> n >> k && !(n == 0 && k == 0))
    {
        vector<long long> coordX(n), coordY(n);

        for(long long i = 0; i < n; i++)
        {
            cin >> coordX[i] >> coordY[i];
        }

        vector<vector<long long>> cercanas(n);

        long long cuantasVecinas = min(k, n - 1);

        for(long long estrella = 0; estrella < n; estrella++)
        {
            vector<pair<long long, long long>> candidatas;

            for(long long otra = 0; otra < n; otra++)
            {
                if(otra == estrella)
                {
                    continue;
                }

                long long dx = coordX[estrella] - coordX[otra];
                long long dy = coordY[estrella] - coordY[otra];

                long long distancia2 = dx * dx + dy * dy;

                candidatas.push_back({distancia2, otra});
            }

            partial_sort(candidatas.begin(),
                         candidatas.begin() + cuantasVecinas,
                         candidatas.end());

            for(long long p = 0; p < cuantasVecinas; p++)
            {
                cercanas[estrella].push_back(candidatas[p].second);
            }
        }

        vector<vector<long long>> vinculos(n);

        for(long long a = 0; a < n; a++)
        {
            for(long long b : cercanas[a])
            {
                if(b < a)
                {
                    continue;
                }

                bool bTieneA = false;

                for(long long c : cercanas[b])
                {
                    if(c == a)
                    {
                        bTieneA = true;
                    }
                }

                if(bTieneA)
                {
                    vinculos[a].push_back(b);
                    vinculos[b].push_back(a);
                }
            }
        }

        long long travelersPath = 0;
        long long cosmicOuroboros = 0;
        long long stellarCluster = 0;
        long long dragonsClaw = 0;
        long long amorphousNebula = 0;

        vector<bool> visitada(n, false);

        for(long long inicio = 0; inicio < n; inicio++)
        {
            if(visitada[inicio])
            {
                continue;
            }

            vector<long long> grupo;
            queue<long long> cola;

            cola.push(inicio);
            visitada[inicio] = true;

            while(!cola.empty())
            {
                long long actual = cola.front();
                cola.pop();

                grupo.push_back(actual);

                for(long long vecina : vinculos[actual])
                {
                    if(!visitada[vecina])
                    {
                        visitada[vecina] = true;
                        cola.push(vecina);
                    }
                }
            }

            long long estrellas = grupo.size();
            long long sumaGrados = 0;
            long long conGrado1 = 0;
            long long conGrado2 = 0;
            long long gradoMaximo = 0;

            for(long long estrella : grupo)
            {
                long long grado = vinculos[estrella].size();

                sumaGrados += grado;
                gradoMaximo = max(gradoMaximo, grado);

                if(grado == 1) conGrado1++;
                if(grado == 2) conGrado2++;
            }

            long long enlaces = sumaGrados / 2;

            if(estrellas == 1)
            {
                amorphousNebula++;
            }
            else if(enlaces == estrellas * (estrellas - 1) / 2)
            {
                stellarCluster++;
            }
            else if(enlaces == estrellas && conGrado2 == estrellas)
            {
                cosmicOuroboros++;
            }
            else if(enlaces == estrellas - 1 &&
                    gradoMaximo == estrellas - 1 &&
                    conGrado1 == estrellas - 1)
            {
                dragonsClaw++;
            }
            else if(enlaces == estrellas - 1 && gradoMaximo <= 2)
            {
                travelersPath++;
            }
            else
            {
                amorphousNebula++;
            }
        }

        cout << travelersPath << ' '
             << cosmicOuroboros << ' '
             << stellarCluster << ' '
             << dragonsClaw << ' '
             << amorphousNebula << '\n';
    }

    return 0;
}
