// <3
// Tema: Formulario / Trigonometria
// Conversion grados-radianes, la tabla de valores exactos, las identidades que se usan para
// simplificar antes de programar, y las leyes de senos y cosenos para resolver un triangulo
// del que solo se conocen algunos lados o angulos.
// El detalle practico mas importante: en C++ sin, cos y tan reciben RADIANES, y para sacar
// el angulo de un vector hay que usar atan2(y,x), no atan(y/x), que pierde el cuadrante.
// Valores e identidades verificados numericamente.

// =============== TRIGONOMETRIA ===============
//
// Conversion
//     radianes = grados * pi / 180
//     grados   = radianes * 180 / pi
//     PI = acos(-1.0)      (mas exacto que escribir 3.14159...)
//     En C++ sin/cos/tan reciben RADIANES, no grados.
//
// Valores exactos   (verificados)
//     grados       0     30      45      60     90
//     radianes     0   pi/6    pi/4    pi/3   pi/2
//     sin          0    1/2   r2/2    r3/2      1
//     cos          1   r3/2   r2/2     1/2      0
//     tan          0   r3/3      1      r3    inf
//     r2 = sqrt(2) ~ 1.4142136    r3 = sqrt(3) ~ 1.7320508
//
// Triangulo rectangulo
//     sin = cateto opuesto / hipotenusa
//     cos = cateto adyacente / hipotenusa
//     tan = opuesto / adyacente = sin / cos
//     Pitagoras : a^2 + b^2 = c^2
//     Ternas enteras comunes: 3-4-5, 5-12-13, 8-15-17, 7-24-25
//
// Identidades   (verificadas)
//     sin^2 t + cos^2 t = 1
//     sin(2t) = 2 sin t cos t
//     cos(2t) = cos^2 t - sin^2 t = 1 - 2 sin^2 t = 2 cos^2 t - 1
//     sin(a+b) = sin a cos b + cos a sin b
//     cos(a+b) = cos a cos b - sin a sin b
//     tan(a+b) = (tan a + tan b) / (1 - tan a tan b)
//     sin(-t) = -sin t        cos(-t) = cos t
//     sin(pi - t) = sin t     cos(pi - t) = -cos t
//     periodo de sin y cos : 2pi      periodo de tan : pi
//
// Triangulo cualquiera   (verificados con el triangulo 3-4-5)
//     ley de senos   : a/sin A = b/sin B = c/sin C = 2R
//     ley de cosenos : c^2 = a^2 + b^2 - 2ab cos C
//         despejando : cos C = (a^2 + b^2 - c^2) / (2ab)
//         si cos C > 0 el angulo es agudo, si < 0 es obtuso
//     area = (1/2) * a * b * sin C
//     radio circunscrito R = a*b*c / (4 * area)
//     radio inscrito     r = area / s   con s el semiperimetro
//     Los angulos suman 180 grados: sabiendo dos, el tercero sale solo.
//
// atan2 contra atan
//     atan2(y, x) devuelve el angulo correcto en los cuatro cuadrantes,
//     en el rango (-pi, pi]. Ejemplo: atan2(-1,-1) = -135 grados.
//     atan(y/x) pierde el cuadrante y se rompe cuando x = 0.
//     Angulo CON SIGNO entre dos vectores:
//         atan2(cross(a,b), dot(a,b))
//     Para ordenar puntos alrededor de un centro se puede usar atan2,
//     pero con enteros es mas exacto comparar por cuadrante y luego
//     por producto cruz, sin tocar flotantes.
