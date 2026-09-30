// <3
// Tema: Math / Recurrencia (Fibonacci)
// Resuelve "Fractions are better when continued" (Maratona SBC de Programacao 2024, Problem F):
// dado un entero N, hay que hallar el numerador (en forma irreducible) de la fraccion continua
// p_N definida recursivamente como p_0 = 1, p_1 = 1/(1+1), p_2 = 1/(1+1/(1+1)), y asi
// sucesivamente, agregando un nivel mas de fraccion en cada paso.
// Al expandir la recurrencia, los numeradores de p_N resultan ser exactamente los numeros de
// Fibonacci (1, 1, 2, 3, 5, 8, ...). El codigo aprovecha esto y calcula el resultado con un
// simple bucle iterativo que va sumando e intercambiando num y dem en cada paso (equivalente a
// num, dem = dem, num+dem), evitando aritmetica de fracciones o recursion explicita.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n ; cin >> n;
    
    if(n==1)
    {
        cout<<1<<endl;
    }
    else if(n == 2)
    {
        cout<<2<<endl;
    }
    else
    {
        long long num = 1;
        long long dem = 2;
        long long temp = 0;
        long long temp2 = 0;
        while(n>1)
        {
            temp2 = num + dem;
            num = temp2;
            
            temp = num;
            num = dem;
            dem = temp;
            
            n--;
        }
        
        cout<<num<<endl;
    }

    return 0;
}