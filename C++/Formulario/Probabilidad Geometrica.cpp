// <3
// Tema: Formulario / Probabilidad Geometrica y Areas Raras
// Resumen: Para los problemas que en realidad son matematica pura y lo dificil no es
// programarlos sino plantear el...
// Detalle: Para los problemas que en realidad son matematica pura y lo dificil no es
// programarlos sino plantear el area: "cual es la probabilidad de que un punto al azar del
// jardin caiga dentro de algun circulo", "cuanto vale en promedio", "que tan seguido se
// encuentran dos personas". La idea unica de toda la ficha: probabilidad = area favorable /
// area total, y el valor esperado es la suma de cada valor por su probabilidad, sin necesitar
// independencia. Trae las areas que no se sacan de memoria: interseccion de dos circulos,
// circulo con rectangulo, y los clasicos de la cita, el palito y la aguja de Buffon. Todo
// verificado con Monte Carlo en este mismo equipo.

// =============== PROBABILIDAD GEOMETRICA Y AREAS RARAS ===============
//
// La idea base
//     P(evento) = medida favorable / medida total
//     En 1D la medida es largo, en 2D area, en 3D volumen.
//     Si el punto se elige UNIFORME, no hay nada mas que calcular
//     areas. El problema "de programacion" es en realidad geometria.
//
// Valor esperado
//     E[X] = suma de (valor * probabilidad de ese valor)
//     LINEALIDAD: E[A + B] = E[A] + E[B] SIEMPRE, aunque A y B
//     esten correlacionados. Es lo que permite sumar la contribucion
//     de cada objeto por separado en vez de analizar el conjunto.
//     Ejemplo tipico: cada circulo i tiene valor v_i y cubre un area
//     a_i del jardin de W x H, entonces
//         respuesta = suma de v_i * (a_i / (W*H))
//     Si los circulos se traslapan NO importa: la linealidad sigue
//     valiendo, cada uno aporta su parte por separado.
//
// Interseccion de DOS circulos (area de la lente)   (verificado)
//     d = distancia entre centros
//     si d >= r1 + r2        -> 0, no se tocan
//     si d <= |r1 - r2|      -> pi * min(r1,r2)^2, uno dentro del otro
//     si no:
//         a1 = 2*acos((d*d + r1*r1 - r2*r2) / (2*d*r1))
//         a2 = 2*acos((d*d + r2*r2 - r1*r1) / (2*d*r2))
//         A  = 0.5*r1*r1*(a1 - sin(a1)) + 0.5*r2*r2*(a2 - sin(a2))
//     O sea: la lente son dos segmentos circulares pegados.
//     union de los dos = pi r1^2 + pi r2^2 - A
//
// Segmento y sector (los ladrillos de todo lo anterior)
//     sector de angulo t : A = r^2 * t / 2
//     segmento (lo que queda entre la cuerda y el arco):
//         A = r^2 * (t - sin t) / 2
//     cuerda del angulo t : largo = 2 r sin(t/2)
//
// Circulo contra rectangulo o poligono
//     No hay formula cerrada corta. Se recorre el borde del poligono
//     sumando areas con signo, tratando cada arista aparte segun si
//     el tramo cae dentro o fuera del circulo.
//     Esta implementado en la seccion Geometry, ficha
//     "Area Circulo-Poligono". Es el metodo del problema del jardin.
//
// Que una FIGURA QUEPA: traducir "cabe" a desigualdades
//     Cuando piden la probabilidad de que algo quepa dentro de otra
//     cosa, casi nunca se integra a lo bruto: conviene escribir el
//     "cabe" como desigualdades sobre las coordenadas, que suelen
//     simplificarse muchisimo.
//     LA HERRAMIENTA CLAVE (arco capaz): el circulo que tiene al
//     segmento AB como DIAMETRO cabe dentro de un convexo K si y
//     solo si todo punto de la frontera de K ve a AB con angulo de
//     a lo sumo 90 grados. Es porque ese circulo es justo donde el
//     angulo vale 90, y por fuera de el es menor.
//     "Angulo <= 90 desde Q" se escribe sin trigonometria:
//         (A - Q) . (B - Q) >= 0
//     y si Q recorre un lado recto, se minimiza ese producto punto.
//     Ejemplo, para el lado x = 0 con Q = (0,q):
//         x1*x2 + (y1-q)*(y2-q) >= 0  para todo q
//         el minimo cae en q = (y1+y2)/2 y vale x1*x2 - (y1-y2)^2/4
//         o sea la condicion es  4*x1*x2 >= (y1-y2)^2
//     En un rectangulo L x W salen cuatro asi, sin una sola raiz:
//         4*x1*x2 >= (y1-y2)^2      4*(W-x1)*(W-x2) >= (y1-y2)^2
//         4*y1*y2 >= (x1-x2)^2      4*(L-y1)*(L-y2) >= (x1-x2)^2
//     (verificado contra la condicion directa de centro y radio en
//     3000000 de pruebas, sin una sola diferencia)
//     Y como las desigualdades son homogeneas de grado 2, escalar el
//     rectangulo no cambia la probabilidad: solo importa la PROPORCION
//     entre los lados. Para dos piedras uniformes en L x W, con
//     t = min(L,W)/max(L,W), la probabilidad de que el circulo quepa es
//         P = (pi/6) * t * (2 - t)
//     (formula verificada numericamente en 8 proporciones, no demostrada;
//     el problema es "I - Omens" de ICPC 2024, esta en este cuaderno)
//     Lo transferible es el metodo, no la formula: primero traducir
//     "cabe" a desigualdades, despues mirar si colapsan.
//
// Uniones de varias figuras
//     |A u B| = |A| + |B| - |A n B|
//     Con tres o mas, inclusion-exclusion (2^n terminos): solo sirve
//     si n es chico. Si no, integracion por barrido o Monte Carlo.
//     Para "cuanta area cubre al menos un circulo" con muchos circulos,
//     lo estandar es barrido angular, no inclusion-exclusion.
//
// Clasicos que se resuelven dibujando el espacio de casos
//     Cita: dos personas llegan uniformemente en [0,T] y se esperan
//     t minutos. El espacio es el cuadrado T x T, y se encuentran en
//     la franja |x - y| <= t.   (verificado)
//         P = 1 - ((T - t)/T)^2
//     Palito partido en tres pedazos al azar: forman triangulo con
//     probabilidad 1/4.   (verificado)
//     Aguja de Buffon: aguja de largo L sobre lineas separadas d,
//     con L <= d, cruza una linea con   P = 2L / (pi * d)  (verificado)
//
// Como atacar uno de estos en competencia
//     1. Identifica que se elige al azar y con que distribucion.
//     2. Dibuja el espacio completo de posibilidades y su medida.
//     3. Sombrea la region favorable y calcula SU medida.
//     4. Si hay varios objetos con valor, usa linealidad y suma
//        valor por probabilidad, uno por uno.
//     5. Si el area no sale cerrada, piensa en barrido o en integrar.
//     Antes de entregar, comprueba con Monte Carlo: es cinco lineas
//     y te dice si la formula que planteaste esta bien.
//
// En C++
//     Area de la interseccion de dos circulos (la lente).
//     double areaLente(double r1, double r2, double d) {
//         if (d >= r1 + r2) return 0;                       // separados
//         if (d <= fabs(r1 - r2))               // uno dentro del otro
//             return PI * min(r1, r2) * min(r1, r2);
//         double a1 = 2 * acos((d*d + r1*r1 - r2*r2) / (2*d*r1));
//         double a2 = 2 * acos((d*d + r2*r2 - r1*r1) / (2*d*r2));
//         return 0.5*r1*r1*(a1 - sin(a1)) + 0.5*r2*r2*(a2 - sin(a2));
//     }
//     union de los dos = PI*r1*r1 + PI*r2*r2 - areaLente(r1, r2, d)
//     Los dos primeros if no son adorno: sin ellos, acos recibe un valor
//     fuera de [-1,1] y devuelve NaN.
