// <3
// Tema: CSES / Manacher (Palindromo Mas Largo que Termina en Cada Posicion)
// Resumen: Para cada posicion, el palindromo mas largo que TERMINA ahi
// Detalle: Para cada posicion, el palindromo mas largo que TERMINA ahi. Primero Manacher con
// centinelas distintos en los extremos ('$' al inicio, '^' al final), que es el truco para que
// el while de expansion no necesite chequear limites: al llegar a los bordes los centinelas
// nunca coinciden. EL BARRIDO QUE LO RESUELVE: si un palindromo centrado en i llega hasta j o
// mas, entonces tambien hay un palindromo centrado en i que termina EXACTAMENTE en j (se
// recorta simetrico). Y entre dos centros que alcanzan j, el de mas a la izquierda da el
// palindromo mas largo. Asi que para cada j basta el PRIMER centro, de izquierda a derecha, que
// lo alcanza. Por eso el puntero j nunca retrocede: cada centro asigna las posiciones nuevas
// que alcanza y que nadie antes alcanzo. Cada posicion se asigna una vez por pasada, y todo
// queda O(n). Se hace una pasada para impares y otra para pares, quedandose con el maximo.

#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(string s) {
    string t = "$";

    for (char c : s) {
        t += '#';
        t += c;
    }

    t += "#^";

    vector<int> p(t.size());

    int l = 1;
    int r = 1;

    for (int i = 1; i < (int)t.size() - 1; i++) {

        p[i] = max(0, min(r - i, p[l + r - i]));

        while (t[i - p[i]] == t[i + p[i]])
            p[i]++;

        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }

    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<int> p = manacher(s);

    int n = s.size();

    vector<int> ans(n);

    /*
        PALINDROMOS IMPARES

        i representa el centro en la cadena original.

        p[(i + 1) * 2] / 2
        nos dice cuanto puede extenderse el palindromo.

        Para cada centro:

            i, i+1, i+2, ...

        podemos obtener palindromos de longitudes:

            1, 3, 5, 7, ...

        Pero usamos j para no volver a procesar posiciones
        que ya fueron actualizadas.
    */

    int j = 0;

    for (int i = 0; i < n; i++) {

        j = max(j, i);

        int limit = i + (p[(i + 1) * 2] / 2);

        for (; j < limit; j++) {
            ans[j] = 1 + 2 * (j - i);
        }
    }

    /*
        PALINDROMOS PARES

        Ahora hacemos lo mismo para palindromos pares.

        El centro esta entre i-1 e i.
    */

    j = 0;

    for (int i = 1; i < n; i++) {

        j = max(j, i);

        int limit = i + (p[1 + i * 2] / 2);

        for (; j < limit; j++) {
            ans[j] = max(ans[j], 2 * (j - i + 1));
        }
    }

    for (int x : ans)
        cout << x << ' ';

    cout << '\n';
}
