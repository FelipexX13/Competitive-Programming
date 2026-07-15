#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll K;
vector<ll> x; // 0-indexed internamente, x[i] = altura del segmento (i+1)

// Dado un candidato H, ¿existe algun p tal que reforzando en p,
// TODOS los segmentos queden con altura >= H?
bool feasible(ll H) {
    ll L = 0;              // mayor indice (1-indexado) con x[i] < H, o 0 si no hay ninguno
    ll U = LLONG_MAX;       // cota superior para p, viene de la condicion de "alcanzar" cada deficit

    for (int i = 1; i <= N; i++) {
        if (x[i-1] < H) {
            L = i; // como i crece, la ultima asignacion es el maximo indice con deficit
            // Necesitamos: K - (p - i) >= H - x[i-1]  =>  p <= i + K - H + x[i-1]
            ll candidate = (ll)i + K - H + x[i-1];
            U = min(U, candidate);
        }
    }

    ll lo = max((ll)1, L);
    ll hi = min((ll)N, U);
    return lo <= hi;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    x.resize(N);
    for (int i = 0; i < N; i++) cin >> x[i];

    ll lo = *min_element(x.begin(), x.end()); // siempre alcanzable (bonus >= 0 siempre)
    ll hi = *max_element(x.begin(), x.end()) + K; // cota superior segura

    ll ans = lo;
    while (lo <= hi) {
        ll mid = lo + (hi - lo) / 2;
        if (feasible(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << ans << "\n";
    return 0;
}