// <3
// Tema: String / Partition and Permutation
// Divide una cadena en 3 partes, las reorganiza y verifica si forma otra cadena objetivo.
// Si es posible, imprime ambas descomposiciones ordenadas.

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
 
    string s1, s2;
    cin >> s1 >> s2;
 
    // Probar todos los cortes posibles:
    // A = [0,i)
    // B = [i,j)
    // C = [j,n)
 
    for(int i = 1; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            string A = s1.substr(0, i);
            string B = s1.substr(i, j-i);
            string C = s1.substr(j);
 
            vector<string> p = {A,B,C};
 
            sort(p.begin(), p.end());
 
            do
            {
                string formed = p[0] + p[1] + p[2];
 
                if(formed == s2)
                {
                    cout << "YES\n";
 
                    // Descomposición original del pasaporte
                    cout << A << " " << B << " " << C << "\n";
 
                    // Descomposición de la visa
                    cout << p[0] << " " << p[1] << " " << p[2] << "\n";
 
                    return 0;
                }
 
            } while(next_permutation(p.begin(), p.end()));
        }
    }
 
    cout << "NO\n";
 
    return 0;
}