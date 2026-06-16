// <3
// Tema: String / Simulation
// Procesa una cadena aplicando operaciones sobre un string acumulador: '*' borra el ultimo
// caracter, '#' duplica el contenido actual, '%' lo invierte, y cualquier otro caracter se
// agrega al final. Devuelve el string resultante.

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string processStr(string s) {
        string god = "";
        for(char a : s)
        {
            if(a == '*')
            {
                if(god.size()>0)
                {
                    god.erase(god.size()-1);
                }
            }
            else if(a == '#')
            {
                god += god;
            }
            else if(a == '%')
            {
                reverse(god.begin(),god.end());
            }
            else
            {
                god += a;
            }
        }
        return god;
    }
};