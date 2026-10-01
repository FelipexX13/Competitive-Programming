// <3
// Tema: CSES / Aho-Corasick (Conteo de Ocurrencias)
// O: (suma de patrones + |s| + 26*nodos)
// Uso: ac.addString(p) por patron; build(); search(s); propagate(); getCount(p)
// Cuantas veces aparece cada patron dentro del texto, con TODOS los patrones a la vez.
// Aho-Corasick es el trie de los patrones mas un suffix link por nodo, que apunta al nodo del
// sufijo propio mas largo que tambien es prefijo de algun patron. Es la generalizacion del fallo
// de KMP a varios patrones a la vez.
// build() hace DOS cosas en el mismo BFS y por eso queda tan corto: calcula los suffix links y
// ademas convierte el trie en AUTOMATA, rellenando las transiciones que no existen con las del
// suffix link. Despues de eso next[u][c] nunca es -1 y recorrer el texto es un for sin whiles.
// search() camina el texto y marca +1 en cada nodo por el que pasa. propagate() recorre el orden
// BFS AL REVES sumando cada nodo a su suffix link: asi cada patron recibe tambien lo que conto
// cualquier patron mas largo que lo contiene como sufijo. Ese paso es el que suele faltar.
// CUANDO USAR: varios patrones contra un texto. Con un solo patron sobra KMP.

#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick
{
    struct Node
    {
        int next[26];
        int link;
        int cnt;

        Node()
        {
            fill(next, next + 26, -1);
            link = 0;
            cnt = 0;
        }
    };

    vector<Node> trie;
    vector<int> order;

    AhoCorasick()
    {
        trie.push_back(Node());
    }

    void addString(string s)
    {
        int u = 0;

        for(char c : s)
        {
            int x = c - 'a';

            if(trie[u].next[x] == -1)
            {
                trie[u].next[x] = trie.size();
                trie.push_back(Node());
            }

            u = trie[u].next[x];
        }
    }

    int getNode(string s)
    {
        int u = 0;

        for(char c : s)
        {
            u = trie[u].next[c - 'a'];
        }

        return u;
    }

    void build()
    {
        queue<int> q;

        for(int c = 0; c < 26; c++)
        {
            int v = trie[0].next[c];

            if(v == -1)
            {
                trie[0].next[c] = 0;
            }
            else
            {
                trie[v].link = 0;
                q.push(v);
            }
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            order.push_back(u);

            for(int c = 0; c < 26; c++)
            {
                int v = trie[u].next[c];

                if(v == -1)
                {
                    trie[u].next[c] = trie[trie[u].link].next[c];
                }
                else
                {
                    trie[v].link = trie[trie[u].link].next[c];
                    q.push(v);
                }
            }
        }
    }

    void search(string s)
    {
        int u = 0;

        for(char c : s)
        {
            u = trie[u].next[c - 'a'];
            trie[u].cnt++;
        }
    }

    void propagate()
    {
        for(int i = order.size() - 1; i >= 0; i--)
        {
            int u = order[i];

            trie[trie[u].link].cnt += trie[u].cnt;
        }
    }

    int getCount(string s)
    {
        int u = getNode(s);
        return trie[u].cnt;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int k;
    cin >> k;

    vector<string> patterns(k);

    AhoCorasick ac;

    for(int i = 0; i < k; i++)
    {
        cin >> patterns[i];
        ac.addString(patterns[i]);
    }

    ac.build();

    ac.search(s);

    ac.propagate();

    for(string p : patterns)
    {
        cout << ac.getCount(p) << '\n';
    }

    return 0;
}
