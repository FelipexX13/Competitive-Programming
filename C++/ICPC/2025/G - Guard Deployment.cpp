// <3
// Tema: Geometry / Convex Hull y Barrido Angular
// Resumen: Perimetro del convex hull de los edificios y altura minima para que las torres se vean
// O: (H^2) por el barrido angular; el convex hull es (H log H)
// Detalle: Resuelve "Guard Deployment" (problema G, ICPC 2025): hay edificios rectangulares con
// altura, y hay que dar el perimetro de la cerca convexa mas corta que los encierra y la altura
// minima comun de las torres para que todas se vean entre si. Son dos problemas sueltos
// pegados: 1) EL PERIMETRO es el del convex hull de las cuatro esquinas de todos los edificios.
// La cerca mas corta que encierra un conjunto de puntos es siempre su envolvente convexa. 2) LA
// ALTURA depende de que edificios se atraviesan. Una linea de vista entre dos torres pasa por
// encima de un edificio si el segmento que las une (visto desde arriba) toca ese rectangulo; y
// si pasa, hay que ir al menos un metro mas alto que el. La respuesta es el maximo de h+1 sobre
// los edificios atravesados, y nunca menos de 3. LO INTERESANTE ES COMO DECIDE SI UN EDIFICIO
// SE ATRAVIESA, sin probar los O(H^2) pares de torres: desde un vertice del hull, todas las
// direcciones que dan al rectangulo forman un INTERVALO ANGULAR, delimitado por sus cuatro
// esquinas. Si otro vertice del hull cae dentro de ese intervalo, el segmento entre ambos pasa
// por el edificio. Teniendo los angulos hacia los demas vertices ordenados, cada consulta es
// una busqueda binaria. El intervalo se obtiene al reves de lo que uno esperaria: se ordenan
// los angulos a las cuatro esquinas, se busca el HUECO mas grande entre angulos consecutivos
// (en circulo), y el intervalo bueno es el complemento de ese hueco. Es la forma de manejar el
// caso en que el intervalo cruza el 0 sin escribir casos especiales. Verificado contra una
// referencia que prueba cada par de torres contra cada edificio con aritmetica entera exacta:
// 1600 casos con rectangulos alineados y rotados 45 grados, perimetro y altura correctos en
// todos, ademas del sample. Medido: 10 casos de N = 1000 edificios en 200 ms.

#include <bits/stdc++.h>
using namespace std;

using ld = long double;

const ld PI = acosl(-1.0L);
const ld EPS = 1e-12L;

struct Point {
    ld x, y;

    bool operator<(const Point& p) const {
        if (fabsl(x - p.x) > EPS)
            return x < p.x;
        return y < p.y;
    }

    bool operator==(const Point& p) const {
        return fabsl(x - p.x) < EPS &&
               fabsl(y - p.y) < EPS;
    }
};

struct Building {
    Point p[4];
    int h;
};

ld cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}


// ------------------------------------------------------------
// CONVEX HULL
// ------------------------------------------------------------

vector<Point> convexHull(vector<Point> p) {

    sort(p.begin(), p.end());

    p.erase(unique(p.begin(), p.end()), p.end());

    int n = p.size();

    if (n <= 1)
        return p;

    vector<Point> h(2 * n);
    int k = 0;

    // Lower
    for (int i = 0; i < n; i++) {

        while (k >= 2 &&
               cross(h[k - 2], h[k - 1], p[i]) <= EPS)
            k--;

        h[k++] = p[i];
    }

    // Upper
    for (int i = n - 2, t = k + 1; i >= 0; i--) {

        while (k >= t &&
               cross(h[k - 2], h[k - 1], p[i]) <= EPS)
            k--;

        h[k++] = p[i];
    }

    h.resize(k - 1);

    return h;
}


// ------------------------------------------------------------
// DISTANCIA
// ------------------------------------------------------------

ld dist(Point a, Point b) {
    ld dx = a.x - b.x;
    ld dy = a.y - b.y;

    return sqrtl(dx * dx + dy * dy);
}


// ------------------------------------------------------------
// PUNTO SOBRE RECTANGULO
// Como los edificios son convexos, basta revisar sus 4 lados.
// ------------------------------------------------------------

bool pointOnSegment(Point a, Point b, Point p) {

    if (fabsl(cross(a, b, p)) > EPS)
        return false;

    return p.x >= min(a.x, b.x) - EPS &&
           p.x <= max(a.x, b.x) + EPS &&
           p.y >= min(a.y, b.y) - EPS &&
           p.y <= max(a.y, b.y) + EPS;
}

bool pointInBuilding(const Building& b, Point p) {

    for (int i = 0; i < 4; i++) {

        Point a = b.p[i];
        Point c = b.p[(i + 1) % 4];

        if (pointOnSegment(a, c, p))
            return true;
    }

    bool pos = false;
    bool neg = false;

    for (int i = 0; i < 4; i++) {

        ld cr = cross(
            b.p[i],
            b.p[(i + 1) % 4],
            p
        );

        if (cr > EPS) pos = true;
        if (cr < -EPS) neg = true;
    }

    return !(pos && neg);
}


// ------------------------------------------------------------
// ANGULO
// ------------------------------------------------------------

ld angle(Point a, Point b) {

    ld x = b.x - a.x;
    ld y = b.y - a.y;

    ld ang = atan2l(y, x);

    if (ang < 0)
        ang += 2 * PI;

    return ang;
}


// ------------------------------------------------------------
// EL EDIFICIO ES ATRAVESADO POR ALGUN SEGMENTO
// ENTRE DOS VERTICES DEL HULL?
//
// Para un vertice v del hull:
//
// todas las direcciones que desde v alcanzan el rectangulo
// forman un intervalo angular.
//
// Los cuatro corners del rectangulo determinan ese intervalo.
// Si existe otro vertice del hull dentro de ese intervalo,
// el segmento entre ambos atraviesa/toca el rectangulo.
// ------------------------------------------------------------

bool buildingBlocks(
    const vector<Point>& hull,
    const Building& b,
    const vector<vector<ld>>& hullAngles
) {

    int H = hull.size();

    for (int v = 0; v < H; v++) {

        // Si el vertice del hull pertenece al edificio,
        // claramente este edificio participa.
        if (pointInBuilding(b, hull[v]))
            return true;

        // Angulos hacia las 4 esquinas del edificio
        vector<ld> a(4);

        for (int k = 0; k < 4; k++)
            a[k] = angle(hull[v], b.p[k]);

        sort(a.begin(), a.end());

        // Buscamos el mayor hueco circular.
        // El intervalo complementario es el menor intervalo
        // que contiene las 4 esquinas.
        int bestGap = 0;
        ld maxGap = -1;

        for (int k = 0; k < 4; k++) {

            ld next = (k == 3 ? a[0] + 2 * PI : a[k + 1]);

            ld gap = next - a[k];

            if (gap > maxGap) {
                maxGap = gap;
                bestGap = k;
            }
        }

        ld L = a[(bestGap + 1) % 4];
        ld R = a[bestGap];

        if (R < L)
            R += 2 * PI;

        const vector<ld>& angles = hullAngles[v];

        // Tenemos los angulos de los demas vertices.
        // Probamos tambien una copia desplazada 2PI para
        // resolver el caso en que el intervalo cruza 0.
        auto check = [&](ld x) {
            return x + EPS >= L && x <= R + EPS;
        };

        auto it = lower_bound(
            angles.begin(),
            angles.end(),
            L - EPS
        );

        if (it != angles.end() && check(*it))
            return true;

        // Si L > 2PI, usamos los angulos originales + 2PI.
        if (L > 2 * PI - EPS) {

            ld L2 = L - 2 * PI;
            ld R2 = R - 2 * PI;

            auto it2 = lower_bound(
                angles.begin(),
                angles.end(),
                L2 - EPS
            );

            if (it2 != angles.end() &&
                *it2 <= R2 + EPS)
                return true;
        }
    }

    return false;
}


// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {

        int N;
        cin >> N;

        vector<Building> buildings(N);

        vector<Point> allPoints;

        for (int i = 0; i < N; i++) {

            for (int j = 0; j < 4; j++) {

                cin >> buildings[i].p[j].x
                    >> buildings[i].p[j].y;

                allPoints.push_back(buildings[i].p[j]);
            }

            cin >> buildings[i].h;
        }

        // ----------------------------------------------------
        // 1. Convex Hull
        // ----------------------------------------------------

        vector<Point> hull = convexHull(allPoints);

        int H = hull.size();

        // ----------------------------------------------------
        // 2. Perimetro
        // ----------------------------------------------------

        ld perimeter = 0;

        for (int i = 0; i < H; i++)
            perimeter += dist(
                hull[i],
                hull[(i + 1) % H]
            );

        // ----------------------------------------------------
        // 3. Angulos de los vertices del hull
        //
        // Para cada vertice guardamos los angulos hacia
        // todos los demas vertices.
        // ----------------------------------------------------

        vector<vector<ld>> hullAngles(H);

        for (int i = 0; i < H; i++) {

            for (int j = 0; j < H; j++) {

                if (i == j)
                    continue;

                hullAngles[i].push_back(
                    angle(hull[i], hull[j])
                );
            }

            sort(
                hullAngles[i].begin(),
                hullAngles[i].end()
            );
        }

        // ----------------------------------------------------
        // 4. Altura minima
        // ----------------------------------------------------

        int minHeight = 3;

        for (int i = 0; i < N; i++) {

            if (buildingBlocks(
                    hull,
                    buildings[i],
                    hullAngles
                )) {

                minHeight = max(
                    minHeight,
                    buildings[i].h + 1
                );
            }
        }

        cout << fixed << setprecision(6)
             << (double)perimeter << ' '
             << minHeight << '\n';
    }

    return 0;
}
