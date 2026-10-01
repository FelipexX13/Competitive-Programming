// <3
// Tema: CSES / Suffix Automaton (Contar Distintas)
// Resumen: Cuantas subcadenas distintas tiene la cadena
// O: (n) estados y transiciones, con alfabeto fijo
// Uso: sam.add(c) por letra; sam.countDistinct()
// Detalle: Cuantas subcadenas DISTINTAS tiene la cadena. El suffix automaton es el automata
// minimo que acepta todos los sufijos, y tiene a lo sumo 2n estados y 3n transiciones, por eso
// se reserva 2*n. Cada estado representa un conjunto de subcadenas que terminan en las mismas
// posiciones, y esas subcadenas son exactamente los largos del intervalo (len[link] + 1 ..
// len[v]). Entonces la respuesta es sumar len[v] - len[link[v]] sobre todos los estados menos
// la raiz. Una linea, una vez construido el automata. EL CLONE ES TODO EL TRUCO de la
// construccion: cuando el estado q al que se llega es mas largo de lo que corresponde, se parte
// en dos para que cada estado siga representando un rango limpio de largos. Si se omite, el
// automata deja de ser minimo y las cuentas se caen. CUANDO USAR: cualquier pregunta sobre
// TODAS las subcadenas. Para sufijos ordenados, suffix array; para subcadenas como conjunto,
// suffix automaton.

#include <bits/stdc++.h>
using namespace std;

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

    void add(char c)
    {
        int x = c - 'a';

        int cur = st.size();
        st.push_back(State());

        st[cur].len = st[last].len + 1;

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

    long long countDistinct()
    {
        long long ans = 0;

        for(int v = 1; v < (int)st.size(); v++)
        {
            ans += st[v].len - st[st[v].link].len;
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    SuffixAutomaton sam(s.size());

    for(char c : s)
    {
        sam.add(c);
    }

    cout << sam.countDistinct() << '\n';

    return 0;
}
