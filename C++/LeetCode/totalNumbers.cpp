// <3
// Tema: Combinatorics / Conteo de Distintos con Inventario de Frecuencias
// Resumen: Dado un arreglo de digitos, contar cuantos numeros DISTINTOS de tres cifras se
// pueden armar usando tres de...
// O: (1000), tres ciclos sobre los digitos con inventario de frecuencias
// Detalle: Resuelve "Unique 3-Digit Even Numbers" (LeetCode 3483): dado un arreglo de digitos,
// contar cuantos numeros DISTINTOS de tres cifras se pueden armar usando tres de ellos, sin
// cero inicial y que el resultado sea par. La trampa es "distintos". Si uno cuenta
// permutaciones de posiciones, [6,6,6] daria 6 en vez de 1, porque los tres seises son
// intercambiables. El arreglo cnt da la vuelta al problema: en vez de recorrer POSICIONES del
// arreglo, recorre VALORES. Cada terna (first, second, last) se visita exactamente una vez, asi
// que cada numero se cuenta una sola vez por construccion, sin sets ni deduplicacion posterior.
// Lo que hace que sea correcto y no solo "distinto" es el prestamo: cnt[last]-- antes de abrir
// el ciclo de first, y cnt[first]-- antes del de second. Eso reserva la copia fisica del digito
// que ya se uso, para que cnt[second] > 0 signifique "queda todavia un ejemplar libre". Sin ese
// prestamo, [2,0,0] contaria 220 aunque solo haya un dos. Cada decremento se devuelve al salir
// del ciclo, asi que cnt vuelve intacto en cada vuelta. El ultimo digito manda la paridad, por
// eso se fija primero y solo con {0,2,4,6,8}; first va de 1 a 9 porque no puede haber cero
// inicial; second es libre de 0 a 9. Costo O(n + 5*9*10) = O(n) con 450 iteraciones fijas, sin
// memoria extra mas alla de cnt[10]. El patron sirve para cualquier "cuantos resultados
// distintos salen de un multiconjunto": iterar sobre los valores posibles y usar el arreglo de
// frecuencias como inventario que se presta y se devuelve.

class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10] = {};

        for (int x : digits) {
            cnt[x]++;
        }

        int ans = 0;

        for (int last : {0, 2, 4, 6, 8}) {
            if (cnt[last] == 0) continue;

            cnt[last]--;

            for (int first = 1; first <= 9; first++) {
                if (cnt[first] == 0) continue;

                cnt[first]--;

                for (int second = 0; second <= 9; second++) {
                    if (cnt[second] > 0) ans++;
                }

                cnt[first]++;
            }

            cnt[last]++;
        }

        return ans;
    }
};
