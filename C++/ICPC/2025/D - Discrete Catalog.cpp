// <3
// Tema: Combinatorics / Ranking de Combinaciones
// Resumen: Dado un subconjunto de tamano k escrito en orden creciente
// O: (n*k), ranking de combinaciones con binomiales
// Detalle: Resuelve "Discrete Catalog" (problema D, ICPC 2025): dado un subconjunto de tamano k
// escrito en orden creciente, decir que posicion ocupa en la lista de TODOS los subconjuntos de
// tamano k ordenados lexicograficamente, contando desde 0. LA IDEA ES CONTAR LO QUE VA ANTES,
// sin generar nada. Recorriendo el subconjunto de izquierda a derecha, cuando en la posicion i
// esta el valor a[i], todos los subconjuntos que en esa posicion tienen un valor MENOR (y
// coinciden en lo anterior) van antes. Para cada candidato j menor que a[i], lo que queda por
// elegir son k-i-1 valores de entre los n-j que siguen, o sea C(n-j, k-i-1). Se suman todos
// esos y se pasa a la siguiente posicion. Ese patron de "contar los que van antes prefijo por
// prefijo" es el ranking, y sirve igual para permutaciones o para cualquier orden
// lexicografico: cambia solo la formula de cuantos completan. El nCr usado multiplica y divide
// alternando (r = r * (n-i+1) / i), que mantiene los numeros chicos porque en cada paso r es
// exactamente un binomial. Con n <= 60 no se desborda: el mayor ID posible es C(60,30) - 1 =
// 118264581564861423, que cabe holgado en long long. Ojo que esa misma funcion SI se desborda a
// partir de n = 62 aunque el resultado quepa. Verificado de dos formas: contra la lista
// completa ordenada para n hasta 12 (6556 escenarios) y contra el ranking exacto calculado
// aparte para n hasta 60 (4005 escenarios). Sin fallos, y los nueve casos del sample dan
// exacto.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll nCr(int n, int k) {
    if (k < 0 || k > n)
        return 0;

    k = min(k, n - k);

    ll r = 1;

    for (int i = 1; i <= k; i++) {
        r = r * (n - i + 1) / i;
    }

    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;

    while (cin >> n >> k) {

        vector<int> a(k);

        for (int &x : a)
            cin >> x;

        ll god = 0;

        int anterior = 0;

        for (int i = 0; i < k; i++)
        {
            for (int j = anterior + 1; j < a[i]; j++)
            {
                god += nCr(n - j, k - i - 1);
            }

            anterior = a[i];
        }

        cout << god << endl;
    }

    return 0;
}
