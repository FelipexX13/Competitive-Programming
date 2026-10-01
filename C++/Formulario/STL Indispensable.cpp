// <3
// Tema: Formulario / STL Indispensable
// Resumen: Las funciones de la libreria estandar que la gente reimplementa a mano por no saber
// que existen
// Detalle: Las funciones de la libreria estandar que la gente reimplementa a mano por no saber
// que existen, y las que se usan mal por un detalle: next_permutation solo recorre las n! si el
// vector arranca ordenado (verificado: desde {1,2,3} da 6 permutaciones, desde {3,1,2} solo 2),
// y substr toma (inicio, CANTIDAD) y no (inicio, fin). Tener esta lista a mano ahorra escribir
// veinte lineas que ya vienen hechas y probadas.

// =============== STL INDISPENSABLE ===============
//
// Ordenar y buscar  (el vector debe estar ordenado para los bound)
//     sort(all(v))                  O(n log n)
//     stable_sort(all(v))           conserva el orden de los iguales
//     sort(all(v), greater<int>())  descendente
//     lower_bound(all(v), x)   primer elemento >= x
//     upper_bound(all(v), x)   primer elemento >  x
//         cuantos x hay = upper_bound - lower_bound
//         posicion = lower_bound(all(v), x) - v.begin()
//     binary_search(all(v), x) devuelve solo true/false
//     nth_element(v.begin(), v.begin()+k, v.end())
//         deja el k-esimo en su sitio en O(n) promedio, sin ordenar todo
//     partial_sort(v.begin(), v.begin()+k, v.end())  solo los k primeros
//
// Permutaciones
//     next_permutation(all(v))  siguiente en orden lexicografico
//         devuelve false cuando llega a la ultima y reinicia
//         ORDENA PRIMERO si quieres recorrer las n! (verificado)
//     prev_permutation(all(v))
//
// Lo que no hay que reimplementar
//     __gcd(a,b)              en C++17 tambien gcd(a,b) y lcm(a,b)
//     iota(all(v), 0)         llena con 0,1,2,3,...
//     accumulate(all(v), 0LL) suma (usa 0LL para no desbordar)
//     max_element / min_element  devuelven ITERADOR: resta v.begin()
//     count(all(v), x)   find(all(v), x)   reverse(all(v))
//     rotate(v.begin(), v.begin()+k, v.end())   rota a la izquierda
//     fill(all(v), x)    v.assign(n, x)    swap(a, b)
//     minmax_element(all(v))  devuelve los dos de una
//     is_sorted(all(v))   next(it)   prev(it)
//
// Conversiones
//     to_string(x)    stoi(s)   stoll(s)   stod(s)
//     s.substr(i, LARGO)   <- cantidad, NO posicion final
//     s.find(t)  devuelve string::npos si no aparece
//     getline(cin, s)  lee la linea entera con espacios
//     stringstream ss(linea); while (ss >> token) ...   partir por espacio
//
// Estructuras y cuando usarlas
//     vector<int> v(n, 0)          vector<vector<int>> g(n)
//     set / multiset   ordenado, O(log n), tiene .lower_bound propio
//     unordered_set    O(1) promedio, sin orden
//     map / unordered_map   igual pero clave -> valor
//     deque            push_front y push_back en O(1)
//     priority_queue   max-heap; greater<> para convertirlo en min-heap
//     bitset<N>        operaciones de 64 bits por vez, 8x menos memoria
//     array<int,N>     tamano fijo, sin costo de heap
//
// Detalles que sirven
//     v.reserve(n) evita realocar si sabes el tamano de antemano
//     emplace_back construye en el sitio, evita una copia
//     structured bindings: for (auto &[k, val] : mapa)   (C++17)
//     lambda: [](int a, int b){ return a > b; }
//     capturar por referencia para comparadores con datos externos:
//         sort(all(idx), [&](int i, int j){ return v[i] < v[j]; });
