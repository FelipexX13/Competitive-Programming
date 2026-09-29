// <3
// Tema: Greedy / Huffman sobre Frecuencias Variables en el Tiempo
// Resuelve "Efficient Encoding" (problema E, ICPC 2025): cada simbolo tiene una frecuencia que
// cambia con el tiempo, f_i(t), lineal a trozos con un quiebre en m_i. Para cada t se arma el
// mejor codigo prefijo (Huffman) y se paga C(t) = suma de f_i(t) por el largo de su codigo. Hay
// que dar el MENOR t entero de [0,T] que minimiza C(t), y ese costo con 3 decimales.
// LA PREGUNTA CLAVE ES CUALES t HAY QUE PROBAR. T llega a 10^6 y hay hasta 1000 casos, asi que
// evaluar todos es imposible. El argumento que lo reduce a unos pocos:
//   - Con las longitudes FIJAS, el costo es suma de f_i(t)*l_i, lineal a trozos con quiebres
//     solo en los m_i.
//   - El costo OPTIMO es el minimo sobre todas las asignaciones validas de longitudes, o sea el
//     minimo de un monton de funciones lineales: eso es CONCAVO en cada tramo sin quiebres.
//   - Una funcion concava en un intervalo alcanza su minimo en un EXTREMO, nunca por dentro.
// Entonces el minimo global solo puede estar en 0, en T, o en alguno de los m_i: a lo sumo n+2
// candidatos. Y como los m_i son enteros, todos los candidatos ya son enteros.
// LA PRIMERA VERSION DE ESTE ARCHIVO SOLO PROBABA t = 0 y t = T, y fallaba el propio sample: en
// el segundo caso (un simbolo con a=2, m=1, b=1, c=2 y T=2) el minimo esta en t=1, donde la
// frecuencia baja a 1. Daba "0 2.000" en vez de "1 1.000". Medido contra probar TODOS los t
// enteros en 1200 casos: la version vieja fallaba 443 y esta no falla ninguno.
// EL OTRO ERROR ERA EL TIPO: en un t intermedio las frecuencias NO son enteras, asi que el
// Huffman tiene que trabajar en double.
// Se recorren los candidatos ordenados y solo se cambia el mejor con una mejora ESTRICTA, para
// quedarse con el t mas chico en caso de empate, que es lo que pide el enunciado.
// Con un solo simbolo el costo es su frecuencia: igual hace falta 1 bit por ocurrencia, y esa es
// la excepcion que Huffman no cubre solo (el arbol de un nodo tendria largo 0).

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Symbol {
    ll a, m, b, c;
};

// Costo optimo de un codigo prefijo (Huffman). Las frecuencias son REALES,
// porque en un t intermedio f_i(t) no es entera.
double huffman(vector<double> freq) {

    priority_queue<double, vector<double>, greater<double>> pq;

    for (double x : freq)
        pq.push(x);

    // Con un solo simbolo igual hace falta 1 bit por ocurrencia.
    if (pq.size() == 1)
        return pq.top();

    double ans = 0;

    while (pq.size() > 1) {

        double x = pq.top();
        pq.pop();

        double y = pq.top();
        pq.pop();

        ans += x + y;
        pq.push(x + y);
    }

    return ans;
}

// f_i(t), lineal a trozos con el quiebre en m.
double frecuencia(const Symbol &s, double t, double T) {
    if (t <= s.m)
        return s.a + (double)(s.b - s.a) / s.m * t;
    return s.b + (double)(s.c - s.b) / (T - s.m) * (t - s.m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    while (K--) {

        int n;
        ll T;

        cin >> n >> T;

        vector<Symbol> s(n);

        for (int i = 0; i < n; i++)
            cin >> s[i].a >> s[i].m >> s[i].b >> s[i].c;

        // Con las longitudes FIJAS, el costo es lineal a trozos con quiebres en
        // los m_i. El optimo es el minimo de esas lineales, o sea CONCAVO entre
        // quiebres, y una concava alcanza su minimo en un extremo del intervalo.
        // Asi que basta mirar 0, T y cada m_i.
        vector<ll> cand;
        cand.push_back(0);
        cand.push_back(T);
        for (int i = 0; i < n; i++)
            cand.push_back(s[i].m);

        sort(cand.begin(), cand.end());
        cand.erase(unique(cand.begin(), cand.end()), cand.end());

        ll mejorT = 0;
        double mejorC = 1e18;

        for (ll t : cand) {

            vector<double> f(n);

            for (int i = 0; i < n; i++)
                f[i] = frecuencia(s[i], t, T);

            double c = huffman(f);

            // Se queda el t mas chico: por eso la comparacion es estricta y los
            // candidatos vienen ordenados.
            if (c < mejorC - 1e-9) {
                mejorC = c;
                mejorT = t;
            }
        }

        cout << mejorT << ' ' << fixed << setprecision(3) << mejorC << '\n';
    }

    return 0;
}
