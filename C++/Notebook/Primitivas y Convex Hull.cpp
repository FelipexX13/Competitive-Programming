// <3
// Tema: Geometry / Primitivas y Convex Hull
// O: (n log n) el hull, (1) las primitivas
// Uso: cross(a,b,c)>0 izquierda; convexHull(p) antihorario; polygonArea(P)
// Base de todo problema geometrico: struct Pt con operadores, producto punto y producto cruz.
// El cruz es la herramienta central: su signo dice si tres puntos giran a la izquierda,
// a la derecha o son colineales, y con eso se resuelve casi todo. Nunca comparar doubles con
// == : usar sgn() con EPS.
// Incluye interseccion de segmentos (dos pruebas de orientacion opuesta, mas los casos
// degenerados colineales via onSeg), convex hull por monotone chain en O(n log n) (ordena por
// coordenada y arma la cadena inferior y la superior descartando giros no convexos), y area
// de poligono simple por la formula del cordon (shoelace), que vale para cualquier poligono
// cerrado sin auto-intersecciones y devuelve el doble del area en valor absoluto entre dos.

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

int sgn(double x)
{
    return (x > EPS) - (x < -EPS);
}

struct Pt
{
    double x, y;
    Pt() {}
    Pt(double x, double y) : x(x), y(y) {}
    Pt operator+(const Pt &o) const { return Pt(x + o.x, y + o.y); }
    Pt operator-(const Pt &o) const { return Pt(x - o.x, y - o.y); }
    Pt operator*(double k) const { return Pt(x * k, y * k); }
};

double dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
double cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
double cross(Pt a, Pt b, Pt c) { return cross(b - a, c - a); }

// p esta sobre el segmento a-b (asumiendo colinealidad)
bool onSeg(Pt a, Pt b, Pt p)
{
    return sgn(cross(a, b, p)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

bool segIntersect(Pt a, Pt b, Pt c, Pt d)
{
    int o1 = sgn(cross(a, b, c)), o2 = sgn(cross(a, b, d));
    int o3 = sgn(cross(c, d, a)), o4 = sgn(cross(c, d, b));
    if (o1 * o2 < 0 && o3 * o4 < 0) return true;
    return onSeg(a, b, c) || onSeg(a, b, d) || onSeg(c, d, a) || onSeg(c, d, b);
}

// Monotone chain: devuelve el casco convexo en sentido antihorario
vector<Pt> convexHull(vector<Pt> p)
{
    sort(p.begin(), p.end(), [](const Pt &a, const Pt &b){
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });

    vector<Pt> lo, up;
    for (auto &pt : p)
    {
        while (lo.size() >= 2 && sgn(cross(lo[lo.size() - 2], lo.back(), pt)) <= 0)
        {
            lo.pop_back();
        }
        lo.push_back(pt);
    }
    for (int i = (int)p.size() - 1; i >= 0; --i)
    {
        Pt pt = p[i];
        while (up.size() >= 2 && sgn(cross(up[up.size() - 2], up.back(), pt)) <= 0)
        {
            up.pop_back();
        }
        up.push_back(pt);
    }

    lo.pop_back();
    up.pop_back();
    lo.insert(lo.end(), up.begin(), up.end());
    return lo;
}

// Formula del cordon (shoelace) para poligono simple
double polygonArea(const vector<Pt> &P)
{
    long double s = 0;
    int n = P.size();
    for (int i = 0; i < n; i++)
    {
        s += (long double)P[i].x * P[(i + 1) % n].y - (long double)P[i].y * P[(i + 1) % n].x;
    }
    return fabs((double)s) * 0.5;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
