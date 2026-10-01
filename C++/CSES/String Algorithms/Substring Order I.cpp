// <3
// Tema: CSES / Descenso por el Suffix Automaton (Distintas)
// O: (26*n) construir y bajar
// Uso: dp[v] = cuantas subcadenas salen de v; se baja eligiendo letra con k
// La k-esima subcadena DISTINTA en orden alfabetico.
// dp[v] = cuantos caminos salen del estado v, que es cuantas subcadenas distintas empiezan con lo
// que lleva uno escrito. Se calcula en orden inverso de largo (otra vez counting sort).
// Despues se BAJA por el automata: en cada estado se prueban las letras de la 'a' a la 'z' y si
// k es mayor que dp[to] se descarta ese bloque entero y se resta; si no, la respuesta empieza por
// esa letra y se entra. Es la misma idea de 'buscar el k-esimo bajando por una estructura' que se
// usa en Fenwick o segment tree, pero sobre el automata.
// El dp arranca en 1 porque cuenta tambien la cadena vacia del propio estado; por eso el corte es
// k == 1 y no k == 0.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SuffixAutomaton
{
    struct State
    {
        int next[26];
        int link;
        int len;

        State()
        {
            fill(next, next + 26, -1);
            link = -1;
            len = 0;
        }
    };

    vector<State> st;
    int last;

    SuffixAutomaton(int n)
    {
        st.reserve(2 * n);
        st.push_back(State());
        last = 0;
    }

    void add(char ch)
    {
        int c = ch - 'a';

        int cur = st.size();
        st.push_back(State());

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

                st[q].link = clone;
                st[cur].link = clone;
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

    ll k;
    cin >> k;

    SuffixAutomaton sam(s.size());

    for(char c : s)
        sam.add(c);

    int sz = sam.st.size();

    // Ordenamos los estados por longitud
    vector<int> cnt(s.size() + 1);

    for(auto &v : sam.st)
        cnt[v.len]++;

    for(int i = 1; i <= (int)s.size(); i++)
        cnt[i] += cnt[i - 1];

    vector<int> order(sz);

    for(int i = sz - 1; i >= 0; i--)
        order[--cnt[sam.st[i].len]] = i;

    // dp[v] = cantidad de caminos/substrings desde v
    // Incluye el substring vacio.
    vector<ll> dp(sz, 1);

    for(int i = sz - 1; i >= 0; i--)
    {
        int v = order[i];

        for(int c = 0; c < 26; c++)
        {
            int to = sam.st[v].next[c];

            if(to != -1)
                dp[v] += dp[to];
        }
    }

    string ans;
    int v = 0;

    while(k > 0)
    {
        for(int c = 0; c < 26; c++)
        {
            int to = sam.st[v].next[c];

            if(to == -1)
                continue;

            // Todos los substrings de este bloque
            // empiezan con esta letra.
            if(k > dp[to])
            {
                k -= dp[to];
            }
            else
            {
                ans.push_back(char('a' + c));

                // Si k == 1, el substring actual
                // es exactamente la respuesta.
                if(k == 1)
                {
                    cout << ans << '\n';
                    return 0;
                }

                // El resto esta dentro de este estado.
                k--;
                v = to;
                break;
            }
        }
    }

    return 0;
}
