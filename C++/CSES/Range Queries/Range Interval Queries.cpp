// <3
// Tema: CSES / Barrido Offline con Fenwick
// Resumen: Contar cuantos elementos de [l,r] tienen valor en [a,b], sin actualizaciones
// O: ((n+q) log n) con barrido de eventos
// Uso: ordenar Event por posicion y responder offline con el Fenwick
// Detalle: Contar cuantos elementos de [l,r] tienen valor en [a,b], sin actualizaciones. Es una
// consulta en DOS dimensiones (posicion y valor), y la tecnica es bajarla a una sola con un
// barrido offline. COMO: cada consulta se parte en dos eventos por la resta de prefijos sobre
// el VALOR, uno con signo + en b y otro con signo - en a-1. Todos los eventos y todos los
// elementos se ordenan por valor, y se barre de menor a mayor insertando en el Fenwick la
// POSICION de cada elemento que ya entro. Cuando el barrido llega a un evento, el Fenwick
// contiene exactamente los elementos con valor <= ese umbral, asi que una consulta de rango de
// posiciones responde el evento. Ese es el patron general: una de las dos dimensiones se
// convierte en TIEMPO (el orden del barrido) y la otra se guarda en el Fenwick. CUANDO USAR:
// consultas de rango en dos dimensiones sin actualizaciones. Si hubiera actualizaciones seria
// una tercera dimension y tocaria BIT 2D o CDQ divide and conquer.

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

struct Event {
    int value, pos, id, sign;

    bool operator<(const Event& other) const {
        return value < other.value;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<pair<int,int>> a(n);

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i - 1] = {x, i};
    }

    sort(a.begin(), a.end());

    vector<Event> events;

    for (int i = 0; i < q; i++) {
        int l, r, c, d;
        cin >> l >> r >> c >> d;

        events.push_back({d, r, i, 1});
        events.push_back({d, l - 1, i, -1});
        events.push_back({c - 1, r, i, -1});
        events.push_back({c - 1, l - 1, i, 1});
    }

    sort(events.begin(), events.end());

    Fenwick fw(n);
    vector<int> ans(q);

    int p = 0;

    for (auto e : events) {

        while (p < n && a[p].first <= e.value) {
            fw.add(a[p].second, 1);
            p++;
        }

        ans[e.id] += e.sign * fw.sum(e.pos);
    }

    for (int x : ans)
        cout << x << '\n';
}
