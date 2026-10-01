// <3
// Tema: CSES / Aho-Corasick (Aparece o No)
// Resumen: Si cada patron aparece o no en el texto, con todos a la vez
// O: (suma de patrones + |s| + 26*nodos)
// Uso: igual que Counting Patterns, pero appears(p) devuelve si cnt > 0
// Detalle: Decir, para cada patron, si aparece o no dentro del texto. Es el mismo Aho-Corasick
// de Counting Patterns: el conteo propagado ya responde la pregunta, y appears() solo mira si
// quedo mayor que cero. Vale la pena tener los dos lado a lado porque la unica diferencia es la
// ultima linea. Si solo hace falta el si/no, tambien sirve un suffix automaton del texto y
// caminar cada patron por el; eso es O(suma de patrones) sin construir nada sobre los patrones.

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

    bool appears(string s)
    {
        int u = 0;

        for(char c : s)
        {
            u = trie[u].next[c - 'a'];
        }

        return trie[u].cnt > 0;
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
        if(ac.appears(p))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
