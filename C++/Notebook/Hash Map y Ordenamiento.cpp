// <3
// Tema: Data Structures / Hash Map y Ordenamiento
// Diferencia clave: unordered_map es tabla hash, O(1) promedio pero SIN orden; map es arbol
// rojo-negro, O(log n) pero siempre ordenado por clave. Ninguno de los dos se puede ordenar
// por el valor (second) directamente, asi que el patron obligado es volcarlo a un
// vector<pair<...>> y ordenar ese vector con un comparador lambda.
// Aqui estan los comparadores mas usados: por clave ascendente/descendente, por valor
// ascendente/descendente, y por valor con desempate por clave (el que piden casi siempre en
// rankings y conteos de frecuencia). Tambien el truco de recorrer con structured bindings
// para modificar valores in-place y el de invertir el mapa.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // contar frecuencias
    unordered_map<string, int> mp = {{"c", 3}, {"a", 1}, {"b", 2}};

    // para ordenar hay que volcar a un vector de pares
    vector<pair<string,int>> v(mp.begin(), mp.end());

    // por clave ascendente
    sort(v.begin(), v.end(), [](auto &l, auto &r){ return l.first < r.first; });

    // por valor descendente
    sort(v.begin(), v.end(), [](auto &l, auto &r){ return l.second > r.second; });

    // por valor descendente con desempate por clave ascendente
    sort(v.begin(), v.end(), [](auto &l, auto &r){
        if (l.second == r.second) return l.first < r.first;
        return l.second > r.second;
    });

    for (auto &p : v)
    {
        cout << p.first << " => " << p.second << "\n";
    }

    // modificar todos los valores in-place (el & es obligatorio, si no se copia)
    // con C++17 tambien vale: for (auto &[key, val] : mp) val += 3;
    for (auto &p : mp)
    {
        p.second += 3;
    }

    // buscar sin crear la clave por accidente (operator[] la crearia)
    if (mp.count("b"))
    {
        cout << "b vale " << mp["b"] << "\n";
    }

    // invertir el mapa (valor -> clave) para ordenar por valor
    vector<pair<int,string>> inv;
    for (auto &p : mp) inv.push_back({p.second, p.first});
    sort(inv.begin(), inv.end());

    // map ya viene ordenado por clave, no necesita sort
    map<int, string> m;
    m[3] = "tres";
    m[1] = "uno";
    m[2] = "dos";
    for (auto &p : m)
    {
        cout << p.first << " -> " << p.second << "\n";
    }

    return 0;
}
