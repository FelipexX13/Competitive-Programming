// <3
// Tema: CSES / Suffix Automaton (Ocurrencias por Estado)
// O: (n), construir mas ordenar por largo con counting sort
// Uso: sam.longestRepeating(s) -> la subcadena mas larga que sale 2+ veces, o -1
// La subcadena mas larga que aparece al menos dos veces.
// Se cuenta cuantas veces ocurre cada estado: los estados creados como 'cur' valen 1 y los clones
// valen 0, y despues se propaga por los suffix links de los estados LARGOS hacia los cortos. Para
// recorrer en ese orden se ordenan los estados por len con COUNTING SORT, que es O(n) y es el
// patron estandar en suffix automaton (ordenar con sort() seria O(n log n) y mas codigo).
// Con occ listo, la respuesta es el estado de mayor len con occ >= 2. firstPos guarda donde
// termino la primera ocurrencia, asi que la subcadena se recorta con substr(pos - len + 1, len).
// Los clones arrancan en 0 a proposito: representan la misma posicion que q, y contarlos tambien
// duplicaria las ocurrencias.

#include <bits/stdc++.h>
using namespace std;

struct State
{
    int next[26];
    int link;
    int len;
    int occ;
    int firstPos;

    State()
    {
        fill(next, next + 26, -1);
        link = -1;
        len = 0;
        occ = 0;
        firstPos = -1;
    }
};

struct SuffixAutomaton
{
    vector<State> st;
    int last;

    SuffixAutomaton(int n)
    {
        st.reserve(2 * n);
        st.push_back(State());

        last = 0;
    }

    void add(char c, int pos)
    {
        int x = c - 'a';

        int cur = st.size();
        st.push_back(State());

        st[cur].len = st[last].len + 1;
        st[cur].firstPos = pos;
        st[cur].occ = 1;

        int p = last;

        while(p != -1 && st[p].next[x] == -1)
        {
            st[p].next[x] = cur;
            p = st[p].link;
        }

        if(p == -1)
        {
            st[cur].link = 0;
        }
        else
        {
            int q = st[p].next[x];

            if(st[p].len + 1 == st[q].len)
            {
                st[cur].link = q;
            }
            else
            {
                int clone = st.size();
                st.push_back(st[q]);

                st[clone].len = st[p].len + 1;
                st[clone].occ = 0;

                while(p != -1 && st[p].next[x] == q)
                {
                    st[p].next[x] = clone;
                    p = st[p].link;
                }

                st[q].link = clone;
                st[cur].link = clone;
            }
        }

        last = cur;
    }

    string longestRepeating(string s)
    {
        int n = s.size();

        for(int i = 0; i < n; i++)
        {
            add(s[i], i);
        }

        vector<int> cnt(n + 1);

        for(auto &state : st)
        {
            cnt[state.len]++;
        }

        for(int i = 1; i <= n; i++)
        {
            cnt[i] += cnt[i - 1];
        }

        vector<int> order(st.size());

        for(int i = st.size() - 1; i >= 0; i--)
        {
            order[--cnt[st[i].len]] = i;
        }

        // Propagamos ocurrencias desde estados largos
        // hacia sus suffix links.
        for(int i = order.size() - 1; i > 0; i--)
        {
            int u = order[i];

            st[st[u].link].occ += st[u].occ;
        }

        int best = 0;
        int bestState = -1;

        for(int i = 1; i < (int)st.size(); i++)
        {
            if(st[i].occ >= 2 && st[i].len > best)
            {
                best = st[i].len;
                bestState = i;
            }
        }

        if(best == 0)
        {
            return "-1";
        }

        int pos = st[bestState].firstPos;

        return s.substr(pos - best + 1, best);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    SuffixAutomaton sam(s.size());

    cout << sam.longestRepeating(s) << '\n';

    return 0;
}
