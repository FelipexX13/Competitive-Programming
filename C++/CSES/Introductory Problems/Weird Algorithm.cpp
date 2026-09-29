// <3
// Tema: CSES / Simulacion Directa
// Simular el proceso de Collatz tal cual lo dice el enunciado, sin mas.
// LO UNICO QUE PUEDE FALLAR: el tipo. Con n hasta 10^6 los valores INTERMEDIOS de la secuencia se
// van muy por encima de 10^9, asi que con int se desborda y el programa se cuelga o imprime
// basura. long long y listo.
// La leccion general: antes de simular, estimar hasta donde crece la variable, no hasta donde
// crece la ENTRADA. Son dos cosas distintas y esta es la trampa mas comun de los problemas
// faciles.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n; cin >> n;
    cout << n << " ";
    while(n!=1)
    {
        if(n%2==0)
        {
            n=n/2;
        }
        else
        {
            n=(n*3)+1;
        }
        cout << n << " ";
    }

    return 0;
}
