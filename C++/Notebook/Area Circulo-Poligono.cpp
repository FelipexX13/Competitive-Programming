// <3
// Tema: Geometry / Area Circulo-Poligono
// Area de la interseccion entre un circulo y un poligono, usando el truco de sumar areas con
// signo arista por arista: se traslada todo para dejar el circulo en el origen y se recorre el
// poligono sumando triangleCircleArea de cada arista, de modo que las contribuciones de fuera
// se cancelan solas y al final basta el valor absoluto. Funciona con el poligono en cualquier
// orientacion y sin importar si el circulo queda dentro, fuera o a medias.
// Para cada arista p-q se resuelve |p + t*d|^2 = r^2, una cuadratica en t, para hallar donde
// corta la circunferencia; esos cortes parten el segmento en tramos. Cada tramo se clasifica
// mirando su punto medio: si cae dentro del circulo aporta el area del triangulo (cross/2), y
// si cae fuera aporta la del sector circular (r^2*angulo/2, con atan2 para quedarse con el
// angulo con signo correcto).
// Aqui se usa con un rectangulo [0,w]x[0,h] para calcular la probabilidad de que un punto
// uniforme caiga dentro del circulo, y con eso el valor esperado de la suma de los v.

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;

struct Pt { double x, y; };

double cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
double dot(Pt a, Pt b)   { return a.x * b.x + a.y * b.y; }
Pt sub(Pt a, Pt b)       { return {a.x - b.x, a.y - b.y}; }
Pt add(Pt a, Pt b)       { return {a.x + b.x, a.y + b.y}; }
Pt mul(Pt a, double t)   { return {a.x * t, a.y * t}; }
double norm2(Pt a)       { return dot(a, a); }

// Area con signo de la interseccion entre el circulo centrado en (0,0) de radio r
// y el triangulo (0,0)-p-q.
double triangleCircleArea(Pt p, Pt q, double r) {
    Pt d = sub(q, p);

    // |p + t*d|^2 = r^2  ->  A t^2 + B t + C = 0
    double A = norm2(d);
    double B = 2.0 * dot(p, d);
    double C = norm2(p) - r * r;

    vector<double> cuts = {0.0, 1.0};

    if (A > EPS) {
        double disc = B * B - 4.0 * A * C;
        if (disc > EPS) {
            double s = sqrt(disc);
            double t1 = (-B - s) / (2.0 * A);
            double t2 = (-B + s) / (2.0 * A);
            if (t1 > EPS && t1 < 1.0 - EPS) cuts.push_back(t1);
            if (t2 > EPS && t2 < 1.0 - EPS) cuts.push_back(t2);
        }
    }

    sort(cuts.begin(), cuts.end());

    double ans = 0.0;
    for (size_t i = 0; i + 1 < cuts.size(); i++) {
        double l = cuts[i], rr = cuts[i + 1];
        double mid = (l + rr) / 2.0;

        Pt a = add(p, mul(d, l));
        Pt b = add(p, mul(d, rr));
        Pt m = add(p, mul(d, mid));

        if (norm2(m) <= r * r) {
            ans += cross(a, b) / 2.0;           // tramo dentro: triangulo
        } else {
            ans += r * r * atan2(cross(a, b), dot(a, b)) / 2.0;  // tramo fuera: sector
        }
    }
    return ans;
}

double circleRectangleArea(double cx, double cy, double r, double w, double h) {
    // Trasladar para que el circulo quede en el origen.
    Pt rect[4] = {{-cx, -cy}, {w - cx, -cy}, {w - cx, h - cy}, {-cx, h - cy}};

    double area = 0.0;
    for (int i = 0; i < 4; i++) area += triangleCircleArea(rect[i], rect[(i + 1) % 4], r);
    return fabs(area);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double r, w, h;
    cin >> n >> r >> w >> h;

    double ans = 0.0;
    for (int i = 0; i < n; i++) {
        double x, y, v;
        cin >> x >> y >> v;
        ans += v * circleRectangleArea(x, y, r, w, h) / (w * h);
    }

    cout << fixed << setprecision(15) << ans << "\n";
    return 0;
}
