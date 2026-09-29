// <3
// Tema: CSES / Fenwick con Descenso Binario (k-esimo)
// Fenwick de unos y ceros (1 = la posicion todavia esta) donde lo interesante es kth(): encontrar
// la k-esima posicion viva sin busqueda binaria por fuera.
// EL DESCENSO SOBRE EL BIT: se arranca en la potencia de 2 mas grande y se va bajando, probando en
// cada paso si el bloque que empieza en pos+p acumula menos de k. Si acumula menos, se avanza y se
// le resta ese acumulado a k. Como los bloques del Fenwick son exactamente potencias de 2, ese
// recorrido es un descenso por el arbol implicito y sale en O(log n) de una, contra O(log^2 n) de
// hacer busqueda binaria llamando a sum() en cada paso.
// CUANDO USAR: "el k-esimo elemento que queda", "el k-esimo mas chico", con inserciones y
// borrados. Es el mismo patron que el descenso del segment tree (ver "Hotel Queries"): en vez de
// buscar por fuera, se baja por la estructura aprovechando lo que ya guarda cada nodo.
// OJO con el 1 << 18: tiene que ser una potencia de 2 mayor o igual a n. Con n mas grande hay que
// subirlo, y ese es el error silencioso de esta plantilla.

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, int x) {
        for (; i <= n; i += i & -i)
            bit[i] += x;
    }

    int sum(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    int kth(int k) {
        int pos = 0;

        for (int p = 1 << 18; p; p >>= 1) {
            int next = pos + p;

            if (next <= n && bit[next] < k) {
                pos = next;
                k -= bit[next];
            }
        }

        return pos + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    Fenwick fw(n);

    for (int i = 1; i <= n; i++)
        fw.add(i, 1);

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;

        int pos = fw.kth(k);

        cout << a[pos] << ' ';

        fw.add(pos, -1);
    }

    cout << '\n';
}
