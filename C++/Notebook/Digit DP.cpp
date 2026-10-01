// <3
// Tema: Dynamic Programming / Digit DP
// Resumen: Contar numeros de 0 a X por una propiedad de sus digitos, con el flag tight
// O: (digitos * estados * 10), aqui 20*200*2*10
// Uso: solve_digitdp(B,d) - solve_digitdp(A-1,d)  // rango [A,B]
// Detalle: Cuenta cuantos numeros de 0 a X cumplen una propiedad definida sobre sus digitos
// (aqui: que la suma de digitos sea divisible por D). Se recorre el numero digito por digito
// llevando dos cosas en el estado: el acumulado de la propiedad (s) y el flag tight, que indica
// si el prefijo construido sigue pegado al prefijo de X. El flag tight es la clave: si sigue
// activo, el digito actual solo puede llegar hasta el digito correspondiente de X; si ya se
// rompio (se puso un digito menor), a partir de ahi se puede poner cualquier cosa de 0 a 9 y el
// subarbol se memoiza y se reutiliza. Para contar en un rango [A,B] se calcula solve(B) -
// solve(A-1).

#include <bits/stdc++.h>

using namespace std;

long long dp[20][200][2];
string S;
int D;

long long go(int i, int s, int tight)
{
    if (i == (int)S.size()) return (s % D == 0);

    long long &r = dp[i][s][tight];
    if (r != -1) return r;
    r = 0;

    int lim = 9;
    if (tight) lim = S[i] - '0';

    for (int d = 0; d <= lim; ++d)
    {
        r += go(i + 1, (s + d) % D, tight && d == lim);
    }
    return r;
}

long long solve_digitdp(long long X, int d)
{
    S = to_string(X);
    D = d;
    memset(dp, -1, sizeof dp);
    return go(0, 0, 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A, B;
    int d;
    while (cin >> A >> B >> d)
    {
        cout << solve_digitdp(B, d) - solve_digitdp(A - 1, d) << "\n";
    }

    return 0;
}
