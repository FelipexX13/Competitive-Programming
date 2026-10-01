// <3
// Tema: CSES / Reconstruir la Cadena desde el Suffix Array
// O: (n log n) por el segment tree de maximos
// Uso: greedy sobre sa; seg guarda la letra usada indexada por rank[p+1]
// Dado un suffix array, construir la cadena mas chica que lo produce, o -1 si no existe.
// Se recorre el suffix array en orden y se asigna a cada sufijo la letra mas pequena posible. Dos
// sufijos consecutivos del arreglo pueden compartir letra SOLO si el orden ya queda decidido por
// lo que viene despues, o sea si rank[p+1] del anterior es menor que rank[p+1] del actual.
// El segment tree de maximos responde justo eso: entre los sufijos ya colocados cuyo siguiente
// sufijo va DESPUES del nuestro, cual es la letra mas grande. Si esa letra es la actual, hay
// conflicto y toca subir a la siguiente.
// El sufijo de largo 1 (p == n-1) va aparte porque no tiene siguiente y siempre obliga a subir.
// Si se pasa de 26 letras no hay solucion y se responde -1.

#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
    int n;
    vector<int> tree;

    SegmentTree(int n)
    {
        this->n = n;
        tree.assign(4 * n, -1);
    }

    void update(int node, int l, int r, int pos, int val)
    {
        if(l == r)
        {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if(pos <= mid)
            update(node * 2, l, mid, pos, val);
        else
            update(node * 2 + 1, mid + 1, r, pos, val);

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int pos, int val)
    {
        update(1, 0, n - 1, pos, val);
    }

    int query(int node, int l, int r, int ql, int qr)
    {
        if(qr < l || r < ql)
            return -1;

        if(ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        return max(
            query(node * 2, l, mid, ql, qr),
            query(node * 2 + 1, mid + 1, r, ql, qr)
        );
    }

    int query(int l, int r)
    {
        if(l > r)
            return -1;

        return query(1, 0, n - 1, l, r);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> sa(n);

    for(int i = 0; i < n; i++)
    {
        cin >> sa[i];
        sa[i]--; // pasamos a 0-index
    }

    // rank[x] = posicion de x dentro del suffix array
    vector<int> rank(n);

    for(int i = 0; i < n; i++)
        rank[sa[i]] = i;

    string s(n, 'a');

    SegmentTree seg(n);

    int c = 0;

    for(int i = 0; i < n; i++)
    {
        int p = sa[i];

        // Si estamos colocando el sufijo de longitud 1,
        // tiene que ser estrictamente mayor que el anterior.
        if(i > 0 && p == n - 1)
            c++;

        else if(p < n - 1)
        {
            // Miramos los sufijos anteriores cuyo siguiente
            // sufijo aparece despues de p+1.
            int r = rank[p + 1];

            int mx = seg.query(r + 1, n - 1);

            // Si alguno tiene nuestra misma letra,
            // necesitamos aumentar la letra.
            if(mx == c)
                c++;
        }

        if(c >= 26)
        {
            cout << -1 << '\n';
            return 0;
        }

        s[p] = char('a' + c);

        // Guardamos la letra de s[p] asociada a rank[p+1]
        if(p < n - 1)
            seg.update(rank[p + 1], c);
    }

    cout << s << '\n';

    return 0;
}
