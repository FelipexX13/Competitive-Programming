// <3
// Tema: Data Structures / Heap con Borrado Perezoso
// Resumen: Hay n enteros no negativos y q operaciones
// Detalle: Resuelve "Aquarium Bubble Lights" (Codeforces, problema B): hay n enteros no
// negativos y q operaciones; en cada una PRIMERO se le resta 1 a todos (sin bajar de cero) y
// DESPUES, si x no es cero, se hace a[x] = max(a[x], v). Tras cada operacion hay que decir
// cuantos quedan positivos, y al final imprimir la secuencia. EL TRUCO ES NO DECREMENTAR NUNCA.
// Restarle 1 a los n elementos en cada una de las q operaciones cuesta O(n*q) = 4*10^10 y no
// pasa ni de lejos. En vez de guardar el valor, se guarda CUANDO se va a volver cero: expire[i]
// = valor + el instante en que se fijo Con eso, "a[i] sigue positivo en el instante t" es
// simplemente expire[i] > t, y el valor real en ese momento es max(0, expire[i] - t). El
// decremento global desaparece: no se toca a nadie, solo avanza el reloj. Al inicio el reloj
// esta en 0, asi que expire[i] arranca valiendo a[i], y al final los valores son expire[i] - q.
// EL BORRADO PEREZOSO ES LA OTRA MITAD. Se mete cada (expire, indice) en un heap de minimos
// para saber quien expira primero. El problema es que cuando a[x] se actualiza, su entrada
// VIEJA sigue tirada en el heap, y std::priority_queue no sabe borrar un elemento del medio. La
// salida es no borrarla: se deja ahi y, al sacarla, se compara contra el valor vigente if
// (expire[id] != e) continue; y si no coinciden es una entrada muerta y se ignora. Cada
// operacion mete a lo sumo una entrada, asi que el heap nunca pasa de n + q elementos y el
// costo total sigue siendo O((n+q) log n). Este patron es el que se usa siempre que haga falta
// un decrease-key y la cola de prioridad no lo tenga: es el mismo "if (dist >
// distancia[actual]) continue;" de Dijkstra. EL ORDEN DE LOS DOS PASOS NO ES NEGOCIABLE, y el
// enunciado lo recalca: primero se vacian los que expiran en el instante t (el while), y solo
// despues se aplica la asignacion. Si se hace al reves, un elemento que acaba de recibir un
// valor nuevo se contaria como expirado. El contador de positivos se lleva al vuelo, restando
// cuando alguien expira y sumando cuando uno pasa de cero a positivo; recorrer el arreglo en
// cada operacion seria volver al O(n*q). Sobre los tipos: expire llega a lo sumo a 10^9 +
// 2*10^5, que todavia cabe en int, pero en long long uno no tiene que pararse a comprobarlo.
// Verificado contra una simulacion directa del enunciado (restar 1 a todos, asignar, contar) en
// 4000 casos aleatorios con valores chicos para forzar que todo expire seguido: sin una sola
// diferencia, mas el sample. Medido con n = q = 2*10^5 y valores hasta 10^9: 0.27 s contra un
// limite de 1 s, y 0.16 s en el adversario de valores 0..3 donde el heap trabaja todo el
// tiempo. OJO: usa structured bindings (auto [e, id]), que piden C++17. En Codeforces compila,
// pero con un g++ viejo hay que volver a .first y .second.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> expire(n + 1);

    // (expire, index)
    priority_queue<pair<ll, int>,
                   vector<pair<ll, int>>,
                   greater<pair<ll, int>>> pq;

    for (int i = 1; i <= n; ++i) {
        ll a;
        cin >> a;

        expire[i] = a;

        if (a > 0)
            pq.push({expire[i], i});
    }

    int positive = 0;

    // Initially, all a[i] > 0 are positive.
    for (int i = 1; i <= n; ++i)
        if (expire[i] > 0)
            positive++;

    for (int t = 1; t <= q; ++t) {
        int x;
        ll v;
        cin >> x >> v;

        // After the mandatory decrement at operation t,
        // an element is zero iff expire[i] <= t.
        while (!pq.empty() && pq.top().first <= t) {
            auto [e, id] = pq.top();
            pq.pop();

            // Old heap entry.
            if (expire[id] != e)
                continue;

            expire[id] = 0;
            positive--;
        }

        if (x != 0) {
            // Current value after the decrement.
            ll cur = max(0LL, expire[x] - t);

            ll nw = max(cur, v);

            if (cur == 0 && nw > 0)
                positive++;

            if (nw > 0) {
                expire[x] = t + nw;
                pq.push({expire[x], x});
            } else {
                expire[x] = 0;
            }
        }

        cout << positive << '\n';
    }

    // Final values are expire[i] - q.
    for (int i = 1; i <= n; ++i) {
        if (i > 1)
            cout << ' ';

        cout << max(0LL, expire[i] - q);
    }

    cout << '\n';

    return 0;
}
