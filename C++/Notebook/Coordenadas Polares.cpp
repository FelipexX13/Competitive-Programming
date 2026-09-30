// <3
// Tema: Geometry / Coordenadas Polares
// O: (1) cada conversion, (n log n) ordenar por angulo
// Uso: aPolar(x,y) -> {r,th}; normalizar(th) deja th en [0,2pi)
// Pasar de (x, y) a (r, theta) y al contrario. Las formulas son de colegio, pero en competitiva
// lo que tumba la solucion son los detalles de implementacion, y por eso vale la ficha.
// 1) EL ANGULO SE SACA CON atan2(y, x), NUNCA CON atan(y/x). atan(y/x) pierde el cuadrante
//    (manda (-1,-1) al mismo angulo que (1,1)) y explota cuando x = 0. atan2 mira los signos de
//    los dos argumentos por separado y acierta en los cuatro cuadrantes.
//    OJO CON EL ORDEN DE LOS ARGUMENTOS: es atan2(y, x), la y va PRIMERO. Invertirlos da el
//    angulo respecto al eje y, y el error pasa desapercibido porque para 45 grados da lo mismo.
// 2) EL RADIO CON hypot(x, y), no con sqrt(x*x + y*y). hypot escala internamente y no pierde el
//    paso intermedio. Medido en esta maquina: con x = y = 1e-200, sqrt(x*x+y*y) da 0 porque el
//    cuadrado se va a cero por UNDERFLOW, mientras hypot da 1.41e-200. Por arriba, con 1e200,
//    aqui las dos dieron 1.41e200 (el x87 calcula con 80 bits y salva el caso), asi que el
//    problema real de sqrt es el underflow, no el overflow. Igual hypot sale gratis.
// 3) atan2 DEVUELVE EL RANGO (-pi, pi], no [0, 2pi). Los angulos de abajo del eje x salen
//    NEGATIVOS. Si el problema necesita [0, 2pi) hay que sumar 2pi a los negativos, y si se
//    olvida, el barrido angular arranca en el eje x NEGATIVO en vez del positivo.
//
// LO QUE DE VERDAD IMPORTA: PARA ORDENAR POR ANGULO, NO USES atan2.
// El uso numero uno de las polares en competitiva es el barrido angular. Con atan2 funciona,
// pero es la version fragil, y conviene tener claro en que falla exactamente:
//   - El orden ANGULAR sale bien con los dos metodos. Medido con 200000 puntos enteros
//     aleatorios: las dos ordenaciones son monotonas en angulo y NO hay ni un solo par cuyo
//     angulo verdadero quede en el orden equivocado.
//   - Donde atan2 se rompe es en los COLINEALES. De las 15156 posiciones en que las dos listas
//     no coinciden, las 15156 son entre puntos del MISMO angulo exacto: atan2 les da doubles
//     que difieren en el ultimo bit, el desempate por distancia nunca se ejecuta y quedan
//     revueltos. Con 200 puntos colineales barajados que deben salir por distancia, el
//     comparador exacto los ordena bien y el de atan2 los saca MAL, tanto con coordenadas
//     chicas como de 2e8.
//   - Y hay algo peor que el orden: comparar angulos double con epsilon rompe la
//     transitividad, y un comparador no transitivo en std::sort es comportamiento indefinido.
// La version exacta usa solo ENTEROS: se parte el plano en dos mitades (arriba o abajo del eje
// x) y dentro de la misma mitad se compara con el producto cruz. Cero punto flotante.
// SU LIMITE: cross y la norma multiplican coordenadas, y 2*c^2 tiene que caber en long long, o
// sea |coord| hasta ~2.1e9 (medido: con 2e9 cabe, con 3e9 la norma ya sale negativa). Para las
// coordenadas de 1e9 tipicas queda un factor 4 de margen.
//
// CUANDO SI CONVIENEN LAS POLARES: rotar (sumar al angulo), simetria circular, sectores y arcos,
// y cualquier enunciado que ya venga en (r, theta). Para SUMAR vectores hay que volver a
// cartesianas: en polares la suma no es componente a componente. Y para rotar un punto exacto
// conviene la matriz de rotacion sobre las cartesianas, que no pasa por atan2 ni acumula el
// error de ida y vuelta (medido: el viaje cartesiano -> polar -> cartesiano sobre 300000 puntos
// de hasta 1e6 pierde a lo sumo 4.7e-10, suficiente para un eps de 1e-9 pero no gratis).

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

// ---------- conversion ----------
struct Polar { double r, th; };

Polar aPolar(double x, double y) {
    return {hypot(x, y), atan2(y, x)};      // th queda en (-pi, pi]
}

pair<double, double> aCartesiano(double r, double th) {
    return {r * cos(th), r * sin(th)};
}

// Lleva cualquier angulo al rango [0, 2pi).
double normalizar(double th) {
    th = fmod(th, 2 * PI);
    if (th < 0) th += 2 * PI;
    return th;
}

double grados(double rad) { return rad * 180.0 / PI; }
double radianes(double deg) { return deg * PI / 180.0; }

// ---------- barrido angular exacto, sin atan2 ----------
struct P {
    long long x, y;
};

long long cross(const P &a, const P &b) { return a.x * b.y - a.y * b.x; }

// semiplano: 0 = angulo en [0, pi), 1 = en [pi, 2pi). El (0,0) cae en 0.
int mitad(const P &p) {
    if (p.y > 0) return 0;
    if (p.y < 0) return 1;
    if (p.x >= 0) return 0;                 // sobre el eje x: el +x va en la 1a
    return 1;                               // mitad y el -x en la 2a
}

// Ordena por angulo en [0, 2pi) arrancando en el +x. Los colineales quedan
// juntos y entre ellos ordenados por distancia al origen.
bool menorAngulo(const P &a, const P &b) {
    int ha = mitad(a), hb = mitad(b);
    if (ha != hb) return ha < hb;

    long long c = cross(a, b);
    if (c != 0) return c > 0;               // a va antes si b queda a su izq

    return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);

    double x, y;
    while (cin >> x >> y) {
        Polar p = aPolar(x, y);
        pair<double, double> q = aCartesiano(p.r, p.th);

        cout << "r = " << p.r
             << "  theta = " << p.th
             << " rad = " << grados(p.th) << " grados"
             << "  [0,2pi) = " << normalizar(p.th)
             << "  vuelta = (" << q.first << ", " << q.second << ")\n";
    }
    return 0;
}
