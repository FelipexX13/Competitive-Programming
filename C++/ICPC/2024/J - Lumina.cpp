// <3
// Tema: Graph / Componentes Fuente de la Condensacion (Tarjan)
// Resumen: Resuelve "Lumina" (problema J, ICPC 2024)
// Detalle: Resuelve "Lumina" (problema J, ICPC 2024). Cada gema ilumina a las que caen dentro
// de SU radio, y el codigo cuenta el minimo de gemas que hay que encender a mano para que al
// final todas queden encendidas. EL GRAFO ES DIRIGIDO aunque venga de circulos: u alcanza a v
// si v esta dentro del radio de u, y como cada gema tiene su propio radio, que u ilumine a v no
// implica lo contrario. Ademas es IMPLICITO: las aristas no se guardan, se recalculan con
// dist^2 <= r^2 (en enteros, sin raiz) cada vez que hacen falta. Son O(n^2) aristas. LA IDEA:
// dentro de una componente fuertemente conexa, encender una gema enciende a todas. Asi que se
// comprime cada SCC a un nodo y queda un DAG (la condensacion). En ese DAG, una componente a la
// que no le llega ninguna arista desde otra (grado de entrada 0) no la puede encender nadie de
// afuera: hay que encender una de sus gemas a mano. Y basta con eso, porque toda componente del
// DAG es alcanzable desde alguna fuente. La respuesta es la cantidad de componentes FUENTE. Las
// SCC salen con Tarjan: disc[] es el orden de descubrimiento, low[] el menor disc alcanzable
// sin salir de la pila, y cuando low[u] == disc[u], u es la raiz de una componente y se saca de
// la pila hasta llegar a el. Las aristas que cruzan entre componentes distintas son las que
// marcan hasIncoming. CUANDO USAR: "minimo de puntos de partida para alcanzarlo todo", "a
// cuantos hay que avisarle para que el rumor llegue a todos". Si ademas piden el minimo de
// aristas a AGREGAR para que el grafo quede fuertemente conexo, la respuesta es max(#fuentes,
// #sumideros), salvo que ya sea una sola componente. OJO: Tarjan recursivo llega a profundidad
// n. Con aristas O(n^2), n no puede ser muy grande y no hay problema, pero en un grafo con
// millones de nodos habria que hacerlo iterativo. AMBIGUEDAD DEL ENUNCIADO: una frase define
// "cerca" de forma SIMETRICA ("si una gema esta dentro del radio de la otra"), y con esa
// lectura la respuesta seria solo el numero de componentes conexas. Pero el ejemplo y la figura
// hablan del aura de CADA gema alcanzando a otras, que es la lectura dirigida de este codigo.
// Los tres samples dan igual con las dos. El caso que las separa: gemas en (-10^9,0) radio
// 10^9, (0,0) radio 0 y (10^9,0) radio 10^9 da 2 dirigido y 1 simetrico. Verificado bajo la
// lectura dirigida contra fuerza bruta en 700 casos; N = 5000 en ~200 ms.

#include <bits/stdc++.h>
using namespace std;

struct Gem {
    long long x, y, r;
};

int n;
vector<Gem> gems;

vector<int> disc, low, st, component;
vector<bool> inStack;

int timer;
int sccCount;

void tarjan(int u) {

    disc[u] = low[u] = timer++;

    st.push_back(u);
    inStack[u] = true;

    for (int v = 0; v < n; v++) {

        if (u == v)
            continue;

        long long dx = gems[u].x - gems[v].x;
        long long dy = gems[u].y - gems[v].y;

        // u puede iluminar v
        if (dx * dx + dy * dy > gems[u].r * gems[u].r)
            continue;

        if (disc[v] == -1) {

            tarjan(v);

            low[u] = min(low[u], low[v]);

        }
        else if (inStack[v]) {

            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {

        while (true) {

            int v = st.back();
            st.pop_back();

            inStack[v] = false;

            component[v] = sccCount;

            if (v == u)
                break;
        }

        sccCount++;
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n != 0) {

        gems.resize(n);

        for (auto &gem : gems)
            cin >> gem.x >> gem.y >> gem.r;

        disc.assign(n, -1);
        low.assign(n, 0);
        component.assign(n, -1);
        inStack.assign(n, false);

        st.clear();

        timer = 0;
        sccCount = 0;

        // Encontrar SCC
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1)
                tarjan(i);
        }

        // inDegree de cada SCC
        vector<bool> hasIncoming(sccCount, false);

        // Revisar todas las aristas
        for (int u = 0; u < n; u++) {

            for (int v = 0; v < n; v++) {

                if (u == v)
                    continue;

                long long dx = gems[u].x - gems[v].x;
                long long dy = gems[u].y - gems[v].y;

                // u -> v
                if (dx * dx + dy * dy <= gems[u].r * gems[u].r) {

                    if (component[u] != component[v]) {
                        hasIncoming[component[v]] = true;
                    }
                }
            }
        }

        int answer = 0;

        for (int c = 0; c < sccCount; c++) {
            if (!hasIncoming[c])
                answer++;
        }

        cout << answer << '\n';
    }

    return 0;
}
