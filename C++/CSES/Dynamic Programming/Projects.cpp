// <3
// Tema: CSES / Weighted Interval Scheduling
// Resumen: Escoger proyectos que no se solapen maximizando la ganancia total
// O: (n log n), sort mas una binaria por proyecto
// Uso: ordenar por FIN; dp[i] = max(dp[i-1], dp[j] + p) con j = lower_bound del inicio
// Detalle: Es el interval scheduling CON PESOS, y no se resuelve con el greedy del clasico: ahi
// se maximiza la cantidad y basta tomar el que termina primero, aqui se maximiza la suma y hay
// que comparar. Se ordena por fin y dp[i] decide entre no tomar el proyecto i (dp[i-1]) o
// tomarlo, sumando su ganancia a dp[j], donde j es el primer proyecto que termina ANTES de que
// empiece el actual. Ese j sale con lower_bound sobre los finales ordenados, y es lo que evita
// el O(n^2). OJO: usa auto [a,b], que pide C++17.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Project
{
    ll a, b, p;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Project> projects(n);

    for(auto &[a, b, p] : projects)
        cin >> a >> b >> p;

    sort(projects.begin(), projects.end(),
        [](Project A, Project B)
        {
            return A.b < B.b;
        });

    vector<ll> ends(n);

    for(int i = 0; i < n; i++)
        ends[i] = projects[i].b;

    vector<ll> dp(n + 1, 0);

    for(int i = 1; i <= n; i++)
    {
        auto [a, b, p] = projects[i - 1];

        // Primer proyecto cuyo final >= a
        int j = lower_bound(ends.begin(), ends.end(), a)
                - ends.begin();

        dp[i] = max(
            dp[i - 1],
            dp[j] + p
        );
    }

    cout << dp[n] << '\n';
}
