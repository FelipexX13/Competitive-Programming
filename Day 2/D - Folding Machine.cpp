// <3
// Tema: Search / State-Space BFS
// Resuelve "Folding Machine" (Maratona de Programacao da SBC 2013, problem D): una cinta de N
// celdas se puede doblar por cualquier punto entre celdas adyacentes (incluso en los extremos,
// lo que invierte la cinta), sumando los valores de las celdas que quedan superpuestas. Dado un
// tape de entrada y uno de salida, determina si existe una secuencia de dobleces que transforme
// el primero en el segundo.
// Como cada doblez real reduce estrictamente el largo de la cinta, genera todos los estados
// alcanzables agrupandolos por longitud (states[len]), probando cada pliegue posible de h
// celdas desde la izquierda o la derecha; normalized() reduce cada estado a su forma canonica
// (el minimo entre la cinta y su reverso) para no explorar duplicados. Al final solo compara si
// el output normalizado aparece entre los estados generados de longitud M.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// A fold at either end may reverse the tape, so both directions
// represent the same state.
vector<ll> normalized(vector<ll> tape) {
    vector<ll> reversed = tape;
    reverse(reversed.begin(), reversed.end());
    return min(tape, reversed);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> input(n);
    for (ll &x : input) cin >> x;

    int m;
    cin >> m;
    vector<ll> output(m);
    for (ll &x : output) cin >> x;

    // The sum of all cells never changes after a fold.
    if (accumulate(input.begin(), input.end(), 0LL) !=
        accumulate(output.begin(), output.end(), 0LL)) {
        cout << "N\n";
        return 0;
    }

    vector<set<vector<ll>>> states(n + 1);
    states[n].insert(normalized(input));

    // Every real fold lowers the tape length. Thus a state only needs
    // to be generated once, in the set indexed by its length.
    for (int len = n; len > m; --len) {
        for (const vector<ll> &tape : states[len]) {
            for (int h = 1; h <= len / 2; ++h) {
                // Fold the h cells at the left end over the rest.
                vector<ll> next;
                next.reserve(len - h);
                for (int j = 0; j < h; ++j)
                    next.push_back(tape[h + j] + tape[h - 1 - j]);
                for (int j = 2 * h; j < len; ++j)
                    next.push_back(tape[j]);
                if (len - h >= m)
                    states[len - h].insert(normalized(next));

                // Fold the h cells at the right end over the rest.
                next.clear();
                const int leftSize = len - h;
                for (int j = 0; j < leftSize - h; ++j)
                    next.push_back(tape[j]);
                for (int j = 0; j < h; ++j)
                    next.push_back(tape[leftSize - h + j] + tape[len - 1 - j]);
                if (len - h >= m)
                    states[len - h].insert(normalized(next));
            }
        }
    }

    cout << (states[m].count(normalized(output)) ? "S\n" : "N\n");
}