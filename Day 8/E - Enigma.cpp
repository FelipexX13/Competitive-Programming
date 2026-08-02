// <3
// Tema: Strings / Brute Force Matching
// Resuelve "Enigma": dado un mensaje cifrado y un crib (palabra que se asume esta en el
// mensaje original), hay que contar en cuantas posiciones puede empezar el crib dentro del
// mensaje cifrado, sabiendo que la maquina Enigma nunca reemplaza una letra por si misma (o
// sea, en una posicion valida ninguna letra del crib puede coincidir con la letra del mensaje
// en esa misma posicion).
// Para cada posicion i de arranque, compara letra a letra el crib contra el substring del
// mensaje de ese largo (variable "tempi"), y descarta la posicion apenas encuentra una letra
// igual (bandera "ok"); cuenta en "god" las posiciones donde ninguna letra coincidio, en
// fuerza bruta O(n*m).

#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s1,s2;
    cin >> s1 >> s2;
    int god=0;
    
    for(int i = 0 ; i <= s1.size()-s2.size();i++)
    {
        string tempi = s1.substr(i,s2.size());
        bool ok = false;
        for(int j = 0 ; j < s2.size() && ok == false;j++)
        {
            if(tempi[j]==s2[j])
            {
                ok = true;
            }
        }
        if(ok == false)
        {
            god++;
        }
    }
    
    cout << god << endl;

    return 0;
}