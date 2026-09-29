// <3
// Tema: Greedy / Puente y Linterna (version con indices)
// La otra solucion del problema B de ICPC 2024 ("The Bridge at Night"), el clasico del puente con
// una sola linterna. Misma estrategia que "B - The Bridge At Night" de esta carpeta, escrita con un
// contador de cuantos quedan en vez de ir recortando el arreglo.
// Con los tiempos ordenados y mientras queden mas de 3, se cruzan los DOS MAS LENTOS con la mejor
// de dos jugadas, donde t[0] y t[1] son los dos mas rapidos:
//     escolta      = 2*t[0] + t[quedan-2] + t[quedan-1]   el mas rapido acompana a cada lento
//     parejaLenta  = t[0] + 2*t[1] + t[quedan-1]          los dos lentos cruzan juntos
// La segunda gana cuando los lentos son MUY lentos, porque paga el mas lento una sola vez para los
// dos; la primera cuando la diferencia es chica. Cada ronda saca a dos del problema.
// Casos base: con 3 quedan t[0]+t[1]+t[2]; con 2, el mas lento; con 1, el unico.
// Verificado con el sample (10, 20, 8) y con el acertijo famoso de 1, 2, 5 y 10, que da 17 (la
// estrategia ingenua de que el rapido acompane a todos daria 19).
// La otra version esta verificada ademas contra un Dijkstra exacto sobre todos los estados en 1500
// casos; esta comparte la formula, asi que vale lo mismo.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    long long n;

    while(cin >> n && n != 0)
    {
        vector<long long> tiempo(n);

        for(long long i = 0; i < n; i++)
        {
            cin >> tiempo[i];
        }

        sort(tiempo.begin(), tiempo.end());

        long long total = 0;
        long long quedan = n;

        while(quedan > 3)
        {
            long long escolta = 2 * tiempo[0] + tiempo[quedan - 2] + tiempo[quedan - 1];
            long long parejaLenta = tiempo[0] + 2 * tiempo[1] + tiempo[quedan - 1];

            total += min(escolta, parejaLenta);
            quedan -= 2;
        }

        if(quedan == 3)
        {
            total += tiempo[0] + tiempo[1] + tiempo[2];
        }
        else if(quedan == 2)
        {
            total += tiempo[1];
        }
        else
        {
            total += tiempo[0];
        }

        cout << total << '\n';
    }

    return 0;
}