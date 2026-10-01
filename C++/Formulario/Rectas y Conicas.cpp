// <3
// Tema: Formulario / Rectas y Conicas
// Resumen: Formulario: la recta en sus cuatro formas, paralelas, perpendiculares, corte y conicas
// O: (1) cada formula, incluido el corte por Cramer
// Detalle: Geometria analitica de toda la vida: pendiente, las cuatro formas de escribir una
// recta, cuando dos son paralelas o perpendiculares, donde se cortan, y las ecuaciones de
// circunferencia, parabola, elipse e hiperbola. El corte de dos rectas se resuelve por Cramer,
// que es lo mismo que "igualar las dos ecuaciones" pero sin despejar a mano y sin dividir por
// cero sin darse cuenta: si el determinante da 0, son paralelas. Formulas verificadas
// numericamente.

// =============== RECTAS Y CONICAS ===============
//
// Pendiente por dos puntos
//     m = (y2 - y1) / (x2 - x1)     indefinida si x1 == x2 (vertical)
//     m > 0 sube, m < 0 baja, m = 0 horizontal
//     angulo con el eje x : theta = atan2(y2-y1, x2-x1)
//
// Formas de la recta
//     pendiente-intercepto : y = m x + b       con b = y1 - m*x1
//     punto-pendiente      : y - y1 = m (x - x1)
//     general              : A x + B y + C = 0
//         desde dos puntos:  A = y2-y1,  B = -(x2-x1),
//                            C = -(A*x1 + B*y1)
//         pendiente = -A/B  ; es vertical cuando B = 0
//     simetrica            : x/p + y/q = 1   (corta los ejes en p y q)
//
// Dos rectas
//     paralelas       : m1 == m2         o  A1*B2 - A2*B1 == 0
//     perpendiculares : m1 * m2 == -1    o  A1*A2 + B1*B2 == 0
//     angulo entre ellas : tan(t) = |(m2 - m1) / (1 + m1*m2)|
//     Con datos enteros compara pendientes cruzando fracciones y
//     evita dividir:  dy1*dx2 == dy2*dx1
//
// Interseccion: igualar las dos ecuaciones (Cramer, verificado)
//     A1 x + B1 y = C1
//     A2 x + B2 y = C2
//     det = A1*B2 - A2*B1
//     si det == 0 -> paralelas (o la misma recta, sin punto unico)
//     x = (C1*B2 - C2*B1) / det
//     y = (A1*C2 - A2*C1) / det
//     Para cortar y = f(x) con y = g(x), resuelve f(x) - g(x) = 0.
//
// Distancias y punto medio
//     |P1P2| = sqrt((x2-x1)^2 + (y2-y1)^2)
//     punto medio = ((x1+x2)/2, (y1+y2)/2)
//     punto a recta Ax+By+C=0 : |A*px + B*py + C| / sqrt(A^2 + B^2)
//     entre dos paralelas     : |C1 - C2| / sqrt(A^2 + B^2)
//     El SIGNO de A*px+B*py+C dice de que lado del corte esta el punto.
//
// Circunferencia
//     (x - h)^2 + (y - k)^2 = r^2        centro (h,k), radio r
//     general : x^2 + y^2 + Dx + Ey + F = 0
//         centro (-D/2, -E/2)
//         r = sqrt(D^2/4 + E^2/4 - F)
//     Dos circunferencias, con d la distancia entre centros:
//         se cortan en 2 puntos si |r1-r2| < d < r1+r2
//         tangentes exteriores si d == r1+r2
//         tangentes interiores si d == |r1-r2|
//         una dentro de la otra sin tocarse si d < |r1-r2|
//
// Parabola
//     y = a x^2 + b x + c
//     vertice : x = -b/(2a) ,  y = c - b^2/(4a)
//     abre hacia arriba si a > 0, hacia abajo si a < 0
//     canonica : y - k = a (x - h)^2   con vertice (h,k)
//
// Elipse e hiperbola centradas en (h,k)
//     elipse    : (x-h)^2/a^2 + (y-k)^2/b^2 = 1
//         a y b son los semiejes; si a = b es una circunferencia
//     hiperbola : (x-h)^2/a^2 - (y-k)^2/b^2 = 1
//         asintotas : y - k = +-(b/a)(x - h)
//
// En C++
//     double distPuntoRecta(double A, double B, double C,
//                           double px, double py) {
//         return fabs(A*px + B*py + C) / hypot(A, B);
//     }
//     bool corte(double A1, double B1, double C1,
//                double A2, double B2, double C2, double& x, double& y) {
//         double d = A1*B2 - A2*B1;
//         if (fabs(d) < 1e-12) return false;                // paralelas
//         x = (C1*B2 - C2*B1) / d;
//         y = (A1*C2 - A2*C1) / d;
//         return true;
//     }
//     Con coordenadas enteras, para saber si tres puntos son colineales NO
//     calcules pendientes: usa el producto cruz, que no divide ni pierde
//     precision.  (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1) == 0
