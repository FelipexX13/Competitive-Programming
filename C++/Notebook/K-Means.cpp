// <3
// Tema: Geometry / K-Means (Clustering)
// Agrupa n puntos (de cualquier dimension d) en k clusters minimizando el SSE: la suma de las
// distancias al cuadrado de cada punto al centroide de su cluster.
// Algoritmo de Lloyd: (1) asignar cada punto al centroide mas cercano, (2) mover cada
// centroide al promedio de sus puntos, y repetir hasta que ninguna asignacion cambie. Cada
// paso solo puede bajar el SSE, asi que siempre converge, pero a un optimo LOCAL que depende
// de los centroides iniciales. Por eso se siembra con k-means++ (cada centroide nuevo sale con
// probabilidad proporcional a su distancia^2 al centroide mas cercano, lo que los reparte) y
// se corre con varias semillas quedandose con el menor SSE.
// Lo que rompe la version ingenua: (a) un cluster puede quedar vacio y su promedio no existe;
// aqui se re-siembra en el punto que peor encaja; (b) sin tope de iteraciones no hay cota
// practica de tiempo. Costo: O(reinicios * iteraciones * n * k * d).
// OJO: el optimo exacto es NP-hard. Si el problema es 1D y pide el optimo, ordenar y hacer DP
// de particion en segmentos contiguos (O(k n^2), o menos con Divide and Conquer Optimization).

#include <bits/stdc++.h>

using namespace std;

typedef vector<double> Vec;

double dist2(const Vec &a, const Vec &b)
{
    double s = 0;
    for (size_t t = 0; t < a.size(); t++) s += (a[t] - b[t]) * (a[t] - b[t]);
    return s;
}

struct KMeans
{
    vector<Vec> c;      // centroides
    vector<int> label;  // cluster de cada punto
    double sse;         // suma de distancias^2 de cada punto a su centroide
};

// Centroide mas cercano a x (en empate, el de menor indice)
int nearest(const Vec &x, const vector<Vec> &c)
{
    int best = 0;
    double bd = dist2(x, c[0]);
    for (int j = 1; j < (int)c.size(); j++)
    {
        double d = dist2(x, c[j]);
        if (d < bd)
        {
            bd = d;
            best = j;
        }
    }
    return best;
}

KMeans kmeansOnce(const vector<Vec> &p, int k, mt19937 &rng, int maxIter)
{
    int n = p.size(), d = p[0].size();

    // Semilla k-means++
    vector<Vec> c(1, p[uniform_int_distribution<int>(0, n - 1)(rng)]);
    vector<double> md(n, 1e300);  // distancia^2 al centroide elegido mas cercano
    while ((int)c.size() < k)
    {
        double total = 0;
        for (int i = 0; i < n; i++)
        {
            md[i] = min(md[i], dist2(p[i], c.back()));
            total += md[i];
        }
        int pick = n - 1;
        if (total > 0)
        {
            double r = uniform_real_distribution<double>(0, total)(rng);
            for (int i = 0; i < n; i++)
            {
                r -= md[i];
                if (r <= 0)
                {
                    pick = i;
                    break;
                }
            }
        }
        else pick = uniform_int_distribution<int>(0, n - 1)(rng);  // todos repetidos
        c.push_back(p[pick]);
    }

    // Lloyd
    vector<int> label(n, -1);
    for (int it = 0; it < maxIter; it++)
    {
        bool changed = false;
        for (int i = 0; i < n; i++)
        {
            int j = nearest(p[i], c);
            if (j != label[i])
            {
                label[i] = j;
                changed = true;
            }
        }
        if (!changed) break;

        vector<Vec> sum(k, Vec(d, 0.0));
        vector<int> cnt(k, 0);
        for (int i = 0; i < n; i++)
        {
            cnt[label[i]]++;
            for (int t = 0; t < d; t++) sum[label[i]][t] += p[i][t];
        }

        // Para re-sembrar un cluster vacio: el punto mas lejano a su centroide actual
        vector<double> err(n);
        for (int i = 0; i < n; i++) err[i] = dist2(p[i], c[label[i]]);

        for (int j = 0; j < k; j++)
        {
            if (cnt[j] > 0)
            {
                for (int t = 0; t < d; t++) c[j][t] = sum[j][t] / cnt[j];
            }
            else
            {
                int far = max_element(err.begin(), err.end()) - err.begin();
                c[j] = p[far];
                err[far] = -1;  // que otro cluster vacio no tome el mismo punto
            }
        }
    }

    KMeans res;
    res.c = c;
    res.label.assign(n, 0);
    res.sse = 0;
    for (int i = 0; i < n; i++)
    {
        res.label[i] = nearest(p[i], c);
        res.sse += dist2(p[i], c[res.label[i]]);
    }
    return res;
}

// Mejor de `restarts` corridas. Semilla fija: resultado reproducible
KMeans kmeans(const vector<Vec> &p, int k, int restarts = 10, int maxIter = 300,
              unsigned seed = 7)
{
    k = max(1, min(k, (int)p.size()));
    mt19937 rng(seed);
    KMeans best;
    best.sse = numeric_limits<double>::infinity();
    for (int r = 0; r < restarts; r++)
    {
        KMeans cur = kmeansOnce(p, k, rng, maxIter);
        if (cur.sse < best.sse) best = cur;
    }
    return best;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, d;
    cin >> n >> k >> d;
    vector<Vec> p(n, Vec(d));
    for (auto &x : p)
        for (auto &v : x) cin >> v;

    KMeans r = kmeans(p, k);

    cout << fixed << setprecision(6) << r.sse << "\n";
    for (auto &cc : r.c)
    {
        for (int t = 0; t < d; t++) cout << cc[t] << (t + 1 < d ? ' ' : '\n');
    }
    for (int i = 0; i < n; i++) cout << r.label[i] << (i + 1 < n ? ' ' : '\n');
    return 0;
}
