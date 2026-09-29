// <3
// Tema: Graph / Clique Maximo (Bron-Kerbosch con Pivote)
// Resuelve "Holy Network" (problema H, ICPC 2025): dados N numeros, hallar el grupo mas grande en
// el que CADA PAR comparta un factor mayor que 1.
// LA TRAMPA ES "CADA PAR". Que el grupo este conectado NO alcanza: hay que pedir que todos con
// todos sean compatibles, o sea un CLIQUE, no una componente conexa. El contraejemplo mas chico
// es {6, 10, 35}: 6 y 10 comparten el 2, 10 y 35 comparten el 5, pero 6 y 35 son coprimos. La
// componente conexa mide 3 y el grupo valido mide 2.
// La primera version de este archivo usaba DSU y devolvia el tamano de la componente: pasaba los
// tres casos del sample (donde ambas cosas coinciden) pero fallaba 762 de 1500 casos aleatorios
// contra fuerza bruta. Esta version, con clique maximo, no falla ninguno.
// EL CLIQUE MAXIMO ES NP-DIFICIL, pero aqui N <= 50 y Bron-Kerbosch con pivote lo resuelve rapido:
// se mantiene R (el clique en curso), P (candidatos) y X (ya descartados), todo en mascaras de 64
// bits porque N cabe en un unsigned long long. El PIVOTE es lo que evita la explosion: se elige el
// vertice de P|X con mas vecinos en P y solo se ramifica por los candidatos que NO son sus
// vecinos, porque cualquier clique maximal o contiene al pivote o contiene a alguno de esos.
// La poda extra (si lo que llevamos mas todos los candidatos no supera al mejor, se corta) ayuda
// bastante cuando el grafo es denso.
// POR QUE NO EXPLOTA CON ESTOS DATOS: cada numero es <= 10^12, asi que tiene a lo sumo 11 primos
// distintos (2*3*5*...*31 ya pasa de 2*10^11). El grafo es entonces la union de unos pocos
// cliques, uno por primo, y esa estructura deja pocos cliques maximales. Medido con 200 casos de
// N = 50: 17 ms si todos comparten factor, 20 ms con numeros de 11 primos, y 84 ms en el
// adversario que mas cliques maximales logre construir.
// El minimo es 1: un grupo de un solo ingrediente es armonico porque no hay pares que revisar.
// Ojo con el 1 como entrada: gcd(1, x) = 1, asi que un 1 no es compatible con nada.
// Se usa __gcd en vez de std::gcd para no depender de C++17 ni de incluir <numeric>.

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int n;
ull adj[64];
int mejor;

// Bron-Kerbosch con pivote sobre mascaras de 64 bits.
//   R = clique que llevamos, P = candidatos, X = ya descartados
void bron(ull R, ull P, ull X) {
    if (P == 0 && X == 0) {
        mejor = max(mejor, __builtin_popcountll(R));
        return;
    }

    // Cota: ni tomando todos los candidatos se mejora lo que ya hay.
    if (__builtin_popcountll(R) + __builtin_popcountll(P) <= mejor)
        return;

    // Pivote: el de P|X con mas vecinos en P. Solo hace falta ramificar por
    // los candidatos que NO son vecinos suyos.
    ull PX = P | X;
    int piv = __builtin_ctzll(PX);
    int mejorGrado = -1;

    for (ull t = PX; t; t &= t - 1) {
        int u = __builtin_ctzll(t);
        int g = __builtin_popcountll(adj[u] & P);
        if (g > mejorGrado) {
            mejorGrado = g;
            piv = u;
        }
    }

    for (ull t = P & ~adj[piv]; t; t &= t - 1) {
        int v = __builtin_ctzll(t);
        ull bit = 1ULL << v;

        bron(R | bit, P & adj[v], X & adj[v]);

        P &= ~bit;
        X |= bit;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n != 0) {

        vector<long long> a(n);

        for (auto &x : a)
            cin >> x;

        for (int i = 0; i < n; i++)
            adj[i] = 0;

        // Dos ingredientes son compatibles si comparten un factor mayor que 1.
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (__gcd(a[i], a[j]) > 1) {
                    adj[i] |= 1ULL << j;
                    adj[j] |= 1ULL << i;
                }

        // Un grupo de UN solo ingrediente siempre es armonico: no hay pares
        // que revisar. Por eso la respuesta nunca baja de 1.
        mejor = 1;

        ull todos = (n == 64) ? ~0ULL : ((1ULL << n) - 1);
        bron(0, todos, 0);

        cout << mejor << '\n';
    }

    return 0;
}
