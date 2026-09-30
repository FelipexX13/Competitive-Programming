// <3
// Tema: CSES / Hashing Doble con Segment Tree
// Consultas de "el tramo [l,r] es palindromo?" sobre una cadena que ademas CAMBIA: hay
// actualizaciones de un caracter mezcladas con las preguntas.
// LA IDEA: un segment tree donde cada nodo guarda DOS hashes del tramo, el de izquierda a derecha
// (fw) y el de derecha a izquierda (bw). El tramo es palindromo si los dos coinciden.
// EL MERGE ES LO UNICO DELICADO, y es asimetrico a proposito:
//     fw de (a + b) = a.fw * BASE^len(b) + b.fw     se lee a y despues b
//     bw de (a + b) = b.bw * BASE^len(a) + a.bw     al reves se lee b y despues a
// Por eso hace falta guardar el LARGO en cada nodo: sin el no se sabe por cuanto desplazar. Las
// potencias de BASE van precalculadas en pw[], porque calcularlas en cada merge seria un log de mas.
// El nodo neutro es el de largo 0, y el merge lo trata aparte para que las consultas que no cubren
// nada no ensucien el hash.
// POR QUE HASHING Y NO MANACHER: Manacher es O(n) pero para una cadena FIJA. Aqui hay
// actualizaciones, y rehacerlo en cada cambio seria O(n) por consulta. El hash con segment tree da
// O(log n) tanto para actualizar como para preguntar.
// EL RIESGO DEL HASHING ES LA COLISION. Con un solo modulo de 10^9 y muchas consultas, la
// probabilidad ya no es despreciable (paradoja del cumpleanos: con 10^5 consultas sobre 10^9
// valores). En un juez adversario conviene hashing DOBLE, con dos pares (BASE, MOD) distintos, y
// dar palindromo solo si coinciden los dos.
// La BASE debe ser mayor que el alfabeto y los caracteres se mapean a 1..26, no a 0..25: si la 'a'
// valiera 0, las cadenas "a", "aa" y "aaa" tendrian el mismo hash.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;
const ll BASE = 911382323;

struct Node {
    ll fw = 0; // izquierda -> derecha
    ll bw = 0; // derecha -> izquierda
    int len = 0;
};

vector<ll> pw;
vector<Node> st;

Node mergeNode(Node a, Node b) {
    if (a.len == 0) return b;
    if (b.len == 0) return a;

    Node res;

    res.len = a.len + b.len;

    // a + b
    res.fw = (a.fw * pw[b.len] + b.fw) % MOD;

    // b + a
    res.bw = (b.bw * pw[a.len] + a.bw) % MOD;

    return res;
}

void build(int p, int l, int r, string &s) {
    if (l == r) {
        st[p].fw = s[l] - 'a' + 1;
        st[p].bw = s[l] - 'a' + 1;
        st[p].len = 1;
        return;
    }

    int mid = (l + r) / 2;

    build(p * 2, l, mid, s);
    build(p * 2 + 1, mid + 1, r, s);

    st[p] = mergeNode(st[p * 2], st[p * 2 + 1]);
}

void update(int p, int l, int r, int pos, char c) {
    if (l == r) {
        st[p].fw = c - 'a' + 1;
        st[p].bw = c - 'a' + 1;
        return;
    }

    int mid = (l + r) / 2;

    if (pos <= mid)
        update(p * 2, l, mid, pos, c);
    else
        update(p * 2 + 1, mid + 1, r, pos, c);

    st[p] = mergeNode(st[p * 2], st[p * 2 + 1]);
}

Node query(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql)
        return Node();

    if (ql <= l && r <= qr)
        return st[p];

    int mid = (l + r) / 2;

    Node left = query(p * 2, l, mid, ql, qr);
    Node right = query(p * 2 + 1, mid + 1, r, ql, qr);

    return mergeNode(left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    // Pasamos a 0-index
    // s[0] corresponde a posicion 1.

    pw.resize(n + 1);
    pw[0] = 1;

    for (int i = 1; i <= n; i++)
        pw[i] = pw[i - 1] * BASE % MOD;

    st.resize(4 * n + 5);

    build(1, 0, n - 1, s);

    while (m--) {

        int type;
        cin >> type;

        if (type == 1) {

            int k;
            char x;

            cin >> k >> x;

            --k;

            update(1, 0, n - 1, k, x);

        } else {

            int a, b;
            cin >> a >> b;

            --a;
            --b;

            Node ans = query(1, 0, n - 1, a, b);

            if (ans.fw == ans.bw)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}
