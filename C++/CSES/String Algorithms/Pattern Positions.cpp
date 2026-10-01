// <3
// Tema: CSES / Aho-Corasick (Primera Aparicion)
// Resumen: Donde empieza la primera aparicion de cada patron, o -1 si no esta
// O: (suma de patrones + |s| + 26*nodos)
// Uso: search() guarda min(first); getFirst(p) devuelve first - |p| + 1, o -1
// Detalle: La posicion donde EMPIEZA la primera aparicion de cada patron, o -1 si no aparece.
// Mismo esqueleto de Aho-Corasick, cambiando el contador por un minimo: en vez de cnt se guarda
// first, la posicion mas temprana en que el recorrido del texto paso por ese nodo. Se propaga
// igual por los suffix links al reves, pero con min en vez de suma. EL DETALLE: first guarda
// donde TERMINA la ocurrencia, asi que para devolver donde empieza hay que restar el largo del
// patron, first - |p| + 1. Equivocarse ahi da respuestas corridas. El INT_MAX como marca de
// 'nunca aparecio' sobrevive la propagacion porque min(INF, INF) = INF.

#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick
{
    struct Node
    {
        int next[26];
        int link;
        int first;

        Node()
        {
            fill(next, next + 26, -1);
            link = 0;
            first = INT_MAX;
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

        for(int i = 0; i < (int)s.size(); i++)
        {
            u = trie[u].next[s[i] - 'a'];

            trie[u].first = min(trie[u].first, i + 1);
        }
    }

    void propagate()
    {
        for(int i = order.size() - 1; i >= 0; i--)
        {
            int u = order[i];

            trie[trie[u].link].first =
                min(trie[trie[u].link].first, trie[u].first);
        }
    }

    int getFirst(string s)
    {
        int u = 0;

        for(char c : s)
        {
            u = trie[u].next[c - 'a'];
        }

        if(trie[u].first == INT_MAX)
            return -1;

        return trie[u].first - (int)s.size() + 1;
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
        cout << ac.getFirst(p) << '\n';
    }

    return 0;
}
