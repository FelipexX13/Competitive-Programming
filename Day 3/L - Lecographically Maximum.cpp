// <3
// Tema: Greedy / Bit Manipulation
// Resuelve "Lecographically Maximum" (Maratona SBC de Programacao 2024, Problem L): dada una
// lista de N enteros y una operacion que intercambia el k-esimo bit entre dos elementos
// cualquiera de la lista, hay que encontrar la secuencia lexicograficamente maxima alcanzable
// aplicando la operacion tantas veces como se quiera.
// Como la operacion permite mover libremente cualquier bit entre cualquier par de posiciones, lo
// unico que se conserva es, para cada bit b, cuantos elementos originalmente lo tenian encendido
// (cnt[b]). El codigo aplica una estrategia greedy: para cada bit b, enciende ese bit en los
// primeros cnt[b] elementos del resultado (ans[i] |= (1 << b)), lo que maximiza
// lexicograficamente la secuencia al concentrar todos los bits posibles en las posiciones mas a
// la izquierda.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> cnt(31, 0);

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        for (int b = 0; b <= 30; b++)
            if (x & (1 << b))
                cnt[b]++;
    }

    vector<int> ans(N, 0);

    for (int b = 0; b <= 30; b++)
        for (int i = 0; i < cnt[b]; i++)
            ans[i] |= (1 << b);

    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}