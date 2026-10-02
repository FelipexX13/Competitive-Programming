// <3
// Tema: Math / Exponenciacion de Matrices (Recurrencias Lineales con n hasta 10^18)
// Resumen: f(n) de una recurrencia lineal de orden k en O(k^3 log n), con n de hasta 10^18
// O: (k^3 log n)
// Uso: recurrencia({c1..ck}, {f0..f(k-1)}, n) para f(n)=c1*f(n-1)+...+ck*f(n-k)
// Detalle: Si f(n) = c1*f(n-1) + c2*f(n-2) + ... + ck*f(n-k), el vector de los ultimos k
// valores avanza multiplicando por una matriz fija T de k x k (fila 0 = los coeficientes,
// debajo una identidad corrida). Avanzar n pasos es multiplicar por T^n, y T^n sale por
// exponenciacion binaria en log n productos de matrices. Fibonacci: c = {1,1}, f0 = {0,1}.
// Con termino constante (f(n) = a*f(n-1) + b): agregar una componente que siempre vale 1,
// orden k+1. Con suma acumulada S(n) = f(0)+...+f(n): agregar S como otra componente.
// Caminos de largo EXACTO L entre i y j en un grafo: (A^L)[i][j], con A la matriz de
// adyacencia; es la misma potencia. Tiempo medido con n = 10^18 y matriz llena:
// k = 50 -> 20 ms, k = 100 -> 130 ms, k = 200 -> 800 ms (al limite de 1 s).

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> Mat;

const ll MOD = 1e9 + 7;

Mat mul(const Mat &A, const Mat &B)
{
    int n = A.size(), m = B[0].size(), k = B.size();
    Mat C(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int t = 0; t < k; t++)
        {
            if (A[i][t] == 0) continue;
            for (int j = 0; j < m; j++)
            {
                C[i][j] = (C[i][j] + A[i][t] * B[t][j]) % MOD;
            }
        }
    }
    return C;
}

Mat matpow(Mat A, ll e)
{
    int n = A.size();
    Mat R(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    while (e)
    {
        if (e & 1) R = mul(R, A);
        A = mul(A, A);
        e >>= 1;
    }
    return R;
}

// f(n) = c[0]*f(n-1) + c[1]*f(n-2) + ... + c[k-1]*f(n-k), con f(0..k-1) = f0
ll recurrencia(const vector<ll> &c, const vector<ll> &f0, ll n)
{
    int k = c.size();
    if (n < k) return ((f0[n] % MOD) + MOD) % MOD;
    Mat T(k, vector<ll>(k, 0));
    for (int j = 0; j < k; j++) T[0][j] = ((c[j] % MOD) + MOD) % MOD;
    for (int i = 1; i < k; i++) T[i][i - 1] = 1;
    Mat P = matpow(T, n - k + 1);
    // estado inicial (f(k-1), f(k-2), ..., f(0)) como columna
    ll res = 0;
    for (int j = 0; j < k; j++)
    {
        ll v = ((f0[k - 1 - j] % MOD) + MOD) % MOD;
        res = (res + P[0][j] * v) % MOD;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
