// <3
// Tema: Implementation / Date Parsing
// Calcula la diferencia de tiempo (hacia adelante) entre dos momentos dados como dia de la semana + hora.
// Usa un arreglo de 14 dias (2 semanas) para manejar el wrap-around cuando el segundo momento
// cae en la siguiente semana.

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    string d1, d2;
    string h1, h2;
    cin >> d1 >> h1 >> d2 >> h2;

    string dias[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun",
                     "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

    // Parsear horas HH:MM
    int hh1, mm1, hh2, mm2;
    sscanf(h1.c_str(), "%d:%d", &hh1, &mm1);
    sscanf(h2.c_str(), "%d:%d", &hh2, &mm2);

    int t1 = hh1 * 60 + mm1;
    int t2 = hh2 * 60 + mm2;

    // Encontrar el indice de d1 en la primera semana
    int idx1 = 0;
    for (int i = 0; i < 7; i++) {
        if (dias[i] == d1) { idx1 = i; break; }
    }

    // Buscar d2 desde idx1 en adelante (en el arreglo de 14 dias)
    // Si es el mismo dia y la hora de fin es menor o igual, avanzar a la siguiente semana
    int idx2 = -1;
    for (int i = idx1; i < 14; i++) {
        if (dias[i] == d2) {
            if (i == idx1 && t2 <= t1) continue;
            idx2 = i;
            break;
        }
    }

    int64 diff = (int64)(idx2 - idx1) * 24 * 60 + (t2 - t1);

    int64 days  = diff / (24 * 60);
    int64 hours = (diff % (24 * 60)) / 60;
    int64 mins  = diff % 60;

    vector<string> parts;
    if (days)  parts.push_back(to_string(days)  + (days  == 1 ? " day"    : " days"));
    if (hours) parts.push_back(to_string(hours) + (hours == 1 ? " hour"   : " hours"));
    if (mins)  parts.push_back(to_string(mins)  + (mins  == 1 ? " minute" : " minutes"));

    if (parts.size() == 3)
        cout << parts[0] << ", " << parts[1] << ", " << parts[2] << "\n";
    else if (parts.size() == 2)
        cout << parts[0] << " and " << parts[1] << "\n";
    else
        cout << parts[0] << "\n";

    return 0;
}