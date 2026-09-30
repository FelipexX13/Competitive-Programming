// <3
// Tema: Geometry / Shoelace (Area de Poligono)
// O: (n)
// Uso: area2(p) = 2*area con signo; puntosInteriores(p) por Pick
// Area de CUALQUIER poligono simple en O(n), convexo o concavo, dando solo sus vertices en
// orden. Suma cruzada de cada arista con la siguiente: sum(x_i*y_{i+1} - x_{i+1}*y_i), y el
// area es la mitad del valor absoluto.
// El truco que importa en competencia es no dividir entre 2: se devuelve el DOBLE del area
// como long long, que con coordenadas enteras es exacto y evita por completo el punto
// flotante. Si el problema pide el area y puede ser .5, imprime a2/2 y a2%2 por separado, o
// multiplica todo por 2 desde el principio.
// El signo tambien sirve: positivo significa que los vertices vienen en sentido antihorario,
// negativo en sentido horario, asi que de paso detecta la orientacion gratis.
// Requisitos: los vertices deben ir en orden alrededor del poligono y el borde no puede
// cruzarse consigo mismo. No hace falta repetir el primer vertice al final.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct P { ll x, y; };

// Doble del area CON SIGNO. Exacto con coordenadas enteras.
// > 0 antihorario, < 0 horario, = 0 degenerado (todos colineales).
ll area2(const vector<P>& p) {
    ll s = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        s += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return s;
}

// Area de verdad. Solo aqui aparece el punto flotante.
double area(const vector<P>& p) {
    return llabs(area2(p)) / 2.0;
}

// Puntos de coordenadas enteras SOBRE el borde.
// Cada arista aporta gcd(|dx|, |dy|) puntos sin contar dos veces los vertices.
ll puntosBorde(const vector<P>& p) {
    ll b = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        b += __gcd(llabs(p[i].x - p[j].x), llabs(p[i].y - p[j].y));
    }
    return b;
}

// Puntos enteros ESTRICTAMENTE interiores, despejando Pick: A = I + B/2 - 1.
// Con 2A entero la cuenta sale exacta y sin dividir.
ll puntosInteriores(const vector<P>& p) {
    return (llabs(area2(p)) - puntosBorde(p) + 2) / 2;
}

// Centroide (centro de masa) del poligono. No es el promedio de los vertices.
pair<double, double> centroide(const vector<P>& p) {
    int n = p.size();
    double a = 0, cx = 0, cy = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double cr = (double)p[i].x * p[j].y - (double)p[j].x * p[i].y;
        a  += cr;
        cx += (p[i].x + p[j].x) * cr;
        cy += (p[i].y + p[j].y) * cr;
    }
    a /= 2;
    return {cx / (6 * a), cy / (6 * a)};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<P> p(n);
    for (auto &v : p) cin >> v.x >> v.y;

    ll a2 = area2(p);

    // Imprimir sin perder el medio punto: parte entera y el .5 aparte.
    cout << llabs(a2) / 2;
    if (llabs(a2) % 2) cout << ".5";
    cout << "\n";

    return 0;
}

// OJO con el overflow: si las coordenadas llegan a 1e9, cada producto
// llega a 1e18 y la suma de varios se pasa de long long. En ese caso
// acumula en __int128, o traslada todos los puntos restando el primer
// vertice antes de sumar (las coordenadas se vuelven chicas y el area
// no cambia).
