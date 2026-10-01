// <3
// Tema: CSES / Barrido Lineal de Rachas
// Resumen: Una pasada llevando el largo de la racha actual y el maximo visto
// Detalle: Una pasada llevando el largo de la racha actual y el maximo visto. Al cambiar el
// caracter se cierra la racha y se reinicia en 1. EL BUG CLASICO: la ultima racha nunca se
// cierra dentro del for, porque no hay un cambio de caracter que la corte. Por eso hay que
// comparar contra el maximo OTRA VEZ despues del ciclo, y es justamente lo que se olvida. Cada
// vez que se escribe un barrido de rachas hay que preguntarse quien cierra la ultima. CUANDO
// USAR: cualquier "cuantos consecutivos iguales", "el bloque mas largo de", en una pasada O(n)
// y sin memoria.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s; cin >> s;
    long long maxi = 0;
    char ant = '-';
    long long temp = 0;
    for(int i = 0 ; i  < (int) s.size() ; i ++)
    {
        if(s[i]== ant)
        {
            temp++;
        }
        else
        {
            if(temp>maxi)
            {
                maxi = temp;
            }
            temp =1;
            ant = s[i];
        }

    }
    if(temp>maxi)
            {
                maxi = temp;
            }
    cout  << maxi << endl;

     return 0;
}
