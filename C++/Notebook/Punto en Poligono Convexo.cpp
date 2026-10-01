// <3
// Tema: Geometry / Punto en Poligono Convexo (O(log n))
// Resumen: Arma el casco convexo de un conjunto de puntos y luego responde muchas consultas del
// tipo "este punto esta...
// O: (n log n) el hull, (log n) cada consulta
// Uso: h = convexHull(p); inside(h,q) con h antihorario y sin colineales
// Detalle: Arma el casco convexo de un conjunto de puntos y luego responde muchas consultas del
// tipo "este punto esta dentro?" en O(log n) cada una, en vez de O(n) revisando arista por
// arista. Todo se hace con enteros (el cross devuelve long long), asi que no hay error de
// precision. El casco usa monotone chain de Andrew; descartar con cross <= 0 elimina los puntos
// colineales y deja solo los vertices reales, devolviendo el hull en sentido antihorario. La
// consulta triangula mentalmente el poligono en abanico desde h[0]: primero descarta el punto
// si cae fuera de las dos aristas extremas (h[0]-h[1] y h[0]-h[n-1]), y si no, busca
// binariamente el sector (h[0], h[lo], h[lo+1]) donde cae y comprueba de que lado esta de esa
// arista. Los cross con >= 0 hacen que el borde cuente como dentro. Contempla los casos
// degenerados en que el casco queda reducido a un punto o a un segmento.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct P { ll x, y; };

ll cross(const P&O, const P&A, const P&B){
    return (A.x-O.x)*(B.y-O.y) - (A.y-O.y)*(B.x-O.x);
}

vector<P> convexHull(vector<P> p){
    int n = p.size(), k = 0;
    sort(p.begin(), p.end(), [](const P&a, const P&b){
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    });
    p.erase(unique(p.begin(), p.end(), [](const P&a, const P&b){
        return a.x==b.x && a.y==b.y;
    }), p.end());
    n = p.size();
    if (n < 3) return p;

    vector<P> h(2*n);
    for (int i = 0; i < n; i++){                       // cadena inferior
        while (k >= 2 && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n-2, t = k+1; i >= 0; i--){           // cadena superior
        while (k >= t && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k-1);                                     // quita el repetido final
    return h;                                          // CCW, sin colineales
}

bool inside(const vector<P>& h, const P& q){
    int n = h.size();
    if (n == 1) return h[0].x==q.x && h[0].y==q.y;
    if (n == 2){                                       // segmento degenerado
        if (cross(h[0], h[1], q) != 0) return false;
        return min(h[0].x,h[1].x)<=q.x && q.x<=max(h[0].x,h[1].x)
            && min(h[0].y,h[1].y)<=q.y && q.y<=max(h[0].y,h[1].y);
    }
    if (cross(h[0], h[1], q)   < 0) return false;
    if (cross(h[0], h[n-1], q) > 0) return false;

    int lo = 1, hi = n-1;                              // busca el sector
    while (hi - lo > 1){
        int mid = (lo + hi) / 2;
        if (cross(h[0], h[mid], q) >= 0) lo = mid;
        else hi = mid;
    }
    return cross(h[lo], h[lo+1], q) >= 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L;
    while (cin >> L){
        vector<P> big(L);
        for (auto &b : big) cin >> b.x >> b.y;
        vector<P> h = convexHull(big);

        int S; cin >> S;
        int cnt = 0;
        for (int i = 0; i < S; i++){
            P q; cin >> q.x >> q.y;
            if (inside(h, q)) cnt++;
        }
        cout << cnt << "\n";
    }
    return 0;
}
