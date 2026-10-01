// <3
// Tema: Data Structures / Ordered Set (PBDS)
// Resumen: set indexado de GNU: find_by_order(k) y order_of_key(x), las dos en O(log n)
// O: (log n) insertar, borrar, find_by_order y order_of_key
// Uso: s.find_by_order(k) -> k-esimo (0-indexado); s.order_of_key(x) -> menores
// Detalle: Estructura basada en politicas de GNU: funciona como un set<> normal pero ademas
// esta indexada internamente, lo que da dos operaciones que un set no tiene, ambas en O(log n):
// find_by_order(k) devuelve un iterador al k-esimo elemento (0-indexado, o end() si k >=
// size()), y order_of_key(x) devuelve cuantos elementos hay estrictamente menores que x. Sirve
// para contar inversiones, rankings dinamicos o "cuantos menores que X llevo hasta ahora" sin
// montar un Fenwick con compresion de coordenadas. Para permitir duplicados usa less_equal<int>
// en vez de less<int> (ojo: con eso erase por valor deja de funcionar y hay que borrar via
// find_by_order). AVISO: es una extension de GNU, solo compila con g++ (no con MSVC ni clang
// sin libstdc++). La instalacion local de MinGW 6.3 de este equipo tiene los headers de pb_ds
// incompletos y da error al compilar, pero en Codeforces y en la mayoria de jueces funciona sin
// problema.

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ordered_set s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);

    cout << *s.find_by_order(0) << "\n";   // 10, el primero
    cout << *s.find_by_order(2) << "\n";   // 30, el tercero

    cout << s.order_of_key(30) << "\n";    // 2, hay dos menores que 30
    cout << s.order_of_key(35) << "\n";    // 3, no hace falta que 35 exista

    if (s.find_by_order(99) == s.end())
    {
        cout << "fuera de rango\n";
    }

    return 0;
}
