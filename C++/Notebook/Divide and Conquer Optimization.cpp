// <3
// Tema: Dynamic Programming / Divide and Conquer Optimization
// Resumen: Optimiza DPs por capas del tipo dp[i][m] = min sobre k de (dp[i-1][k] + C(k,m))
// O: (n log n) por capa, en vez de O(n^2)
// Uso: compute(1,n,1,n,C,prev,cur,opt); exige desigualdad de Monge
// Detalle: Optimiza DPs por capas del tipo dp[i][m] = min sobre k de (dp[i-1][k] + C(k,m)),
// tipicos de "partir un arreglo en i grupos". Baja cada capa de O(n^2) a O(n log n). Se apoya
// en que el punto de corte optimo es monotono: si opt[m] es el mejor k para m, entonces opt es
// no decreciente en m. Entonces se resuelve el m del medio buscando su optimo en el rango
// [optl, optr], y con ese resultado se acota la busqueda de las dos mitades: la izquierda solo
// puede tener su optimo en [optl, bestk] y la derecha en [bestk, optr]. Solo es valido si el
// costo C cumple la desigualdad cuadrangular (condicion de Monge).

#include <bits/stdc++.h>

using namespace std;

const long long INF = (1LL << 62);

void compute(int l, int r, int optl, int optr,
             const function<long long(int,int)>& C,
             vector<long long>& prev, vector<long long>& cur, vector<int>& opt)
{
    if (l > r) return;

    int m = (l + r) / 2;
    int bestk = optl;
    long long best = INF;

    for (int k = optl; k <= min(m - 1, optr); ++k)
    {
        long long v = prev[k] + C(k, m);
        if (v < best)
        {
            best = v;
            bestk = k;
        }
    }

    cur[m] = best;
    opt[m] = bestk;

    compute(l, m - 1, optl, bestk, C, prev, cur, opt);
    compute(m + 1, r, bestk, optr, C, prev, cur, opt);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
