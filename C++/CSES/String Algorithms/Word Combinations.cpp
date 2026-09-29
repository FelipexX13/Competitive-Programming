// <3
// Tema: CSES / Trie + DP de Segmentacion (Conteo)
// Cuantas formas hay de partir s en palabras del diccionario. dp[i] = formas de armar el prefijo
// s[0..i), con dp[0] = 1, y cada palabra que empiece en i y termine en j suma dp[i] a dp[j+1].
// EL TRIE ES LO QUE HACE QUE QUEPA: probar cada palabra del diccionario en cada posicion seria
// O(n * k * largo). Con las palabras en un trie, desde cada i se camina UNA vez por el trie
// siguiendo s, y cada nodo marcado como fin de palabra en el camino es una palabra que encaja. El
// recorrido se corta apenas el trie no tiene la letra, asi que desde cada i se avanza a lo sumo
// lo que mide la palabra mas larga.
// El if (dp[i] == 0) continue ahorra caminar desde posiciones a las que no se puede llegar.
// CUANDO USAR: segmentar un texto en palabras de un diccionario, contando formas (como aqui) o
// maximizando un puntaje (como "E - Spacebar Tokenizer" de ICPC 2024, que es este mismo esqueleto
// con max en vez de suma).

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

struct Node {
    int nxt[26];
    bool end;

    Node() {
        memset(nxt, -1, sizeof(nxt));
        end = false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int k;
    cin >> k;

    vector<Node> trie(1);

    while (k--) {
        string w;
        cin >> w;

        int v = 0;

        for (char c : w) {
            int x = c - 'a';

            if (trie[v].nxt[x] == -1) {
                trie[v].nxt[x] = trie.size();
                trie.emplace_back();
            }

            v = trie[v].nxt[x];
        }

        trie[v].end = true;
    }

    int n = s.size();

    vector<long long> dp(n + 1);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        if (dp[i] == 0) continue;

        int v = 0;

        for (int j = i; j < n; j++) {
            int x = s[j] - 'a';

            if (trie[v].nxt[x] == -1)
                break;

            v = trie[v].nxt[x];

            if (trie[v].end) {
                dp[j + 1] += dp[i];

                if (dp[j + 1] >= MOD)
                    dp[j + 1] -= MOD;
            }
        }
    }

    cout << dp[n] << '\n';
}
