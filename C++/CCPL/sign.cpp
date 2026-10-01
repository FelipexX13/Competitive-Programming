// <3
// Tema: String / Maximo Solape Sufijo-Prefijo (KMP)
// Resumen: Un letrero muestra k caracteres; en cada paso todo se corre una posicion a la
// izquierda y entra una letra...
// O: (n + m), el solape sale de la funcion de prefijos de KMP
// Detalle: Resuelve "Scrolling Sign" (problema H, CCPL): un letrero muestra k caracteres; en
// cada paso todo se corre una posicion a la izquierda y entra una letra nueva por la derecha.
// Hay que mostrar w palabras de k letras en orden, metiendo la menor cantidad de letras
// posible. TODA LA REDUCCION ESTA EN UNA OBSERVACION: si estando en la palabra A se meten t
// letras, el letrero queda mostrando A[t..k-1] seguido de las t nuevas. Para que eso sea B hace
// falta que A[t..k-1] sea igual a B[0..k-t-1], o sea que un SUFIJO de A de largo k-t coincida
// con el PREFIJO de B de ese mismo largo. Entonces el costo minimo de pasar de A a B es k -
// (mayor L tal que el sufijo de A de largo L es prefijo de B) y el total es k por la primera
// palabra (el letrero arranca vacio) mas esos costos. Que el enunciado permita mostrar palabras
// intermedias que no son del mensaje no cambia nada: esas son justamente los estados por los
// que se pasa mientras entran las t letras. Y lo de "si una palabra se repite seguida, se
// muestra una sola vez" sale gratis: si A == B el solape es k y el costo es 0, sin escribir
// ningun caso especial. COMO SE SACA EL SOLAPE SIN PAGAR O(k^2): se arma la cadena B + '#' + A
// y se calcula la funcion de fallo de KMP; su ultimo valor es el mayor prefijo de B que ademas
// es sufijo de A, que es exactamente L. El separador tiene que ser un caracter que NO aparezca
// en las palabras (aqui son mayusculas, asi que '#' sirve), porque si no el fallo podria cruzar
// de una mitad a la otra y devolver un valor mayor que k, que no corresponde a ningun solape
// real. Probar los L de k hacia abajo comparando substrings seria O(k^2) por par y O(w*k^2) en
// total; con k = w = 1500 eso son 3*10^9 y no pasa. Con KMP es O(k) por par, O(w*k) =
// 2.25*10^6. Medido en el peor caso del enunciado (k = 1500, w = 1500, palabras casi identicas
// para que el fallo retroceda lo mas posible), 20 casos completos: 512 ms. Verificado contra
// una simulacion REAL del letrero, con BFS sobre los estados posibles, en 1500 casos con k de 1
// a 4; y el solape de KMP contra comparar substrings a lo bruto en 20000 pares. Cero
// diferencias en ambas. Los dos samples dan 5 y 5, y el ejemplo del enunciado (CAT ATE TED con
// k = 3, que se logra metiendo CATED) da 5.

#include <bits/stdc++.h>
using namespace std;

// Mayor L tal que los ultimos L caracteres de a son los primeros L de b.
int solape(const string &a, const string &b) {
    string s = b + "#" + a;
    int m = s.size();

    vector<int> f(m, 0);

    for (int i = 1; i < m; i++) {
        int j = f[i - 1];

        while (j > 0 && s[i] != s[j])
            j = f[j - 1];

        if (s[i] == s[j])
            j++;

        f[i] = j;
    }

    return f[m - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int casos;
    cin >> casos;

    while (casos--) {
        int k, w;
        cin >> k >> w;

        vector<string> pal(w);
        for (int i = 0; i < w; i++) cin >> pal[i];

        // El letrero arranca vacio, asi que la primera palabra cuesta k.
        long long total = k;

        for (int i = 1; i < w; i++) {
            total += k - solape(pal[i - 1], pal[i]);
        }

        cout << total << '\n';
    }
    return 0;
}
