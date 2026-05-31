// <3
// Tema: Math / Modular Arithmetic
// Calcula el número mínimo de saltos de tamaño 3*b necesarios para cubrir la distancia vertical abs(a-c),
// o determina si no es posible porque la distancia no es múltiplo de b.

#include <bits/stdc++.h>

using namespace std;

int main() {
    while(true){
        int a,b,c;
        cin >> a >> b >> c;
        if(a==0 && b ==0 && c ==0)
        {
            return 0;
        }
        
        int god = abs(a-c);
        if(god%b!=0)
        {
            cout << "No accounting tablet" << "\n";
        }
        else
        {
            if((god/b) % 3 ==0)
            {
                cout << (god/b)/3<< "\n";
            }
            else
            {
                
                cout << ((god/b)/3)+1<< "\n";
            }
        }
        
        
    }
    
    
    
    
    return 0;
}