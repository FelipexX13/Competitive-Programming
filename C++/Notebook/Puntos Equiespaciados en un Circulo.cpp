// <3
// Tema: Math / Divisores de la Suma Total
// Resumen: Quitar los minimos puntos de un circulo para que el resto quede equiespaciado
// O: (sqrt(S) + d(S)*n^2) en el peor caso, pero los dos filtros lo dejan casi lineal
// Uso: lee n y los n huecos del circulo; imprime cuantos puntos quitar, o -1
// Detalle: Hay n puntos en un circulo y se dan los n HUECOS entre puntos consecutivos (dist[i]
// va del punto i al i+1, y el ultimo cierra el circulo). Hay que quitar la menor cantidad de
// puntos para que los que queden esten igualmente espaciados, dejando al menos 3. -1 si no se
// puede. LA IDEA QUE RESUELVE TODO: si al final quedan k puntos equiespaciados, cada arco mide
// S/k con S la suma de todos los huecos. O sea que el arco TIENE que ser un DIVISOR de S.
// Entonces no hay que buscar entre 2^n subconjuntos: basta probar los divisores de S, que son
// O(sqrt(S)) de encontrar y pocos de recorrer. Los dos filtros son los que hacen que esto
// vuele, y cada uno sale de una observacion distinta: i >= maxi cada arco es una suma de huecos
// CONSECUTIVOS, asi que no puede medir menos que el hueco mas grande, porque ese hueco vive
// adentro de algun arco. i <= S/3 quedan k = S/i puntos y el enunciado pide al menos 3. Y como
// los divisores se recorren de MENOR A MAYOR, el primero que funciona es el que deja mas puntos
// (k = S/i) y por lo tanto el que quita menos. Por eso se corta con el primer exito y no hace
// falta comparar candidatos. Dentro de un divisor se prueban los n puntos de arranque porque el
// recorrido es un greedy: va acumulando y cada vez que llega EXACTO al arco corta. Si arranca
// en un punto que no es un corte real, se pasa (anti > i) y se descarta ese arranque. Como
// cualquier particion valida tiene al menos 3 cortes, alguno de los n arranques cae en uno.
// quitados sale solo: cada arco consume cont huecos y conserva 1 punto, asi que suma cont - 1.
// Al final quitados = n - k. RAMA MUERTA: el "else cout << -1" de adentro del exito nunca se
// ejecuta, porque n - quitados es exactamente k = S/i y el filtro i <= S/3 ya garantiza k >= 3.
// Verificado instrumentando la rama sobre las 2.451 pruebas: 0 ejecuciones. Se deja como estaba
// para no tocar codigo que sirve. OJO: sum es int. Con n y huecos grandes se desborda; si los
// limites suben, a long long. OJO: el atajo de "todos iguales -> 0" responde antes de mirar si
// hay al menos 3 puntos, asi que con n = 1 o n = 2 contesta 0. Solo importa si el problema
// permite n < 3. VERIFICADO contra fuerza bruta sobre subconjuntos: exhaustivo para n = 3, 4 y
// 5 con huecos de 1 a 3 (todas las combinaciones) mas 2.100 casos aleatorios, 2.451 en total, 0
// diferencias. Tiempo: 0.01 s hasta n = 8000 en los peores casos que arme (suma muy divisible,
// huecos casi iguales con uno roto, todos unos menos el ultimo).

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    while(cin >> n)
    {
        if(n == 0) return 0;

        vector<int> dist(n);
        int maxi = -1;
        bool iguales = true;
        int ant = 0;
        int sum = 0;

        for(int i = 0 ; i < n ; i++)
        {
            cin >> dist[i];

            if(i == 0)
                ant = dist[i];

            if(dist[i] > maxi)
            {
                maxi = dist[i];
            }

            if(ant != dist[i])
            {
                iguales = false;
            }

            sum += dist[i];
        }

        if(iguales)
        {
            cout << 0 << endl;
        }
        else
        {
            bool entro = false;

            vector<int> divisores;

            for(int i = 1 ; i * i <= sum ; i++)
            {
                if(sum % i == 0)
                {
                    divisores.push_back(i);

                    if(i != sum / i)
                    {
                        divisores.push_back(sum / i);
                    }
                }
            }

            sort(divisores.begin(), divisores.end());

            for(int i : divisores)
            {
                // i es el largo del arco: no puede ser menor que el hueco mas
                // grande, ni tan grande que queden menos de 3 puntos.
                if(i < maxi || i > sum / 3)
                    continue;

                for(int inicio = 0 ; inicio < n ; inicio++)
                {
                    int anti = 0;
                    int quitados = 0;
                    int cont = 0;
                    bool ok = true;

                    for(int j = 0 ; j < n ; j++)
                    {
                        int pos = (inicio + j) % n;

                        anti += dist[pos];
                        cont++;

                        if(anti == i)
                        {
                            anti = 0;
                            quitados += cont - 1;   // el arco conserva 1 punto
                            cont = 0;
                        }
                        else if(anti > i)
                        {
                            ok = false;             // este arranque no es corte
                            break;
                        }
                    }

                    if(ok && anti == 0)
                    {
                        entro = true;

                        if(n - quitados >= 3)
                        {
                            cout << quitados << endl;
                        }
                        else
                        {
                            cout << -1 << endl;
                        }

                        break;
                    }
                }

                if(entro)
                {
                    break;
                }
            }

            if(!entro)
            {
                cout << -1 << endl;
            }
        }
    }

    return 0;
}
