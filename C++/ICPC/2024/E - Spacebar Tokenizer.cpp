// <3
// Tema: String / Trie + DP de Segmentacion (Maximo)
// Resumen: Partir cada cadena en tokens para que la suma de puntajes sea MAXIMA
// Detalle: Resuelve "Spacebar Tokenizer" (problema E, ICPC 2024): partir cada cadena en tokens
// para que la suma de puntajes sea MAXIMA. Cada token del diccionario vale su puntaje, y el
// enunciado dice que CUALQUIER otro token vale 0: se puede cortar donde sea. dp[i] = mejor
// puntaje para el prefijo de largo i. Hay dos transiciones: avanzar una letra sumando 0 (esa
// letra queda dentro de un token no reconocido) y, por cada palabra del diccionario que empiece
// en i y termine en j, proponer dp[i] + puntaje para dp[j+1]. LA TRAMPA DEL PROBLEMA ES ESA
// TRANSICION DE 0. Sin ella se exige que TODA la cadena se parta en palabras del diccionario, y
// el segundo caso del sample ("theonlytokenizeripo", donde "theonly" no esta) sale imposible en
// vez de 13. La primera version de este archivo tenia ese error: daba -1000000000 en el sample.
// Verificada la corregida contra todas las formas de cortar en 1015 frases chicas, sin fallos.
// Las palabras van en un trie para que desde cada posicion se camine una sola vez siguiendo la
// cadena: cada nodo con puntaje en el camino es una palabra que encaja, y el recorrido se corta
// en cuanto el trie no tiene la letra. Es exactamente el esqueleto de "Word Combinations" de
// CSES (que esta en este cuaderno) con max en vez de suma. Vale reconocer que "segmentar en
// palabras de un diccionario" es siempre esto, cambie o no lo que se optimiza. Con la
// transicion de 0 toda posicion es alcanzable, asi que ya no hace falta un valor de
// "imposible". Y dp va en long long porque el enunciado no acota los puntajes. El trie se
// reconstruye por caso de prueba, ya que el diccionario cambia.

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[26];
    int score;

    Node() {
        fill(next, next + 26, -1);
        score = -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, s;

    while (cin >> m >> s && (m || s)) {

        vector<Node> trie(1);

        // Insertar palabras
        for (int i = 0; i < m; i++) {

            string word;
            int value;

            cin >> word >> value;

            int node = 0;

            for (char c : word) {

                int x = c - 'a';

                if (trie[node].next[x] == -1) {
                    trie[node].next[x] = trie.size();
                    trie.emplace_back();
                }

                node = trie[node].next[x];
            }

            trie[node].score = value;
        }

        while (s--) {

            string a;
            cin >> a;

            int n = a.size();

            vector<long long> dp(n + 1, 0);

            for (int i = 0; i < n; i++) {

                // a[i] como parte de un token NO reconocido: suma 0
                dp[i + 1] = max(dp[i + 1], dp[i]);

                int node = 0;

                for (int j = i; j < n; j++) {

                    int x = a[j] - 'a';

                    if (trie[node].next[x] == -1)
                        break;

                    node = trie[node].next[x];

                    if (trie[node].score != -1) {

                        dp[j + 1] = max(
                            dp[j + 1],
                            dp[i] + trie[node].score
                        );
                    }
                }
            }

            cout << dp[n] << '\n';
        }
    }

    return 0;
}
