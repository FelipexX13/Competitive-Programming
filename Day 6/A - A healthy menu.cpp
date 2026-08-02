// <3
// Tema: Math / Greedy
// Resuelve "A healthy menu" (Maratona SBC de Programacao 2025, Problem A): un colegio tiene M
// clases y N frutas, y para cada fruta i y clase j se conoce G[i][j], la cantidad de estudiantes
// de esa clase a quienes les gusta esa fruta (un estudiante puede gustarle varias frutas). Hay
// que hallar el menor numero total de estudiantes posible en todo el colegio, consistente con
// esos conteos. Para cada clase, la cota minima de estudiantes es el mayor G[i][j] entre todas
// las frutas i (y siempre es alcanzable dejando que un mismo estudiante le guste mas de una
// fruta). El codigo recorre cada clase i, calcula "maxxx" como el maximo de clases[j][i] sobre
// todas las frutas j, y acumula esos maximos en "maxi", que es la respuesta final.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n; cin >> n; 
    int m; cin >> m;
    
    vector<vector<int>> clases;
    long long maxi = 0;
    
    for(int i = 0 ; i < n; i++)
    {
        vector<int> pp;
        for(int j = 0 ; j < m; j++)
        {
            int a; cin>>a;
            pp.push_back(a);
        }
        clases.push_back(pp);
    }
    for(int i = 0 ; i < m; i++)
    {
        long long maxxx = 0;
        for(int j = 0 ; j < n; j++)
        {
            if(clases[j][i] >= maxxx)
            {
                maxxx = clases[j][i];
            }
        }
        maxi += maxxx;
    }
    
    cout << maxi<< endl;

    return 0;
}