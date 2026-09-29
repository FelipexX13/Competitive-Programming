// <3
// Tema: Formulario / Areas y Volumenes
// Areas de figuras planas y volumenes de cuerpos, incluidas las que uno cree recordar y
// termina equivocando: el rombo es d1*d2/2 (no lado por lado), el cono y la piramide llevan
// el tercio, y el perimetro de la elipse NO tiene formula cerrada elemental, solo la
// aproximacion de Ramanujan.
// Todas las formulas de aqui se comprobaron contra integracion numerica o contra el area por
// shoelace del poligono correspondiente.

// =============== AREAS Y VOLUMENES ===============
//
// Figuras planas   (A = area, P = perimetro)
//     cuadrado     A = L^2          P = 4L      diagonal = L*sqrt(2)
//     rectangulo   A = b*h          P = 2(b+h)  diagonal = sqrt(b^2+h^2)
//     rombo        A = d1*d2 / 2    P = 4L
//         las diagonales se cortan perpendicularmente en el centro
//         el lado sale de ellas: L = sqrt((d1/2)^2 + (d2/2)^2)
//         tambien A = L^2 * sin(angulo)
//     romboide     A = b*h          P = 2(a+b)
//     trapecio     A = (B + b) * h / 2
//     triangulo    A = b*h/2        (Heron esta en la ficha Geometria)
//     circulo      A = pi r^2       P = 2 pi r
//     corona circular  A = pi (R^2 - r^2)
//     sector de angulo t en radianes
//         A = r^2 * t / 2          arco = r * t
//     elipse       A = pi a b
//         El perimetro no tiene formula cerrada elemental.
//         Ramanujan, APROXIMADO (error ~1e-5 con a=5, b=2, medido):
//             P ~ pi (3(a+b) - sqrt((3a+b)(a+3b)))
//     poligono regular de n lados de largo L   (verificado)
//         A = n * L^2 / (4 * tan(pi/n))
//         apotema = L / (2 * tan(pi/n))
//         angulo interior = (n-2)*180/n     suma total = (n-2)*180
//         angulo central = 360/n
//
// Cuerpos   (V = volumen, S = area total)
//     cubo            V = a^3           S = 6a^2
//                     diagonal = a*sqrt(3)
//     ortoedro        V = a*b*c         S = 2(ab + ac + bc)
//                     diagonal = sqrt(a^2 + b^2 + c^2)
//     prisma          V = (area base) * h
//     cilindro        V = pi r^2 h      lateral = 2 pi r h
//                     S = 2 pi r (r + h)
//     cono            V = pi r^2 h / 3  lateral = pi r g
//                     g = sqrt(r^2 + h^2)    S = pi r (r + g)
//     esfera          V = 4/3 pi r^3    S = 4 pi r^2
//     casquete esferico de altura h  (verificado)
//                     V = pi h^2 (3r - h) / 3
//     piramide        V = (area base) * h / 3
//     tetraedro regular de arista a  (verificado)
//                     V = a^3 / (6*sqrt(2))     S = sqrt(3) * a^2
//     toro, R al centro del tubo y r el radio del tubo (verificado)
//                     V = 2 pi^2 R r^2          S = 4 pi^2 R r
//
// Reglas que se olvidan
//     Al escalar una figura por k: longitudes x k, areas x k^2,
//     volumenes x k^3. Sirve para problemas de semejanza.
//     Pappus: al girar una figura plana alrededor de un eje externo,
//     V = area de la figura * recorrido de su centroide.
//     El cono y la piramide son un tercio del prisma de igual base
//     y altura; la esfera es dos tercios del cilindro que la encierra.
