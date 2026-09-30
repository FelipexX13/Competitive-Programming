// <3
// Tema: Math / Prefix Sums
// Resuelve "Triangles" (Maratona de Programacao da SBC 2013, problem F): dados N puntos sobre
// un circulo, descritos por las longitudes de arco entre puntos consecutivos, cuenta cuantos
// triangulos equilateros distintos se pueden formar usando esos puntos como vertices.
// Convierte los arcos en posiciones absolutas sobre el circulo con una suma prefija (tot),
// marcando cada posicion ocupada en el arreglo booleano nums[]. Un triangulo equilatero solo
// puede existir si el perimetro total es multiplo de 3 (tri = tot/3); para cada posicion
// marcada i, verifica si i+tri e i+2*tri tambien estan marcadas, y de ser asi cuenta un
// triangulo y desmarca las tres posiciones para no reutilizarlas.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n; cin >> n;
    long long tot = 0;
    long long god = 0;
    vector<long long> nums1;
    for(long long i = 0 ; i < n ; i ++)
    {
        long long a; cin >>a;
        tot+= a;
        nums1.push_back(tot);
    }
    vector<long long> nums(10000000,0);
    for(long long i = 0 ; i < nums1.size() ; i++)
    {
        nums[nums1[i]]=1;
    }
    
    if(tot%3!=0)
    {
        cout<< 0 <<endl;
    }
    else
    {
        long long tri = tot/3;
        for(long long i = 0 ; i < (10000000) ; i++)
        {
            
            if(nums[i]==1 && nums[i]==nums[i+tri]&&nums[i]==nums[i+tri+tri]&&i<10000000&&i+tri<10000000&&i+tri+tri<10000000)
            {
               
                god++;
                nums[i]=0;
                nums[i+tri] = 0;
                nums[i+tri+tri] = 0;
            }
        }
        
        cout << god << endl;
    }
    return 0;
}