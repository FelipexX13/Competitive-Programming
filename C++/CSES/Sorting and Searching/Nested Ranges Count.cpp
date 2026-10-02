// <3
// Tema: CSES / Contar Rangos Anidados con Fenwick
// Resumen: Lo mismo que Nested Ranges Check, pero CUANTOS contiene y cuantos lo contienen
// O: (n log n), Fenwick sobre los finales comprimidos
// Uso: mismo orden que la version Check, pero contando con fw.query en vez de un maximo
// Detalle: La version Check solo pregunta si hay alguno, y por eso le basta un maximo. Aqui hay
// que CONTAR, y eso ya es una consulta de rango: cuantos de los ya vistos tienen fin menor o
// igual al mio. Esa es la consulta de prefijo de un Fenwick indexado por el fin comprimido. Se
// hacen las dos pasadas, una en cada sentido, reiniciando el Fenwick en medio. El mismo
// desempate de la version Check (fin decreciente con inicios iguales) sigue siendo necesario.

#include <bits/stdc++.h>
using namespace std;

struct Fenwick
{
    int n;
    vector<int> bit;

    Fenwick(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void add(int x, int v)
    {
        for(; x <= n; x += x & -x)
            bit[x] += v;
    }

    int query(int x)
    {
        int ans = 0;

        for(; x > 0; x -= x & -x)
            ans += bit[x];

        return ans;
    }
};

struct Range
{
    int l, r, id;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Range> a(n);
    vector<int> vals;

    for(int i = 0; i < n; i++)
    {
        cin >> a[i].l >> a[i].r;
        a[i].id = i;

        vals.push_back(a[i].r);
    }

    // Compresion de coordenadas
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    for(auto &x : a)
    {
        x.r = lower_bound(vals.begin(), vals.end(), x.r)
              - vals.begin() + 1;
    }

    // l creciente, r decreciente
    sort(a.begin(), a.end(), [](Range A, Range B)
    {
        if(A.l != B.l)
            return A.l < B.l;

        return A.r > B.r;
    });

    vector<int> contains(n);
    vector<int> contained(n);

    // --------------------------------
    // Cuantos rangos contiene este?
    // --------------------------------

    Fenwick fw(n);

    for(int i = n - 1; i >= 0; i--)
    {
        // Posteriores con r <= r_actual
        contains[a[i].id] = fw.query(a[i].r);

        fw.add(a[i].r, 1);
    }

    // --------------------------------
    // Cuantos rangos contienen este?
    // --------------------------------

    fw = Fenwick(n);

    for(int i = 0; i < n; i++)
    {
        // Anteriores con r >= r_actual
        int anteriores = i;

        int menores = fw.query(a[i].r - 1);

        contained[a[i].id] = anteriores - menores;

        fw.add(a[i].r, 1);
    }

    // Orden original
    for(int x : contains)
        cout << x << ' ';

    cout << '\n';

    for(int x : contained)
        cout << x << ' ';

    cout << '\n';

    return 0;
}
