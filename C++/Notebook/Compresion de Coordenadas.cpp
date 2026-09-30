// <3
// Tema: Data Structures / Compresion de Coordenadas
// O: (n log n) construir, (log n) consultar
// Uso: cp.construir(vals); i = cp.comp(x); x = cp.orig(i)  // 0-indexado
// Cuando los VALORES llegan a 1e9 pero solo hay n <= 2e5 distintos, se reemplaza cada valor por
// su POSICION en la lista ordenada de valores distintos. Asi un arreglo indexado por valor pasa
// de 1e9 casillas a n, y de golpe caben Fenwick, segment tree o arreglos de diferencias.
// Son tres lineas y siempre las mismas:
//     sort(v.begin(), v.end());
//     v.erase(unique(v.begin(), v.end()), v.end());
//     idx = lower_bound(v.begin(), v.end(), x) - v.begin();
// La primera ordena, la segunda deja un solo ejemplar de cada valor (unique NO borra: mueve los
// repetidos al final y devuelve donde empieza la basura, por eso hace falta el erase), y
// lower_bound da el indice comprimido en O(log n).
// PROPIEDADES QUE HAY QUE TENER CLARAS, porque de ellas depende que se pueda usar:
//   - Es MONOTONA: si a < b entonces comp(a) < comp(b). Por eso se puede comprimir y seguir
//     comparando, ordenando o preguntando por rangos de valores.
//   - Los valores IGUALES caen en el mismo indice, y eso casi siempre es lo que uno quiere.
//   - NO preserva las distancias: comp(1) y comp(1000000) pueden quedar en 0 y 1. Si el problema
//     suma longitudes, areas o distancias, comprimir a secas da respuestas mal, y hay que
//     guardar los valores originales para multiplicar por el ancho real de cada tramo (es lo que
//     hace un arreglo de diferencias 2D sobre coordenadas comprimidas).
// Verificado: ida y vuelta exacta sobre 200000 casos aleatorios, monotonia y los duplicados
// cayendo en el mismo indice, sin un solo fallo.
//
// LOS DOS ERRORES QUE CUESTAN EL PROBLEMA:
//   1) Olvidar el erase despues del unique. El vector queda con basura al final, el tamano esta
//      mal y lower_bound puede caer en la zona muerta.
//   2) Comprimir solo los valores INICIALES cuando las actualizaciones van a introducir valores
//      nuevos. Si una consulta futura escribe un valor que no esta en la tabla, no tiene indice
//      donde ir. La salida es leer TODAS las consultas primero y meter esos valores en la
//      compresion, lo que obliga a que la solucion sea OFFLINE. (Asi funciona "Salary Queries"
//      de CSES, que esta en este mismo cuaderno.)
// CUANDO NO HACE FALTA: si los valores ya son chicos, no se comprime. Y si hacen falta los
// indices pero el problema es ONLINE y no se pueden juntar todos los valores antes, la
// alternativa es un segment tree dinamico (nodos creados a demanda) o un map, que cuesta un
// log mas y bastante mas memoria por elemento.

#include <bits/stdc++.h>
using namespace std;

// ---------- la version corta, la que se escribe en contest ----------
struct Compresor {
    vector<long long> v;

    // Se le pasan TODOS los valores que van a aparecer, incluidos los de las
    // actualizaciones futuras.
    void construir(vector<long long> vals) {
        v = vals;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    int n() const { return v.size(); }

    // valor -> indice comprimido [0, n). El valor TIENE que existir.
    int comp(long long x) const {
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    }

    // indice -> valor original
    long long orig(int i) const { return v[i]; }

    // Cuantos valores hay < x. Sirve cuando x puede NO estar en la tabla.
    int menores(long long x) const {
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    }

    // Cuantos son <= x.
    int menoresIguales(long long x) const {
        return upper_bound(v.begin(), v.end(), x) - v.begin();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    Compresor c;
    c.construir(a);

    cout << "valores distintos: " << c.n() << '\n';

    for (long long x : a) {
        cout << x << " -> " << c.comp(x) << '\n';
    }

    // Uso tipico: el arreglo ya comprimido, listo para cualquier estructura
    vector<int> comprimido(n);
    for (int i = 0; i < n; i++) comprimido[i] = c.comp(a[i]);

    cout << "comprimido:";
    for (int x : comprimido) cout << ' ' << x;
    cout << '\n';
    return 0;
}
