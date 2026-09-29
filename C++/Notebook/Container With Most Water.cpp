// <3
// Tema: Greedy / Two Pointers (Container With Most Water)
// Paredes verticales de altura h[i] en la posicion i: elegir dos que, junto con el eje x,
// formen el recipiente de mayor area (j - i) * min(h[i], h[j]). Fuerza bruta es O(n^2);
// con dos punteros desde los extremos es O(n).
// Por que se mueve la pared MAS BAJA: el agua queda topada por ella. Cualquier recipiente entre
// esa pared y una interior es mas angosto y sigue topado por la misma altura (o menos), asi
// que nunca supera al actual: esa pared ya dio su mejor recipiente y se puede descartar.
// Si miden lo mismo, ninguna de las dos mejora con una pared interior: mover cualquiera.
// El area puede pasar de 2^31 (1e9 * 1e5): usar long long.
// No confundir con Trapping Rain Water (el agua que retienen TODAS las barras): tambien es de
// dos punteros, pero en cada posicion suma min(maxIzq, maxDer) - h[i].

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// {area maxima, {i, j}} (i = j = -1 si hay menos de dos paredes)
pair<ll, pair<int, int>> maxArea(const vector<ll> &h)
{
    int l = 0, r = (int)h.size() - 1, bi = -1, bj = -1;
    ll best = 0;
    while (l < r)
    {
        ll a = (ll)(r - l) * min(h[l], h[r]);
        if (a > best || bi == -1)
        {
            best = a;
            bi = l;
            bj = r;
        }
        if (h[l] < h[r]) l++;
        else r--;
    }
    return {best, {bi, bj}};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> h(n);
    for (auto &x : h) cin >> x;

    auto r = maxArea(h);
    cout << r.first << "\n";
    cout << r.second.first << " " << r.second.second << "\n";
    return 0;
}
