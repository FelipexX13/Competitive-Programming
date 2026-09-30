// <3
// Tema: Math / Probabilidad (Paradoja del cumpleanos)
// Resuelve "Mount Rushmore and Birthdays" (Contest 05 [Avanzados], problema F): dado N, el
// numero de dias que tiene un anio, hay que hallar la minima cantidad de personas necesarias en
// un cuarto para que la probabilidad de que dos compartan cumpleanos sea mayor a 50%.
// Calcula iterativamente, persona por persona, la probabilidad "prob" de que todos los
// cumpleanos sigan siendo distintos (multiplicando (n-personas)/n en cada paso, la
// generalizacion de la formula clasica de la paradoja del cumpleanos), y se detiene apenas
// 1 - prob supera 0.5, devolviendo esa cantidad de personas.

#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double n; cin >>n;
    double prob = 1;
    double persons = 2;
    prob *= (n-1)/n;
    
    if(n==1)
    {
        cout << 2 << endl;
        return 0;
    }
    

        while(true)
        {
            prob *= (n-persons)/n;
            
            persons++;
            if(1-prob>0.5)
            {
                cout<< persons << endl;
                return 0;
            }
            
        }
        
        
        
    

    return 0;
}