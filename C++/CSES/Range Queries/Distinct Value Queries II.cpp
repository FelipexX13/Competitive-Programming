// <3
// Tema: CSES / Segment Tree sobre Ocurrencia Anterior
// Saber si en [x,y] hay valores repetidos, y la idea es preciosa: para cada posicion i se calcula
// prev[i], la ultima posicion antes de i con el mismo valor (o 0 si no hay). Entonces el rango
// [x,y] tiene un repetido si y solo si existe algun i en [x,y] con prev[i] >= x.
// Eso se convierte en una consulta de MAXIMO de prev[] sobre el rango, o como esta aqui, de minimo
// sobre el arreglo complementario. De cualquier forma, el punto es que una pregunta que parecia
// necesitar contar valores distintos se reduce a un maximo de rango, que un segment tree responde
// en O(log n) y ONLINE, sin necesidad de Mo.
// COMPARAR CON "Distinct Values Queries": ese cuenta CUANTOS distintos hay y por eso necesita Mo o
// un BIT offline. Este solo pregunta SI hay repetidos, que es mucho mas debil, y esa debilidad es
// justo lo que permite la reduccion a un maximo. Vale la pena mirar los dos juntos: la leccion es
// que antes de sacar la artilleria conviene ver si el problema pide menos de lo que parece.
// EL PATRON DE prev[i]: aparece en casi todos los problemas de "distintos en un rango". Se calcula
// con un map de ultima posicion vista en una pasada.
// OJO: usa structured bindings (auto [a, b]), que piden C++17. En CSES compila, pero con
// un g++ viejo hay que volver a .first y .second.

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int n) : n(n), tree(4 * n, INF) {}

    void update(int node, int l, int r, int pos, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, val);
        else
            update(node * 2 + 1, mid + 1, r, pos, val);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return INF;

        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        return min(
            query(node * 2, l, mid, ql, qr),
            query(node * 2 + 1, mid + 1, r, ql, qr)
        );
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

struct Operation {
    int type, x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<int> values;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        values.push_back(a[i]);
    }

    vector<Operation> ops(q);

    for (auto &[type, x, y] : ops) {
        cin >> type >> x >> y;

        if (type == 1)
            values.push_back(y);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    auto get = [&](int x) {
        return lower_bound(values.begin(), values.end(), x)
             - values.begin();
    };

    for (int i = 1; i <= n; i++)
        a[i] = get(a[i]);

    int m = values.size();

    vector<set<int>> pos(m);

    for (int i = 1; i <= n; i++)
        pos[a[i]].insert(i);

    vector<int> nxt(n + 1, INF);

    for (int x = 0; x < m; x++) {
        auto &s = pos[x];

        for (auto it = s.begin(); it != s.end(); ++it) {
            auto nx = next(it);

            if (nx != s.end())
                nxt[*it] = *nx;
        }
    }

    SegmentTree st(n);

    for (int i = 1; i <= n; i++)
        st.update(i, nxt[i]);

    for (auto [type, x, y] : ops) {

        if (type == 2) {

            if (st.query(x, y) <= y)
                cout << "NO\n";
            else
                cout << "YES\n";

        } else {

            int k = x;
            int newValue = get(y);
            int oldValue = a[k];

            if (oldValue == newValue)
                continue;

            // Quitar k del valor anterior
            {
                auto &s = pos[oldValue];
                auto it = s.find(k);

                int prevPos = -1;
                int nextPos = INF;

                if (it != s.begin()) {
                    auto p = prev(it);
                    prevPos = *p;
                }

                auto nx = next(it);

                if (nx != s.end())
                    nextPos = *nx;

                if (prevPos != -1)
                    st.update(prevPos, nextPos);

                st.update(k, INF);

                s.erase(it);
            }

            // Agregar k al nuevo valor
            {
                auto &s = pos[newValue];

                auto it = s.lower_bound(k);

                int nextPos = INF;

                if (it != s.end())
                    nextPos = *it;

                if (it != s.begin()) {
                    auto p = prev(it);
                    st.update(*p, k);
                }

                st.update(k, nextPos);

                s.insert(k);
            }

            a[k] = newValue;
        }
    }
}
