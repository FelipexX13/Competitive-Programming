// <3
// Tema: Math / Probabilidad (Valor esperado con inverso modular)
// Resuelve "Frangolino ali na mesa" (Maratona SBC de Programacao 2025, Problem F): un robot
// mesero recibe Q comandos, cada uno con un argumento X_i, pero cada comando es en realidad "ir
// a la mesa X_i" o "pedir X_i milanesas en la mesa actual" con 50% de probabilidad cada uno
// (empezando en la mesa 1); hay que calcular, para cada mesa, el valor esperado de milanesas
// servidas, modulo 1e9+7. El codigo usa linealidad de la esperanza: arma coeff[i] = X_i *
// inv2^i, calcula sumas por sufijo "suffix[i]" de esos coeficientes, inicializa ans[1] con
// suffix[1] (caso en que el robot nunca se movio) y le suma a ans[X_i] el termino pow2[i-1] *
// suffix[i+1] (la contribucion esperada de que el comando i sea el ultimo movimiento hacia esa
// mesa), todo con aritmetica modular precomputada de potencias e inversos de 2.

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, Q;
    cin >> N >> Q;
 
    vector<int> X(Q + 1);
 
    long long inv2 = (MOD + 1) / 2;
 
    vector<long long> invPow(Q + 1), pow2(Q + 1);
    invPow[0] = 1;
    pow2[0] = 1;
    for (int i = 1; i <= Q; i++) {
        invPow[i] = invPow[i - 1] * inv2 % MOD;
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
 
    vector<long long> coeff(Q + 1);
    for (int i = 1; i <= Q; i++) {
        cin >> X[i];
        coeff[i] = 1LL * X[i] * invPow[i] % MOD;
    }
 
    vector<long long> suffix(Q + 2, 0);
    for (int i = Q; i >= 1; i--) {
        suffix[i] = (suffix[i + 1] + coeff[i]) % MOD;
    }
 
    vector<long long> ans(N + 1, 0);
 
    // initial value at table 1
    ans[1] = suffix[1];
 
    // increments
    for (int i = 1; i <= Q; i++) {
        long long add = pow2[i - 1] * suffix[i + 1] % MOD;
        ans[X[i]] += add;
        if (ans[X[i]] >= MOD) ans[X[i]] -= MOD;
    }
 
    for (int i = 1; i <= N; i++)
        cout << ans[i] % MOD << "\n";
 
    return 0;
}