// <3
// Tema: Dynamic Programming / LIS en O(n log n) con Reconstruccion
// Resumen: Subsecuencia creciente mas larga con lower_bound, y los indices de una de ellas
// O: (n log n)
// Uso: auto idx = lis(a, true); largo = idx.size(); a[idx[k]] es la k-esima de la LIS
// Detalle: tail[k] guarda el MENOR valor en que puede terminar una subsecuencia creciente de
// largo k+1 visto hasta ahora. tail siempre queda ordenado, asi que cada a[i] se ubica con
// una binaria: si es mayor que todo, alarga la mejor; si no, reemplaza al primer tail que
// no le gana, dejando un final mas bajo para el futuro. El largo de la LIS es tail.size(),
// pero OJO: tail NO es una LIS, es solo una tabla de finales. Para sacar una de verdad se
// guarda, para cada i, el indice que tenia el tail anterior (padre) y se camina hacia atras.
// estricta = true  -> a[i1] <  a[i2] <  ... (lower_bound)
// estricta = false -> a[i1] <= a[i2] <= ... (upper_bound)
// Variantes: decreciente -> negar los valores. Por pares (x,y) con x creciente e y creciente:
// ordenar por x ascendente y, en empate de x, por y DESCENDENTE (para no encadenar dos con
// el mismo x), y correr LIS estricta sobre las y. Minimo de subsecuencias no crecientes que
// cubren todo (Dilworth) = largo de la LIS estricta.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> lis(const vector<ll> &a, bool estricta = true)
{
    int n = a.size();
    vector<ll> tail;                  // tail[k]: menor final de una de largo k+1
    vector<int> tailIdx, padre(n, -1);
    for (int i = 0; i < n; i++)
    {
        auto it = estricta ? lower_bound(tail.begin(), tail.end(), a[i])
                           : upper_bound(tail.begin(), tail.end(), a[i]);
        int k = it - tail.begin();
        if (k == (int)tail.size())
        {
            tail.push_back(a[i]);
            tailIdx.push_back(i);
        }
        else
        {
            tail[k] = a[i];
            tailIdx[k] = i;
        }
        padre[i] = k ? tailIdx[k - 1] : -1;
    }
    vector<int> res;
    for (int i = tail.empty() ? -1 : tailIdx.back(); i != -1; i = padre[i])
    {
        res.push_back(i);
    }
    reverse(res.begin(), res.end());
    return res;                       // indices crecientes de una LIS
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
