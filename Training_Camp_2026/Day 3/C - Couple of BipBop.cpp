// <3
// Tema: String Algorithms / Suffix Array + LCP
// Resuelve "Couple of BipBop" (Maratona SBC de Programacao 2024, Problem C): Bob y Charlie
// empiezan a bailar cada uno en un verso aleatorio de una cancion de N versos y siguen la
// coreografia hasta desincronizarse o llegar al final de la cancion; hay que calcular el valor
// esperado de versos que bailaran en sincronia, expresado como fraccion irreducible P/Q, si
// ambos eligen su verso inicial de forma uniforme e independiente.
// El valor esperado equivale a sumar, sobre todos los pares de posiciones iniciales (i,j), el
// largo del prefijo comun de los sufijos que empiezan en i y en j. El codigo construye el suffix
// array (suffix_array) y el arreglo de LCP (kasai) de la secuencia de movimientos, y luego usa
// una pila monotona para sumar en O(N) la suma de minimos de LCP sobre todos los subarreglos
// (sumPairs), equivalente a la suma de LCP entre todos los pares de sufijos.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll gcdll(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

vector<int> suffix_array(vector<int> s) {
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rnk[i] = s[i];
    }

    for (int k = 1;; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rnk[a] != rnk[b])
                return rnk[a] < rnk[b];

            int ra = a + k < n ? rnk[a + k] : -1;
            int rb = b + k < n ? rnk[b + k] : -1;
            return ra < rb;
        };

        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;

        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i]);

        rnk = tmp;

        if (rnk[sa[n-1]] == n - 1)
            break;
    }

    return sa;
}

vector<int> kasai(vector<int> &s, vector<int> &sa) {
    int n = s.size();

    vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;

    vector<int> lcp(n - 1);

    int h = 0;

    for (int i = 0; i < n; i++) {
        int r = rank[i];

        if (r == n - 1)
            continue;

        int j = sa[r + 1];

        while (i + h < n && j + h < n && s[i+h] == s[j+h])
            h++;

        lcp[r] = h;

        if (h)
            h--;
    }

    return lcp;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> a(N);

    for (int i = 0; i < N; i++)
        cin >> a[i];

    auto sa = suffix_array(a);
    auto lcp = kasai(a, sa);


    // suma de LCP entre pares distintos
    ll sumPairs = 0;

    vector<pair<ll,ll>> st; 
    ll accumulated = 0;

    for (int i = 0; i < (int)lcp.size(); i++) {

        ll cnt = 1;
        ll val = lcp[i];

        while (!st.empty() && st.back().first >= val) {
            accumulated -= st.back().first * st.back().second;
            cnt += st.back().second;
            st.pop_back();
        }

        st.push_back({val, cnt});

        accumulated += val * cnt;

        sumPairs += accumulated;
    }


    ll numerator = 1LL * N * (N + 1) / 2 + 2 * sumPairs;
    ll denominator = 1LL * N * N;

    ll g = gcdll(numerator, denominator);

    cout << numerator / g << '/' << denominator / g << '\n';

    return 0;
}