// <3
// Tema: Formulario / Geometria
// Resumen: Formulas de geometria que se usan sin pensar pero se olvidan bajo presion
// O: (1) las primitivas; (n) area y perimetro de poligono
// Detalle: Formulas de geometria que se usan sin pensar pero se olvidan bajo presion: areas,
// Heron, shoelace, Pick, sector y segmento circular, y el significado del signo del producto
// cruz. La regla que mas salva: si los datos son enteros, trabajar con cross/dot y distancias
// al cuadrado en vez de sqrt, y no comparar doubles con ==

// =============== GEOMETRIA ===============
//
// Triangulo
//     area = base * altura / 2
//     area = |cross(B-A, C-A)| / 2        con coordenadas
//     Heron: s=(a+b+c)/2, area = sqrt(s(s-a)(s-b)(s-c))
//     ley de cosenos : c^2 = a^2 + b^2 - 2ab*cos(C)
//     ley de senos   : a/sin(A) = b/sin(B) = c/sin(C) = 2R
//     desigualdad triangular: a+b > c para que exista
//
// Poligono simple (vertices en orden)
//     Shoelace: area = |sum (x_i * y_{i+1} - x_{i+1} * y_i)| / 2
//     El signo de la suma dice la orientacion: + antihorario.
//     Regular de n lados y lado L: area = n*L^2 / (4*tan(pi/n))
//     angulo interior = (n-2)*180/n grados
//
// Pick: para poligono con vertices en enteros
//     area = I + B/2 - 1
//     I = puntos enteros interiores, B = puntos enteros en el borde
//     puntos enteros en el segmento (x1,y1)-(x2,y2):
//         gcd(|x2-x1|, |y2-y1|) + 1   (contando los dos extremos)
//
// Circulo de radio r
//     perimetro = 2*pi*r          area = pi*r^2
//     sector de angulo t (rad)  : area = r^2 * t / 2
//     segmento circular         : area = r^2 (t - sin t) / 2
//     cuerda de angulo t        : largo = 2r*sin(t/2)
//     PI = acos(-1.0)   1 rad = 180/pi grados
//
// Producto cruz y punto (la base de todo)
//     cross(A,B) = ax*by - ay*bx
//     cross(A,B,C) = cross(B-A, C-A)
//         > 0 giro antihorario, < 0 horario, = 0 colineales
//     dot(A,B) = ax*bx + ay*by
//         > 0 angulo agudo, < 0 obtuso, = 0 perpendicular
//     Con enteros no uses sqrt: compara distancias al cuadrado.
//
// Distancias
//     punto a recta por A,B : |cross(B-A, P-A)| / |B-A|
//     Manhattan |dx|+|dy|, Chebyshev max(|dx|,|dy|)
//     Rotar 45 grados convierte Manhattan en Chebyshev:
//         (x,y) -> (x+y, x-y)
//
// Euler para grafos planos y poliedros
//     V - E + F = 2
//     Con n rectas en posicion general el plano queda en
//     1 + n + C(n,2) regiones: 2, 4, 7, 11, 16, 22, 29, 37
