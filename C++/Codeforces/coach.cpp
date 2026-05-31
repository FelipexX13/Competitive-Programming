// <3
// Tema: Math / Polynomial Composition
// Calcula la composición de polinomios P(Q(x)) usando multiplicación polinómica modular.
// El resultado es modular 998244353 y tiene grado máximo n*m.

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

// Multiplica dos polinomios A y B
// A[i] representa el coeficiente de x^i
// B[j] representa el coeficiente de x^j
vector<long long> multiply(const vector<long long>& A, const vector<long long>& B) {
    vector<long long> result(A.size() + B.size() - 1, 0);

    for (int i = 0; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)B.size(); j++) {
            // A[i] * x^i multiplicado por B[j] * x^j
            // queda en el grado i + j
            result[i + j] += A[i] * B[j];
            result[i + j] %= MOD;
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // P tiene grado n, por eso tiene n + 1 coeficientes
    vector<long long> P(n + 1);

    // Q tiene grado m, por eso tiene m + 1 coeficientes
    vector<long long> Q(m + 1);

    for (int i = 0; i <= n; i++) {
        cin >> P[i];
    }

    for (int i = 0; i <= m; i++) {
        cin >> Q[i];
    }

    // El grado máximo de P(Q(x)) es n * m
    // Por eso la respuesta tiene n*m + 1 coeficientes
    vector<long long> ans(n * m + 1, 0);

    // power representa Q^i
    // Al inicio i = 0, entonces Q^0 = 1
    vector<long long> power = {1};

    // Calculamos:
    // P(Q(x)) = p0*Q^0 + p1*Q^1 + p2*Q^2 + ... + pn*Q^n
    for (int i = 0; i <= n; i++) {

        // Sumamos P[i] * Q^i a la respuesta
        for (int j = 0; j < (int)power.size(); j++) {
            ans[j] += P[i] * power[j];
            ans[j] %= MOD;
        }

        // Preparamos la siguiente potencia:
        // si ahora power = Q^i,
        // después de multiplicar por Q queda power = Q^(i+1)
        if (i < n) {
            power = multiply(power, Q);
        }
    }

    // Imprimimos los coeficientes r0, r1, ..., r(n*m)
    for (int i = 0; i <= n * m; i++) {
        cout << ans[i] << " ";
    }

    cout << "\n";

    return 0;
}