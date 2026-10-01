// <3
// Tema: String / KMP sobre Cadena Recursiva (Duplicacion)
// Resumen: Hay n+1 canciones definidas por s_{i+1} = s_i + t[i] + s_i
// O: (|t| + |s| * log k), KMP sobre la cadena que se duplica
// Detalle: Resuelve "Song of the Sirens" (Codeforces, problema G): hay n+1 canciones definidas
// por s_{i+1} = s_i + t[i] + s_i, y cada consulta pide cuantas veces aparece un nombre w dentro
// de s_k, modulo 1e9+7. La cadena crece al doble en cada paso, asi que s_n puede medir 2^100000
// y construirla esta descartado de entrada. LA RECURRENCIA ES TODO: f(i+1) = 2*f(i) + g(t[i])
// Las apariciones de w en s_{i+1} son las de la copia izquierda, las de la derecha (de ahi el
// 2*f(i)) y las que CRUZAN el caracter del medio. Esas ultimas son g. POR QUE g SOLO DEPENDE DE
// LA LETRA Y NO DE LA POSICION, que es el paso que hay que ver: una aparicion que cruza el
// centro tiene largo m, asi que no puede meterse mas de m-1 caracteres hacia cada lado. O sea
// que solo depende del SUFIJO de largo m-1 de s_i, de la letra del medio, y del PREFIJO de
// largo m-1 de s_i. Y como s_{i+1} empieza y termina con s_i, esos prefijos y sufijos YA NO
// CAMBIAN en cuanto |s_i| >= m-1. Entonces g se calcula una sola vez para cada una de las 26
// letras, contando apariciones de w en (sufijo + letra + prefijo). Por eso primero se hace
// crecer cur = s_k hasta que mida al menos m. Como se duplica cada vez, eso son a lo sumo unos
// 20 pasos con |w| hasta 10^6, no n pasos. DESENROLLANDO la recurrencia desde ese punto k: f(n)
// = f(k) * 2^(n-k) + suma desde i=k+1 hasta n de g(t[i-1]) * 2^(n-i) Esa suma tiene hasta n
// terminos, y con q consultas seria O(n*q) = 10^10. El truco para bajarla: como 2^(n-j-1) =
// 2^(n-1) * 2^(-j), se saca el 2^(n-1) afuera y lo que queda, suma de 2^(-j) sobre las
// posiciones j donde t[j] es la letra c, se precalcula UNA vez en prefijos por letra. Asi cada
// consulta cuesta O(26) en esa parte en vez de O(n). INV2 = 500000004 es el inverso de 2 modulo
// 1e9+7, que sale de (MOD+1)/2 y evita tener que llamar a una exponenciacion modular. Los
// 2^(-j) son potencias de ese inverso. DETALLES DEL KMP: despues de un match se hace j =
// pi[j-1] en vez de j = 0, que es lo que permite contar apariciones SOLAPADAS (con w = "aa" en
// "aaa" hay dos, no una). Y el mismo arreglo pi se reusa para el conteo en cur y para los 26
// strings de g, que por eso se pasa como parametro en vez de recalcularlo. Los limites cuadran
// porque la suma de todos los |w| no pasa de 10^6: cur mide ~2m y cada uno de los 26 strings de
// g mide 2m-1, asi que el trabajo por consulta es O(m) veces una constante. Si al terminar de
// crecer todavia |cur| < m, es que ni s_n alcanza el largo de w y la respuesta es 0. Este
// archivo entro al cuaderno sin la verificacion habitual, a pedido: ya venia aceptado.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;
const ll INV2 = 500000004;

vector<int> build_pi(const string& p) {
    int m = p.size();
    vector<int> pi(m);

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];

        while (j > 0 && p[i] != p[j])
            j = pi[j - 1];

        if (p[i] == p[j])
            j++;

        pi[i] = j;
    }

    return pi;
}

ll count_occ(const string& s, const string& p, const vector<int>& pi) {
    int j = 0;
    ll ans = 0;

    for (char c : s) {
        while (j > 0 && c != p[j])
            j = pi[j - 1];

        if (c == p[j])
            j++;

        if (j == (int)p.size()) {
            ans++;
            j = pi[j - 1];
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    string s0, t;
    cin >> s0 >> t;

    // pow2[i] = 2^i
    // invpow2[i] = 2^(-i)
    vector<ll> pow2(N + 1), invpow2(N + 1);

    pow2[0] = 1;
    invpow2[0] = 1;

    for (int i = 1; i <= N; i++) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
        invpow2[i] = invpow2[i - 1] * INV2 % MOD;
    }

    /*
        pref[c][i] =
        suma de 2^(-j) para j < i donde t[j] == c
    */

    vector<vector<ll>> pref(26, vector<ll>(N + 1));

    for (int c = 0; c < 26; c++) {
        for (int i = 0; i < N; i++) {
            pref[c][i + 1] = pref[c][i];

            if (t[i] - 'a' == c)
                pref[c][i + 1] =
                    (pref[c][i + 1] + invpow2[i]) % MOD;
        }
    }

    while (Q--) {
        int n;
        string w;

        cin >> n >> w;

        int m = w.size();

        vector<int> pi = build_pi(w);

        /*
            Construimos s_k hasta que:

                |s_k| >= |w|

            o hasta llegar a s_n si n es menor.
        */

        string cur = s0;

        int k = 0;

        while (k < n && (int)cur.size() < m) {
            cur = cur + t[k] + cur;
            k++;
        }

        /*
            Si todavia |cur| < |w|, entonces estamos en s_n
            y simplemente hacemos KMP directamente.
        */

        if ((int)cur.size() < m) {
            cout << 0 << '\n';
            continue;
        }

        /*
            cur = s_k
        */

        ll base = count_occ(cur, w, pi);

        /*
            Si k == n, ya tenemos exactamente s_n.
        */

        if (k == n) {
            cout << base % MOD << '\n';
            continue;
        }

        /*
            Para calcular g(c):

            suffix(|w|-1) + c + prefix(|w|-1)

            Todas las apariciones de w en este string
            contienen obligatoriamente el caracter central c.
        */

        string prefix = cur.substr(0, m - 1);
        string suffix = cur.substr(cur.size() - (m - 1), m - 1);

        vector<ll> g(26);

        for (int c = 0; c < 26; c++) {
            string x;
            x.reserve(2 * m - 1);

            x += suffix;
            x += char('a' + c);
            x += prefix;

            g[c] = count_occ(x, w, pi);
        }

        /*
            f(n,w) =
                f(k,w) * 2^(n-k)
                +
                sum_{i=k+1}^n g(i,w) * 2^(n-i)

            Como g(i,w) depende unicamente de t[i-1]:

                g(i,w) = g[t[i-1]]
        */

        ll ans = base * pow2[n - k] % MOD;

        /*
            Queremos:

            sum_{j=k}^{n-1}
                g[t[j]] * 2^(n-j-1)

            = 2^(n-1) *
              sum_{j=k}^{n-1}
                g[t[j]] * 2^(-j)
        */

        ll sum = 0;

        for (int c = 0; c < 26; c++) {
            ll x = (pref[c][n] - pref[c][k] + MOD) % MOD;
            sum = (sum + g[c] * x) % MOD;
        }

        ans = (ans + sum * pow2[n - 1]) % MOD;

        cout << ans << '\n';
    }

    return 0;
}
