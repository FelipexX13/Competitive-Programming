// <3
// Tema: CSES / Greedy de Maximo Prefijo
// Resumen: Greedy: recorriendo de izquierda a derecha
// Detalle: Greedy: recorriendo de izquierda a derecha, cada elemento que sea menor que el
// maximo visto tiene que subir hasta ese maximo, y el costo se acumula. Nunca conviene subir un
// elemento por encima de lo necesario ni bajar ninguno, porque las operaciones solo suman. POR
// QUE ES OPTIMO: el maximo de prefijo es una cota inferior, cada posicion tiene que llegar por
// lo menos ahi, y el greedy paga exactamente esa cota. No hay decision que tomar, y eso es lo
// que distingue a un greedy trivialmente correcto de uno que hay que demostrar. long long en el
// acumulador: n posiciones con diferencias de hasta 10^9 se pasan de int.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n ; cin >> n;
    long long ant=0;
    long long god =0;
    for(int i = 0 ; i < n ; i++)
    {
        long long a; cin >> a;
        if(i!=0)
        {
            if(a < ant)
            {
                god+= ant-a;

                ant = ant;
                continue;
            }
        }
        ant = a;
    }
    cout << god << endl;

    return 0;
}
