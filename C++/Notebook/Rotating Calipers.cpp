// <3
// Tema: Geometry / Rotating Calipers (Par Mas Lejano)
// Resumen: Par de puntos mas lejano (diametro del conjunto) en O(n log n)
// O: (n log n) el hull, (n) el diametro
// Uso: h = convexHull(p); diameter(h) -> {dist^2, {P,Q}}  // dist^2, no dist
// Detalle: Par de puntos mas lejano (diametro del conjunto) en O(n log n). El par optimo
// siempre son dos vertices del casco convexo, asi que se arma el casco y se recorre con dos
// punteros: para cada arista (i, i+1) se avanza j mientras el triangulo (i, i+1, j) crezca en
// area. Donde deja de crecer, j es el vertice mas lejano a la recta de esa arista (su
// antipodal). Como j solo avanza y da a lo sumo una vuelta, el recorrido cuesta O(n). Detalle
// que la version ingenua olvida: el antipodal se mide contra LOS DOS extremos de la arista (i e
// i+1); medir solo contra i puede perder el par optimo. Todo en enteros con distancia AL
// CUADRADO: exacto, sin sqrt ni EPS (coordenadas hasta ~1e9 para que no desborde long long). El
// casco sale sin repetidos ni colineales, que es lo que necesita el while (con colineales el
// area deja de ser estrictamente unimodal). Casos borde: un solo punto distinto -> 0; todos
// colineales -> el casco tiene 2 puntos. El mismo recorrido de antipodales resuelve: ancho
// minimo del conjunto (minimo, sobre las aristas, de la distancia a su antipodal), rectangulo
// de area minima que lo cubre y distancia entre dos poligonos convexos.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct P
{
    ll x, y;
    bool operator<(const P &o) const { return x != o.x ? x < o.x : y < o.y; }
    bool operator==(const P &o) const { return x == o.x && y == o.y; }
};

P operator-(P a, P b) { return {a.x - b.x, a.y - b.y}; }
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll cross(P o, P a, P b) { return cross(a - o, b - o); }
ll dist2(P a, P b)
{
    P d = a - b;
    return d.x * d.x + d.y * d.y;
}

// Monotone chain: casco en sentido antihorario, sin repetidos ni colineales
vector<P> convexHull(vector<P> p)
{
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    if (n <= 2) return p;

    vector<P> h(2 * n);
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, lo = k + 1; i >= 0; i--)
    {
        while (k >= lo && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k - 1);
    return h;
}

// {distancia^2 maxima, par de puntos}. h = casco antihorario (el de convexHull)
pair<ll, pair<P, P>> diameter(const vector<P> &h)
{
    int n = h.size();
    if (n == 1) return {0, {h[0], h[0]}};
    if (n == 2) return {dist2(h[0], h[1]), {h[0], h[1]}};

    ll best = -1;
    P a = h[0], b = h[0];
    for (int i = 0, j = 1; i < n; i++)
    {
        int ni = (i + 1) % n;
        // avanzar j mientras el area del triangulo (i, ni, j) siga creciendo
        while (cross(h[i], h[ni], h[(j + 1) % n]) > cross(h[i], h[ni], h[j])) j = (j + 1) % n;

        if (dist2(h[i], h[j]) > best)
        {
            best = dist2(h[i], h[j]);
            a = h[i];
            b = h[j];
        }
        if (dist2(h[ni], h[j]) > best)
        {
            best = dist2(h[ni], h[j]);
            a = h[ni];
            b = h[j];
        }
    }
    return {best, {a, b}};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<P> p(n);
    for (auto &q : p) cin >> q.x >> q.y;

    auto r = diameter(convexHull(p));

    cout << r.first << "\n";  // distancia al cuadrado (exacta)
    cout << fixed << setprecision(6) << sqrt((double)r.first) << "\n";
    cout << r.second.first.x << " " << r.second.first.y << " "
         << r.second.second.x << " " << r.second.second.y << "\n";
    return 0;
}
