// <3
// Tema: Math / Eliminacion Gaussiana (mod p)
// Resuelve sistemas lineales A x = b sobre Z_p con p PRIMO, que es lo que aparece cuando el
// problema pide contar soluciones de un sistema, resolver ecuaciones modulares, o sacar el
// determinante y el rango de una matriz modulo un primo.
// La unica diferencia con el Gauss de toda la vida es que no se puede dividir: para normalizar
// el pivote se multiplica por su inverso modular (Fermat, a^(p-2) mod p). Como p es primo,
// TODO elemento distinto de cero tiene inverso, asi que no hace falta pivoteo parcial por
// estabilidad numerica como en double; basta tomar el primer pivote no nulo.
// Devuelve el rango. Con m incognitas, si el sistema es compatible hay exactamente
// p^(m - rango) soluciones: rango == m significa solucion unica, y rango < m deja variables
// libres (aqui se fijan en 0 para entregar una solucion cualquiera).
// Costo O(n * m * min(n,m)). Si p no es primo la normalizacion falla; y si el sistema es sobre
// GF(2), conviene la version con bitset, que va 64 veces mas rapido.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mpow(ll a, ll e, ll p) {
    ll r = 1; a %= p;
    while (e) { if (e & 1) r = r * a % p; a = a * a % p; e >>= 1; }
    return r;
}

ll inverso(ll a, ll p) { return mpow((a % p + p) % p, p - 2, p); }

// Matriz AUMENTADA de n filas por (m+1) columnas: las m incognitas y el termino
// independiente al final. Devuelve el rango; deja una solucion en sol.
int gauss(vector<vector<ll>> a, int m, vector<ll>& sol, bool& incompatible, ll p) {
    int n = a.size(), fila = 0;
    vector<int> donde(m, -1);          // donde[col] = fila que tiene el pivote de esa columna

    for (int col = 0; col < m && fila < n; col++) {
        int piv = -1;
        for (int i = fila; i < n; i++)
            if (a[i][col] % p) { piv = i; break; }
        if (piv < 0) continue;         // columna sin pivote: variable libre

        swap(a[piv], a[fila]);

        ll iv = inverso(a[fila][col], p);
        for (int j = col; j <= m; j++)
            a[fila][j] = a[fila][j] * iv % p;

        for (int i = 0; i < n; i++)
            if (i != fila && a[i][col] % p) {
                ll f = a[i][col];
                for (int j = col; j <= m; j++)
                    a[i][j] = ((a[i][j] - f * a[fila][j]) % p + p) % p;
            }

        donde[col] = fila++;
    }

    sol.assign(m, 0);                  // las variables libres quedan en 0
    for (int j = 0; j < m; j++)
        if (donde[j] >= 0) sol[j] = a[donde[j]][m] % p;

    // Una fila 0 = c con c != 0 significa que no hay solucion.
    incompatible = false;
    for (int i = fila; i < n; i++) {
        bool cero = true;
        for (int j = 0; j < m; j++)
            if (a[i][j] % p) { cero = false; break; }
        if (cero && a[i][m] % p) { incompatible = true; break; }
    }
    return fila;
}

// Determinante mod p de una matriz cuadrada. 0 significa que es singular.
ll determinante(vector<vector<ll>> a, ll p) {
    int n = a.size();
    ll det = 1;
    for (int c = 0; c < n; c++) {
        int piv = -1;
        for (int i = c; i < n; i++)
            if (a[i][c] % p) { piv = i; break; }
        if (piv < 0) return 0;
        if (piv != c) { swap(a[piv], a[c]); det = (p - det) % p; }   // cada swap cambia el signo

        det = det * a[c][c] % p;
        ll iv = inverso(a[c][c], p);
        for (int i = c + 1; i < n; i++) {
            ll f = a[i][c] * iv % p;
            for (int j = c; j < n; j++)
                a[i][j] = ((a[i][j] - f * a[c][j]) % p + p) % p;
        }
    }
    return det;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const ll P = 1000000007;
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<ll>> a(n, vector<ll>(m + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++) { cin >> a[i][j]; a[i][j] = ((a[i][j] % P) + P) % P; }

    vector<ll> sol;
    bool incompatible;
    int rango = gauss(a, m, sol, incompatible, P);

    if (incompatible) {
        cout << "sin solucion\n";
    } else {
        cout << "rango " << rango << ", soluciones = P^" << (m - rango) << "\n";
        for (int j = 0; j < m; j++) cout << sol[j] << " \n"[j == m - 1];
    }
    return 0;
}
