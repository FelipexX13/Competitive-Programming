// <3
// Tema: Binary Search / Busqueda sobre la Respuesta con Fracciones Exactas
// Resumen: Elegir trabajadores con tarifas y ventanas de disponibilidad para limpiar S calles
// al menor costo
// Detalle: Resuelve "Clean Streets" (problema C, Regionals 2025): elegir trabajadores con
// tarifas y ventanas de disponibilidad para limpiar S calles al menor costo. Se busca sobre la
// RAZON r = costo por hora. Para un r fijo, un trabajador sirve si su intervalo [L/H, U/H]
// contiene a r, y entre los que sirven se toman los mas baratos hasta juntar S calles: un
// segment tree responde "cual es el costo minimo de tomar exactamente need calles entre los H
// mas chicos" con un descenso por el arbol. LOS CANDIDATOS SON FINITOS: la respuesta optima
// siempre cae en algun extremo de intervalo, o sea en algun L_i/H_i. No hace falta busqueda
// binaria real sobre reales: se prueban esos O(N) candidatos en orden, agregando trabajadores
// cuyo intervalo ya empezo y sacando los que ya terminaron, como un barrido. LO QUE HAY QUE
// COPIAR DE AQUI ES fracLess Y fracLE: comparar a/b contra c/d se hace con la multiplicacion
// cruzada a*d < c*b, en ENTEROS. Usar double para ordenar fracciones es la forma mas comun de
// fallar estos problemas, porque dos fracciones distintas pueden dar el mismo double y el orden
// queda al azar. Ojo con el signo de los denominadores: la multiplicacion cruzada solo conserva
// la desigualdad si ambos son positivos. El costo final se reporta como fraccion (num * horas /
// den) en vez de convertirlo a decimal antes de tiempo, para no arrastrar error. OJO: usa
// structured bindings (auto [a, b]), que piden C++17. En el juez compila, pero con un g++ viejo
// hay que volver a .first y .second.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Cleaner {
    ll H, L, U;
};

struct SegTree {
    int n;
    vector<ll> cnt;
    vector<ll> cost;

    SegTree(int n) : n(n) {
        cnt.assign(4 * n + 5, 0);
        cost.assign(4 * n + 5, 0);
    }

    void update(int node, int l, int r, int pos, ll dc, ll dcost) {
        if (l == r) {
            cnt[node] += dc;
            cost[node] += dcost;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, dc, dcost);
        else
            update(node * 2 + 1, mid + 1, r, pos, dc, dcost);

        cnt[node] = cnt[node * 2] + cnt[node * 2 + 1];
        cost[node] = cost[node * 2] + cost[node * 2 + 1];
    }

    void update(int pos, ll dc) {
        update(1, 1, n, pos, dc, dc * pos);
    }

    // Minimo costo para tomar exactamente need calles
    // usando los H mas pequenos.
    ll query(int node, int l, int r, ll need) {
        if (l == r) {
            return need * l;
        }

        int mid = (l + r) / 2;

        if (cnt[node * 2] >= need) {
            return query(node * 2, l, mid, need);
        }

        ll leftCost = cost[node * 2];
        ll leftCnt = cnt[node * 2];

        return leftCost +
               query(node * 2 + 1, mid + 1, r, need - leftCnt);
    }

    ll query(ll need) {
        if (cnt[1] < need)
            return -1;

        return query(1, 1, n, need);
    }
};

// a/b < c/d
bool fracLess(ll a, ll b, ll c, ll d) {
    return a * d < c * b;
}

// a/b <= c/d
bool fracLE(ll a, ll b, ll c, ll d) {
    return a * d <= c * b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll S, K;

    cin >> N >> S >> K;

    vector<Cleaner> a(N);

    for (auto &[H, L, U] : a) {
        cin >> H >> L >> U;
    }

    // Orden por L/H
    vector<int> byL(N);
    iota(byL.begin(), byL.end(), 0);

    sort(byL.begin(), byL.end(), [&](int i, int j) {
        return fracLess(
            a[i].L, a[i].H,
            a[j].L, a[j].H
        );
    });

    // Orden por U/H
    vector<int> byU(N);
    iota(byU.begin(), byU.end(), 0);

    sort(byU.begin(), byU.end(), [&](int i, int j) {
        return fracLess(
            a[i].U, a[i].H,
            a[j].U, a[j].H
        );
    });

    // Candidatos r = L_i / H_i
    vector<int> candidates = byL;

    SegTree st(100000);

    int pL = 0;
    int pU = 0;

    bool found = false;

    ll bestNum = 0;
    ll bestDen = 1;

    for (int id : candidates) {

        ll num = a[id].L;
        ll den = a[id].H;

        // Agregar todos los trabajadores cuyo
        // intervalo ya comenzo.
        while (pL < N) {
            int j = byL[pL];

            if (!fracLE(
                    a[j].L, a[j].H,
                    num, den
                ))
                break;

            ll capacity = K / a[j].H;

            st.update(a[j].H, capacity);

            pL++;
        }

        // Eliminar trabajadores cuyo intervalo
        // ya termino antes de r.
        while (pU < N) {
            int j = byU[pU];

            if (!fracLess(
                    a[j].U, a[j].H,
                    num, den
                ))
                break;

            ll capacity = K / a[j].H;

            st.update(a[j].H, -capacity);

            pU++;
        }

        // Podemos limpiar S calles?
        ll totalHours = st.query(S);

        if (totalHours == -1)
            continue;

        // costo = r * totalHours
        //
        // r = num / den
        //
        // costo = num * totalHours / den

        ll curNum = num * totalHours;
        ll curDen = den;

        ll g = gcd(curNum, curDen);

        curNum /= g;
        curDen /= g;

        if (!found ||
            (__int128)curNum * bestDen <
            (__int128)bestNum * curDen) {

            found = true;
            bestNum = curNum;
            bestDen = curDen;
        }
    }

    if (!found) {
        cout << "*\n";
        return 0;
    }

    cout << bestNum << ' ' << bestDen << '\n';
}
