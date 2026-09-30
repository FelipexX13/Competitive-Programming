// <3
// Tema: Data Structures / Segment Tree sobre Coordenadas Comprimidas
// Resuelve "Emergency Rations" (problema E, Regionals 2025). Las consultas traen posiciones que
// llegan hasta valores enormes, asi que lo primero es COMPRIMIR: se juntan todos los |x| que
// aparecen, se ordenan, se quitan repetidos, y el segment tree trabaja sobre esos indices.
// EL DETALLE QUE SE OLVIDA: hay que incluir el 0 en la lista de coordenadas. Es un tamano valido
// (caja vacia) y si no esta, las consultas que lo necesitan caen fuera del arreglo o se contestan
// con el siguiente valor, que es otra respuesta.
// Se comprime por valor ABSOLUTO porque el problema es simetrico: lo que importa es la distancia al
// origen, no el lado. Eso ademas reduce a la mitad las coordenadas distintas.
// PATRON GENERAL: cada vez que los indices son enormes pero la cantidad de valores distintos es
// chica, se comprime. La plantilla esta en "Compresion de Coordenadas" de este cuaderno; lo unico
// que cambia de problema a problema es QUE valores hay que meter en la lista, y ahi es donde se
// falla: hay que incluir no solo los datos, sino tambien los extremos que las consultas puedan
// necesitar (aqui, el 0).

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define forn(i,n) for(int i = 0; i < n; i++)

struct SegmentTree
{
    int n;
    vector<ll> tree, lazy;

    SegmentTree(vector<ll>& a)
    {
        n = a.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);

        build(1, 0, n - 1, a);
    }

    void build(int node, int l, int r, vector<ll>& a)
    {
        if(l == r)
        {
            tree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void push(int node)
    {
        if(lazy[node] == 0)
            return;

        ll x = lazy[node];

        tree[node * 2] += x;
        tree[node * 2 + 1] += x;

        lazy[node * 2] += x;
        lazy[node * 2 + 1] += x;

        lazy[node] = 0;
    }

    void update(int node, int l, int r, int ql, int qr, ll val)
    {
        if(ql > r || qr < l)
            return;

        if(ql <= l && r <= qr)
        {
            tree[node] += val;
            lazy[node] += val;
            return;
        }

        push(node);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int l, int r, ll val)
    {
        if(l > r)
            return;

        update(1, 0, n - 1, l, r, val);
    }

    ll query()
    {
        return tree[1];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    vector<ll> x(Q);
    vector<ll> coords;

    forn(i, Q)
    {
        cin >> x[i];

        coords.push_back(abs(x[i]));
    }

    // Coordenadas de los posibles tamanos de las cajas
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    /*
        Incluimos el tamano 0.

        t = 0 significa:
        no hacer ninguna operacion de "quitar una racion
        de cada caja", sino vaciar cada caja individualmente.
    */
    vector<ll> values;

    // 0 siempre es una posibilidad
    values.push_back(0);

    for(ll v : coords)
        values.push_back(v);

    int M = values.size();

    /*
        freq[i] = cantidad de cajas cuyo tamano es values[i]
    */
    vector<ll> freq(M, 0);

    /*
        Al principio no hay cajas.

        Para cada posible t:
            valor[t] = t + cantidad de cajas con tamano > t

        Como inicialmente no hay cajas:
            valor[t] = t
    */
    vector<ll> initial(M);

    for(int i = 0; i < M; i++)
        initial[i] = values[i];

    SegmentTree st(initial);

    /*
        Posicion de cada valor en el vector comprimido.
    */
    unordered_map<ll,int> pos;

    for(int i = 0; i < M; i++)
        pos[values[i]] = i;

    /*
        Agregar una caja de tamano x.

        Para todo t < x:
            cantidad de cajas > t aumenta en 1

        Por lo tanto hacemos:
            [0, pos[x)-1] += 1
    */
    auto addBox = [&](ll x)
    {
        int p = pos[x];

        st.update(0, p - 1, 1);

        freq[p]++;
    };

    /*
        Quitar una caja de tamano x.

        Para todo t < x:
            cantidad de cajas > t disminuye en 1
    */
    auto removeBox = [&](ll x)
    {
        int p = pos[x];

        st.update(0, p - 1, -1);

        freq[p]--;
    };

    forn(i, Q)
    {
        if(x[i] > 0)
        {
            addBox(x[i]);
        }
        else
        {
            removeBox(-x[i]);
        }

        cout << st.query() << ' ';
    }

    cout << '\n';

    return 0;
}
