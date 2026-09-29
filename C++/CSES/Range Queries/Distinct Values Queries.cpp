// <3
// Tema: CSES / Mo's Algorithm
// CUANDO USAR MO: esta es la pregunta importante, porque Mo no es la primera opcion casi nunca.
// Antes de llegar aqui hay que descartar lo demas, en este orden:
//   - Suma, xor o cualquier operacion con INVERSA  -> prefix sums, O(1) por consulta.
//   - min, max, gcd, o cualquier operacion asociativa e idempotente sin updates
//                                                  -> sparse table, O(1) por consulta.
//   - Operacion asociativa CON updates             -> segment tree o BIT, O(log n).
// Mo entra cuando la respuesta NO se puede combinar a partir de las mitades. "Cuantos valores
// distintos", "cual es la moda", "cuantos valores aparecen exactamente k veces", "suma de los
// cuadrados de las frecuencias": de conocer la respuesta de [l,m] y la de [m+1,r] no sale la de
// [l,r], asi que ningun segment tree la aguanta. Lo que si se puede es pasar de un rango al de
// al lado metiendo o sacando UN elemento en O(1). Eso es exactamente lo que Mo explota.
// Las tres condiciones que se tienen que cumplir para usarlo:
//   1. OFFLINE. Hay que tener las q consultas antes de empezar a responder, porque lo primero
//      que se hace es reordenarlas. Si el problema es interactivo o la consulta i+1 depende de
//      la respuesta i, Mo queda descartado de entrada.
//   2. SIN actualizaciones al arreglo (existe Mo con updates, pero es O(n^(5/3)) y es otra
//      plantilla distinta).
//   3. add y remove de UN elemento en O(1), o a lo sumo O(log n).
// Los limites tambien mandan: Mo es O((n+q)*sqrt(n)), asi que vive comodo en n, q <= 2*10^5 con
// 1 o 2 segundos. Con n de 10^6 ya no cabe y toca buscar otra cosa.
//
// COMO FUNCIONA: se mantiene una ventana [L,R] con el conteo cnt[] de cada valor y el total de
// distintos. Cada consulta se atiende moviendo L y R hasta su posicion. Movidos en desorden eso
// seria O(n) por consulta, pero ordenando por (bloque de l, r) cada puntero se mueve poco: R
// solo avanza dentro de cada bloque (n por bloque, sqrt(n) bloques) y L nunca se aleja mas de
// un bloque. De ahi sale el sqrt.
// El orden de los cuatro while es el canonico: primero los dos que EXPANDEN y despues los dos
// que CONTRAEN, para que la ventana no quede invertida (L por delante de R) en medio del ajuste.
//
// Detalles de esta implementacion:
//   - B = sqrt(n) es lo estandar; el tamano de bloque que minimiza el costo teorico es
//     n/sqrt(q), que ayuda cuando q es mucho mas chico que n.
//   - La compresion de coordenadas NO es opcional aqui: los valores llegan a 10^9 y cnt[] se
//     indexa por valor, asi que sin comprimir habria que reservar 10^9 enteros.
//   - remove() se llama igual que std::remove de <algorithm>; con using namespace std compila
//     igual porque ninguna sobrecarga de la STL acepta un solo int, pero es un nombre a evitar.
// Para este problema puntual existe algo mas rapido: offline ordenando las consultas por r y
// llevando un BIT con la ultima aparicion de cada valor, O((n+q)*log n). Mo se queda porque es
// la plantilla general: el dia que cambien "distintos" por "moda" o por "frecuencia de
// frecuencias", el BIT no sirve y esto de aqui solo cambia en add y remove.

#include <bits/stdc++.h>
using namespace std;

int B;                      // tamano de bloque
vector<int> a, cnt;
int distinct = 0;

struct Query { int l, r, idx; };

void add(int i)    { if (cnt[a[i]]++ == 0) distinct++; }
void remove(int i) { if (--cnt[a[i]] == 0) distinct--; }

vector<int> mo(vector<Query>& qs) {
    sort(qs.begin(), qs.end(), [](const Query& x, const Query& y) {
        if (x.l / B != y.l / B) return x.l / B < y.l / B;  // por bloque de l
        return x.r < y.r;                                  // luego por r
    });

    vector<int> ans(qs.size());
    int L = 0, R = -1;              // ventana actual vacia
    for (auto& q : qs) {
        while (R < q.r) add(++R);
        while (L > q.l) add(--L);
        while (R > q.r) remove(R--);
        while (L < q.l) remove(L++);
        ans[q.idx] = distinct;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    a.resize(n);
    for (int& x : a) cin >> x;

    // compresion de coordenadas
    vector<int> v(a);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int& x : a) x = lower_bound(v.begin(), v.end(), x) - v.begin();
    cnt.assign(v.size(), 0);

    B = max(1, (int)sqrt(n));
    vector<Query> qs(q);
    for (int i = 0; i < q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--; qs[i].r--;
        qs[i].idx = i;
    }

    for (int x : mo(qs)) cout << x << '\n';
}
