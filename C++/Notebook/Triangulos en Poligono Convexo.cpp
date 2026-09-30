// <3
// Tema: Combinatorics / Triangulos en Poligono Convexo
// O: (1), es C(n,3)
// Uso: c3(n) = n*(n-1)*(n-2)/6  // todo trio de un convexo es triangulo
// Dado n, cuantos triangulos distintos salen escogiendo 3 vertices de un poligono regular
// convexo de n lados. La respuesta es simplemente C(n,3) = n*(n-1)*(n-2)/6. Con n = 5 da 10,
// que son exactamente los diez del dibujo del enunciado.
// TODO EL PROBLEMA ESTA EN VER POR QUE NO HAY QUE RESTAR NADA. Contar triangulos con vertices
// de un conjunto de puntos NO es C(n,3) en general: hay que quitar las ternas COLINEALES, que
// dan un triangulo degenerado de area cero. Lo que salva este problema es la palabra CONVEXO:
// en un poligono convexo ningun vertice cae sobre el segmento que une a otros dos, asi que no
// existe una sola terna colineal y las C(n,3) ternas sirven todas. Si el enunciado dijera
// "puntos en el plano" en vez de "poligono convexo", la solucion seria otra: contar las ternas
// colineales agrupando por direccion y restarlas.
// Y se cuentan CONJUNTOS de vertices, no formas. En el pentagono los 10 incluyen repetidos por
// congruencia (5 con dos lados del poligono y 5 con un lado y dos diagonales), y el dibujo los
// muestra como distintos. Si pidieran formas distintas salvo rotacion y reflexion, seria otro
// problema completamente, de conteo de Burnside.
// La sucesion son los numeros tetraedricos: n = 3, 4, 5, ... da 1, 4, 10, 20, 35, 56, 84, 120,
// 165, 220. Sirve para reconocerla si aparece en una salida sin saber de donde viene.
// Verificado contra fuerza bruta (contar las ternas una por una) para n de 0 a 300, y contra
// enteros exactos para n hasta 2000: sin un solo fallo.
//
// LO UNICO QUE PUEDE FALLAR ES EL DESBORDE, y vale saber donde exactamente (medido):
//   - Escribiendo n*(n-1)*(n-2)/6 tal cual, el PRODUCTO intermedio se pasa de long long con
//     n = 2097154. O sea que la formula directa aguanta hasta n = 2097153.
//   - Dividiendo ANTES de multiplicar (que es lo que hace c3 aqui abajo) se llega hasta
//     n = 3810779, y ahi el que ya no cabe es el RESULTADO, no un paso intermedio.
//   - Conviene tener claro que dividir temprano solo gana un factor 1.82 en n: el techo duro lo
//     pone el resultado, y contra eso no hay orden de operaciones que ayude. Si n es mas grande
//     toca __int128, unsigned, o responder modulo algo.
// POR QUE LA DIVISION TEMPRANA ES EXACTA: entre tres enteros consecutivos siempre hay uno
// multiplo de 3 y al menos uno par, asi que se puede dividir cada factor por separado sin
// perder nada. Lo que NO se puede es dividir a lo bruto: hay que buscar CUAL de los tres es el
// multiplo de 3, porque no siempre es el mismo.
// Si el problema pide la respuesta modulo un primo p, no se divide: se multiplica por el
// inverso de 6, o sea C(n,3) = n*(n-1)*(n-2) * inv6 % p, con inv6 = modpow(6, p-2, p).

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// C(n,3) sin formar el producto completo.
ll c3(ll n) {
    if (n < 3) return 0;

    ll a = n, b = n - 1, c = n - 2;

    // Entre tres consecutivos hay exactamente un multiplo de 3.
    if (a % 3 == 0) {
        a /= 3;
    } else if (b % 3 == 0) {
        b /= 3;
    } else {
        c /= 3;
    }

    // Y al menos uno par (puede que el de arriba ya haya cambiado la paridad).
    if (a % 2 == 0) {
        a /= 2;
    } else if (b % 2 == 0) {
        b /= 2;
    } else {
        c /= 2;
    }

    return a * b * c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    while (cin >> n) {
        cout << c3(n) << '\n';
    }
    return 0;
}
