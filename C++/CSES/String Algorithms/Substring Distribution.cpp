// <3
// Tema: CSES / Suffix Automaton + Arreglo de Diferencias
// Resumen: Cuantas subcadenas distintas hay de cada largo, de 1 hasta n
// O: (n), un barrido de estados mas uno de largos
// Uso: por cada estado v, diff[len[link]+1]++ y diff[len[v]+1]--; prefijos
// Detalle: Cuantas subcadenas distintas hay de cada largo 1, 2, ..., n. Cada estado del suffix
// automaton aporta UN rango contiguo de largos, de len[link]+1 hasta len[v], y aporta
// exactamente una subcadena distinta por cada largo de ese rango. Entonces en vez de sumar uno
// por uno se marca el rango con un ARREGLO DE DIFERENCIAS (+1 al inicio, -1 despues del fin) y
// al final una pasada de sumas acumuladas da la respuesta de todos los largos. Esa combinacion
// de 'cada estado es un intervalo' + 'arreglo de diferencias' es lo que convierte un problema
// de O(n^2) subcadenas en O(n).

#include <bits/stdc++.h>
using namespace std;

struct SAM
{
    struct Node
    {
        int next[26];
        int link, len;

        Node()
        {
            memset(next, -1, sizeof(next));
            link = -1;
            len = 0;
        }
    };

    vector<Node> st;
    int last = 0;

    SAM(int n)
    {
        st.reserve(2 * n);
        st.push_back(Node());
    }

    void add(char ch)
    {
        int c = ch - 'a';

        int cur = st.size();
        st.push_back(Node());

        st[cur].len = st[last].len + 1;

        int p = last;

        while(p != -1 && st[p].next[c] == -1)
        {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if(p == -1)
        {
            st[cur].link = 0;
        }
        else
        {
            int q = st[p].next[c];

            if(st[p].len + 1 == st[q].len)
            {
                st[cur].link = q;
            }
            else
            {
                int clone = st.size();
                st.push_back(st[q]);

                st[clone].len = st[p].len + 1;

                while(p != -1 && st[p].next[c] == q)
                {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    SAM sam(s.size());

    for(char c : s)
        sam.add(c);

    vector<long long> diff(s.size() + 2);

    for(int v = 1; v < sam.st.size(); v++)
    {
        int l = sam.st[sam.st[v].link].len + 1;
        int r = sam.st[v].len;

        diff[l]++;
        diff[r + 1]--;
    }

    long long cur = 0;

    for(int len = 1; len <= s.size(); len++)
    {
        cur += diff[len];
        cout << cur << ' ';
    }

    cout << '\n';
}
