// <3
// Tema: CSES / Descenso por el Suffix Automaton (con Repetidas)
// O: (26*n) construir y bajar
// Uso: dp[v] suma occ de los hijos; cada subcadena pesa cuantas veces aparece
// La k-esima subcadena en orden alfabetico, pero contando las REPETIDAS tantas veces como
// aparecen.
// Es el Substring Order I con un cambio de peso: en la version I cada subcadena distinta vale 1,
// aqui vale occ, o sea cuantas veces aparece en la cadena. Por eso primero se propagan las
// ocurrencias por los suffix links (calculateOccurrences) y el dp suma occ[to] + dp[to] en vez de
// 1 + dp[to].
// Al bajar hay que restar occ[to] antes de seguir, que son las apariciones del prefijo actual
// exacto; si k cae dentro de esas, la respuesta es justo lo que se lleva escrito.
// Comparar este archivo con el de la version I es la mejor forma de ver que un suffix automaton
// responde muchas preguntas distintas cambiando solo el peso del dp.

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
        ll occ;

        State()
        {
            fill(next, next + 26, -1);
            link = -1;
            len = 0;
            occ = 0;
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
        st[cur].occ = 1;

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
                st[clone].occ = 0;

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

vector<int> buildOrder(SuffixAutomaton &sam, int n)
{
    int sz = sam.st.size();

    vector<int> cnt(n + 1);

    for(auto &v : sam.st)
        cnt[v.len]++;

    for(int i = 1; i <= n; i++)
        cnt[i] += cnt[i - 1];

    vector<int> order(sz);

    for(int i = sz - 1; i >= 0; i--)
        order[--cnt[sam.st[i].len]] = i;

    return order;
}

void calculateOccurrences(SuffixAutomaton &sam, vector<int> &order)
{
    for(int i = (int)order.size() - 1; i > 0; i--)
    {
        int v = order[i];

        if(sam.st[v].link != -1)
        {
            sam.st[sam.st[v].link].occ += sam.st[v].occ;
        }
    }
}

vector<ll> calculateDP(SuffixAutomaton &sam, vector<int> &order)
{
    int sz = sam.st.size();

    vector<ll> dp(sz, 0);

    for(int i = sz - 1; i >= 0; i--)
    {
        int v = order[i];

        for(int c = 0; c < 26; c++)
        {
            int to = sam.st[v].next[c];

            if(to == -1)
                continue;

            dp[v] += sam.st[to].occ;
            dp[v] += dp[to];
        }
    }

    return dp;
}

string kthSubstring(SuffixAutomaton &sam, vector<ll> &dp, ll k)
{
    string ans;
    int v = 0;

    while(true)
    {
        for(int c = 0; c < 26; c++)
        {
            int to = sam.st[v].next[c];

            if(to == -1)
                continue;

            // Todo el bloque que empieza con esta letra
            ll block = sam.st[to].occ + dp[to];

            if(k > block)
            {
                k -= block;
                continue;
            }

            // La respuesta puede ser exactamente ans + c
            if(k <= sam.st[to].occ)
            {
                ans.push_back(char('a' + c));
                return ans;
            }

            // Saltamos las ocurrencias del propio prefijo
            k -= sam.st[to].occ;

            ans.push_back(char('a' + c));
            v = to;

            break;
        }
    }
}

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

    vector<int> order = buildOrder(sam, s.size());

    calculateOccurrences(sam, order);

    vector<ll> dp = calculateDP(sam, order);

    cout << kthSubstring(sam, dp, k) << '\n';

    return 0;
}
