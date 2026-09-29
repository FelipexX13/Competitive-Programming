// <3
// Tema: Formulario / Algebra y Ecuaciones
// Resolver e igualar ecuaciones: cuadratica con discriminante, Vieta para sacar suma y
// producto de raices sin calcularlas, sistemas 2x2 por Cramer, productos notables, leyes de
// exponentes y logaritmos, y proporciones y promedios.
// Incluye la version numericamente estable de la cuadratica, que importa cuando b^2 domina a
// 4ac y la resta directa pierde todos los digitos. Vieta y Cramer estan verificados.

// =============== ALGEBRA Y ECUACIONES ===============
//
// Ecuacion cuadratica   a x^2 + b x + c = 0
//     x = (-b +- sqrt(b^2 - 4ac)) / (2a)
//     discriminante D = b^2 - 4ac
//         D > 0 : dos raices reales distintas
//         D = 0 : una raiz doble, x = -b/(2a)
//         D < 0 : ninguna raiz real
//     Vieta (verificado) : x1 + x2 = -b/a    x1 * x2 = c/a
//         Sirve para responder sobre las raices sin calcularlas.
//     Version estable, cuando b^2 es mucho mayor que 4ac:
//         q  = -(b + sign(b)*sqrt(D)) / 2
//         x1 = q / a        x2 = c / q
//     Si a = 0 no es cuadratica: es b x + c = 0, y si b = 0 tambien
//     hay que tratarlo aparte. Ese caso borde tumba muchas soluciones.
//
// Sistema de dos ecuaciones (Cramer, verificado)
//     a1 x + b1 y = c1
//     a2 x + b2 y = c2
//     det = a1*b2 - a2*b1
//         det != 0 : solucion unica
//         det == 0 : o no hay solucion, o hay infinitas (misma recta)
//     x = (c1*b2 - c2*b1) / det        y = (a1*c2 - a2*c1) / det
//     Igualar dos funciones y = f(x), y = g(x) es resolver f(x)-g(x)=0.
//
// Productos notables
//     (a + b)^2 = a^2 + 2ab + b^2
//     (a - b)^2 = a^2 - 2ab + b^2
//     (a + b)(a - b) = a^2 - b^2
//     (a + b)^3 = a^3 + 3a^2 b + 3a b^2 + b^3
//     a^3 + b^3 = (a + b)(a^2 - ab + b^2)
//     a^3 - b^3 = (a - b)(a^2 + ab + b^2)
//     a^n - b^n siempre es divisible por (a - b)
//     binomio de Newton : (a+b)^n = sum_k C(n,k) a^(n-k) b^k
//
// Exponentes y logaritmos
//     a^m * a^n = a^(m+n)       a^m / a^n = a^(m-n)
//     (a^m)^n = a^(m*n)         (ab)^n = a^n b^n
//     a^0 = 1                   a^(-n) = 1 / a^n
//     a^(1/n) = raiz n-esima de a
//     log(x*y) = log x + log y  log(x/y) = log x - log y
//     log(x^n) = n * log x      log_b(x) = log(x) / log(b)
//     En C++ log() es natural; existen log2() y log10() aparte.
//     OJO: log2(n) puede dar 2.9999 por flotante. Si necesitas el
//     exponente exacto, usa 31 - __builtin_clz(n) o un bucle.
//
// Proporciones y porcentajes
//     regla de tres: si a corresponde a b, entonces c da b*c/a
//     aumentar p% : x * (1 + p/100)     disminuir : x * (1 - p/100)
//     variacion porcentual = (nuevo - viejo) / viejo * 100
//     Subir p% y luego bajar p% NO devuelve al valor original.
//     promedio simple   = suma / n
//     promedio ponderado= sum(w_i * x_i) / sum(w_i)
//     media geometrica  = (producto de los x_i)^(1/n)
//         se usa para tasas de crecimiento encadenadas
//     media armonica    = n / sum(1/x_i)
//         se usa para promediar velocidades sobre la misma distancia
//     Siempre: armonica <= geometrica <= aritmetica
//
// Valor absoluto e inecuaciones
//     |x| < a   equivale a   -a < x < a
//     |x| > a   equivale a   x < -a  o  x > a
//     |a + b| <= |a| + |b|         desigualdad triangular
//     Al multiplicar o dividir una inecuacion por un NEGATIVO,
//     el sentido se voltea. Es el error clasico al despejar.
//
// En C++
//     Cuadratica numericamente estable. Devuelve cuantas raices reales hay.
//     int cuadratica(double a, double b, double c, double& x1, double& x2) {
//         double D = b*b - 4*a*c;
//         if (D < 0) return 0;
//         double q = -(b + copysign(sqrt(D), b)) / 2;
//         x1 = q / a;
//         x2 = (fabs(q) > 1e-300) ? c / q : x1;
//         if (x1 > x2) swap(x1, x2);
//         return D > 0 ? 2 : 1;
//     }
//     El copysign evita restar dos numeros casi iguales. Con a=1, b=1e8,
//     c=1 la formula directa da 0 en una raiz; esta da -1e-8.
//     Sistema 2x2 por Cramer. false = no hay solucion unica.
//     bool cramer(double a1, double b1, double c1,
//                 double a2, double b2, double c2, double& x, double& y) {
//         double d = a1*b2 - a2*b1;
//         if (fabs(d) < 1e-12) return false;
//         x = (c1*b2 - c2*b1) / d;
//         y = (a1*c2 - a2*c1) / d;
//         return true;
//     }
