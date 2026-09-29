// <3
// Tema: CSES / Fenwick con Compresion Offline
// Fenwick sobre VALORES en vez de posiciones, para contar cuantos salarios caen en un rango. Como
// los valores llegan a 10^9 hay que comprimirlos, y aqui esta el detalle que hace el problema:
// las consultas se leen TODAS primero, porque los valores que van a aparecer en las actualizaciones
// futuras tambien tienen que entrar en la compresion. Si uno comprime solo con los valores
// iniciales, la primera actualizacion a un valor nuevo no tiene indice donde ir.
// Eso obliga a que el problema sea OFFLINE: leer todo, comprimir, y despues procesar en orden.
// El Fenwick guarda la CANTIDAD de empleados con cada valor comprimido, asi que cambiar un salario
// es add(viejo, -1) y add(nuevo, +1), y contar en un rango es la resta de dos prefijos.
// CUANDO USAR: contar elementos en un rango de VALORES con actualizaciones. Es el patron de
// "cuantos hay menores que x" con cambios. La alternativa online es un segment tree dinamico o
// sobre los valores sin comprimir, que gasta mas memoria pero no obliga a leer todo antes.
// OJO: usa structured bindings (auto [a, b]), que piden C++17. En CSES compila, pero con
// un g++ viejo hay que volver a .first y .second.

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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> salary(n + 1);
    vector<tuple<char, int, int>> queries;
    vector<int> values;

    for (int i = 1; i <= n; i++) {
        cin >> salary[i];
        values.push_back(salary[i]);
    }

    for (int i = 0; i < q; i++) {
        char type;
        int a, b;
        cin >> type >> a >> b;

        queries.push_back({type, a, b});

        if (type == '!')
            values.push_back(b);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    Fenwick fw(values.size());

    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(values.begin(), values.end(), salary[i])
                  - values.begin() + 1;

        fw.add(pos, 1);
    }

    for (auto [type, a, b] : queries) {

        if (type == '!') {
            int oldPos = lower_bound(values.begin(), values.end(), salary[a])
                         - values.begin() + 1;

            int newPos = lower_bound(values.begin(), values.end(), b)
                         - values.begin() + 1;

            fw.add(oldPos, -1);
            fw.add(newPos, 1);

            salary[a] = b;
        }

        else {
            int right = upper_bound(values.begin(), values.end(), b)
                        - values.begin();

            int left = lower_bound(values.begin(), values.end(), a)
                       - values.begin();

            cout << fw.sum(right) - fw.sum(left) << '\n';
        }
    }
}
