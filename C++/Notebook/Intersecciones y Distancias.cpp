// <3
// Tema: Geometry / Intersecciones, Distancias y Par Mas Cercano
// Resumen: El PUNTO de corte de rectas, segmentos y circulos; distancias; punto en poligono
// O: (1) cada primitiva, (n) inPolygon, (n log n) closestPair
// Uso: inPolygon(P,q): 1 dentro, 0 borde, -1 fuera; circleInter da 0, 1 o 2 puntos
// Detalle: Complementa "Primitivas y Convex Hull": usa el mismo Pt, sgn, dot y cross (si ya
// los copiaste de alla, no los repitas). Alla segIntersect solo dice SI se cortan; aqui
// salen los puntos.
// lineInter: corte de las rectas AB y CD; si son paralelas divide por cero, asi que antes
// chequear sgn(cross(b-a, d-c)) != 0. segInterPoint devuelve false si son paralelas o
// colineales aunque se solapen (para eso, segIntersect de Primitivas).
// inPolygon vale para cualquier poligono simple, concavo o no, sin importar el sentido:
// rayo hacia la derecha contando cruces, sin divisiones (el lado se decide con cross).
// circleInter con circulos IDENTICOS devuelve vacio aunque haya infinitos puntos.
// closestPair: barrido por x con un multiset ordenado por y; cada punto solo compara con
// los que caen en la franja [y-d, y+d], que son O(1). Devuelve la distancia.
// Todo en double con EPS = 1e-9. Si las coordenadas son enteras y la respuesta tambien
// (cruces, orientaciones), mejor long long con cross exacto y sin EPS.

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

int sgn(double x) { return (x > EPS) - (x < -EPS); }

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
double len(Pt a) { return sqrt(dot(a, a)); }

bool onSeg(Pt a, Pt b, Pt p)
{
    return sgn(cross(a, b, p)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

// Proyeccion de p sobre la recta ab
Pt proyeccion(Pt p, Pt a, Pt b)
{
    Pt d = b - a;
    return a + d * (dot(p - a, d) / dot(d, d));
}

double distLine(Pt p, Pt a, Pt b) { return fabs(cross(a, b, p)) / len(b - a); }

double distSeg(Pt p, Pt a, Pt b)
{
    if (sgn(dot(p - a, b - a)) <= 0) return len(p - a);
    if (sgn(dot(p - b, a - b)) <= 0) return len(p - b);
    return distLine(p, a, b);
}

// Corte de las RECTAS ab y cd. Precondicion: no paralelas
Pt lineInter(Pt a, Pt b, Pt c, Pt d)
{
    Pt r = b - a, s = d - c;
    return a + r * (cross(c - a, s) / cross(r, s));
}

// Corte de los SEGMENTOS ab y cd en un unico punto
bool segInterPoint(Pt a, Pt b, Pt c, Pt d, Pt &out)
{
    if (sgn(cross(b - a, d - c)) == 0) return false;   // paralelos o colineales
    out = lineInter(a, b, c, d);
    return onSeg(a, b, out) && onSeg(c, d, out);
}

// 1 dentro, 0 en el borde, -1 fuera. Poligono simple, concavo o convexo
int inPolygon(const vector<Pt> &P, Pt q)
{
    int n = P.size();
    bool dentro = false;
    for (int i = 0; i < n; i++)
    {
        Pt a = P[i], b = P[(i + 1) % n];
        if (onSeg(a, b, q)) return 0;
        if ((a.y > q.y) != (b.y > q.y))       // la arista cruza la horizontal de q
        {
            if ((cross(a, b, q) > 0) == (b.y > a.y)) dentro = !dentro;
        }
    }
    return dentro ? 1 : -1;
}

vector<Pt> circleInter(Pt c1, double r1, Pt c2, double r2)
{
    Pt d = c2 - c1;
    double D = len(d);
    if (sgn(D) == 0) return {};                        // concentricos
    if (sgn(D - (r1 + r2)) > 0 || sgn(D - fabs(r1 - r2)) < 0) return {};
    double a = (r1 * r1 - r2 * r2 + D * D) / (2 * D);
    Pt m = c1 + d * (a / D);
    // Tangencia por DISTANCIAS, no con sgn(h): en tangencia r1^2-a^2 da ~1e-14, la
    // raiz lo sube a ~1e-7 > EPS y salian 2 puntos casi iguales (13 fallos al probar)
    if (sgn(D - (r1 + r2)) == 0 || sgn(D - fabs(r1 - r2)) == 0) return {m};
    double h = sqrt(max(0.0, r1 * r1 - a * a));
    Pt per = Pt(-d.y, d.x) * (h / D);
    return {m + per, m - per};
}

// Recta ab contra el circulo (c, r)
vector<Pt> lineCircle(Pt a, Pt b, Pt c, double r)
{
    Pt p = proyeccion(c, a, b);
    double d = len(p - c);
    if (sgn(d - r) > 0) return {};
    if (sgn(d - r) == 0) return {p};                   // tangente (ver circleInter)
    double h = sqrt(max(0.0, r * r - d * d));
    Pt dir = (b - a) * (1.0 / len(b - a));
    return {p - dir * h, p + dir * h};
}

double closestPair(vector<Pt> p)
{
    sort(p.begin(), p.end(), [](const Pt &a, const Pt &b) { return a.x < b.x; });
    multiset<pair<double, double>> s;                  // (y, x) de los de la franja
    double best = 1e18;
    int j = 0;
    for (int i = 0; i < (int)p.size(); i++)
    {
        while (p[i].x - p[j].x > best)
        {
            s.erase(s.find({p[j].y, p[j].x}));
            j++;
        }
        auto it = s.lower_bound({p[i].y - best, -1e18});
        for (; it != s.end() && it->first <= p[i].y + best; ++it)
        {
            best = min(best, len(p[i] - Pt(it->second, it->first)));
        }
        s.insert({p[i].y, p[i].x});
    }
    return best;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
