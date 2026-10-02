// <3
// Tema: CSES / Mobius (Inversion para Contar Coprimos)
// Resumen: Cuantos pares del arreglo son coprimos entre si
// O: (maxValue log maxValue) la suma armonica, (maxValue) la criba lineal
// Uso: mu = mobius(maxValue); ans = suma de mu[d] * C(multiplos de d, 2)
// Detalle: Contar pares coprimos de frente es O(n^2). La inversion de Mobius le da la vuelta:
// en vez de contar los coprimos, se cuentan los pares que comparten un divisor d y se suman con
// el signo mu[d], que cancela lo que se conto de mas. La formula es: respuesta = suma sobre d
// de mu[d] * C(cuantos multiplos de d hay, 2). Los d con mu[d] = 0 (los que tienen un primo al
// cuadrado) se saltan, que es la mitad del ahorro. mu se calcula con CRIBA LINEAL, que de paso
// da el menor factor primo y corre en O(n) de verdad, no O(n log log n). El break cuando i % p
// == 0 es lo que garantiza que cada compuesto se tache UNA sola vez. El ciclo de countMultiples
// es la suma armonica n/1 + n/2 + n/3 + ... = n log n.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 1e6;

// --------------------------------------------------
// Funcion de Mobius usando criba lineal
// --------------------------------------------------

vector<int> mobius(int n)
{
    vector<int> mu(n + 1);
    vector<int> primes;
    vector<bool> composite(n + 1, false);

    mu[1] = 1;

    for(int i = 2; i <= n; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
            mu[i] = -1;
        }

        for(int p : primes)
        {
            if(i * p > n)
                break;

            composite[i * p] = true;

            if(i % p == 0)
            {
                mu[i * p] = 0;
                break;
            }

            mu[i * p] = -mu[i];
        }
    }

    return mu;
}

// --------------------------------------------------
// Cuenta cuantos elementos del arreglo son divisibles
// por d
// --------------------------------------------------

int countMultiples(int d, int maxValue, vector<int>& freq)
{
    int cnt = 0;

    for(int x = d; x <= maxValue; x += d)
        cnt += freq[x];

    return cnt;
}

// --------------------------------------------------
// Cuenta los pares coprimos
// --------------------------------------------------

ll countCoprimePairs(vector<int>& freq, vector<int>& mu, int maxValue)
{
    ll ans = 0;

    for(int d = 1; d <= maxValue; d++)
    {
        if(mu[d] == 0)
            continue;

        int cnt = countMultiples(d, maxValue, freq);

        ll pairs = 1LL * cnt * (cnt - 1) / 2;

        ans += 1LL * mu[d] * pairs;
    }

    return ans;
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> freq(MAXN + 1);

    int maxValue = 0;

    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        freq[x]++;
        maxValue = max(maxValue, x);
    }

    vector<int> mu = mobius(maxValue);

    cout << countCoprimePairs(freq, mu, maxValue) << '\n';

    return 0;

}
