// <3
// Tema: Simulation / Ad Hoc
// Resuelve "Toilet Seat" (Kattis): dada una secuencia de preferencias 'U' (arriba) o 'D'
// (abajo) de personas que usan el bano una tras otra, donde el primer caracter es la posicion
// inicial del asiento, pide calcular cuantos ajustes de asiento se necesitan bajo tres
// politicas: (1) siempre dejarlo arriba, (2) siempre dejarlo abajo, (3) dejarlo como a uno le
// gustaria encontrarlo. Recorre la cadena una sola vez calculando en paralelo ans1 y ans2
// (contando cuantas veces el asiento debe moverse segun cada politica fija) y ans3 (contando
// los cambios de preferencia entre personas consecutivas, que es el costo bajo la politica de
// dejarlo "como te gustaria encontrarlo").

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    ll ans1=0,ans2=0,ans3=0;
    
    //1
    if(s[0]== 'U' && s[1] == 'U') ans1+=0;
    else if(s[0]== 'U' && s[1] == 'D') ans1+=2;
    else if(s[0]== 'D' && s[1] == 'D') ans1+=1;
    else ans1+=1;
    for(int i = 2; i < s.size(); i++)
    {
        if(s[i] == 'D') ans1+=2;
    }
    
    //2
    if(s[0]== 'U' && s[1] == 'U') ans2+=1;
    else if(s[0]== 'U' && s[1] == 'D') ans2+=1;
    else if(s[0]== 'D' && s[1] == 'D') ans2+=0;
    else ans2+=2;
    for(int i = 2; i < s.size(); i++)
    {
        if(s[i] == 'U') ans2+=2;
    }
    
    //3 
    char act = s[0];
    for(int i = 1 ; i < s.size(); i++)
    {
        if(s[i] != act)
        {
            ans3++;
            act = s[i];
        }
    }
    
    cout << ans1 << endl;
    cout << ans2 << endl;
    cout << ans3 << endl;
    

    return 0;
}