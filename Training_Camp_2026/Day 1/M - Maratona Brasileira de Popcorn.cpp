// <3
// Tema: Greedy / Binary Search
// Resuelve "Maratona Brasileira de Popcorn" (Maratona de Programacao da SBC 2019, Day 1
// problem M): N bolsas de palomitas en fila deben repartirse en C tramos contiguos (uno por
// competidor), cada competidor come a lo sumo T unidades por segundo, y se quiere minimizar el
// tiempo total (el maximo de todas las bolsas que come cada competidor, dividido T). Busqueda
// binaria sobre la cota maxima S que puede cargar un competidor: la funcion gruposNecesarios
// hace un particionado greedy (como el problema clasico de asignacion de libros/pintores)
// contando cuantos tramos contiguos hacen falta para que ninguno supere S, y se busca el menor
// S factible con a lo sumo C tramos. La respuesta final es ceil(S / T).

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, c;
    long long t;
    cin >> n >> c >> t;
 
    vector<long long> p(n);
    long long lo = 0, hi = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        lo = max(lo, p[i]);   // la bolsa más grande fija una cota inferior
        hi += p[i];           // un solo competidor comiendo todo fija la cota superior
    }
 
    // Dada una cota S, calcula cuántos grupos contiguos (competidores)
    // se necesitan para que ningún grupo tenga suma mayor que S.
    auto gruposNecesarios = [&](long long S) -> long long {
        long long grupos = 1;
        long long acumulado = 0;
        for (int i = 0; i < n; i++) {
            if (acumulado + p[i] > S) {
                grupos++;
                acumulado = p[i];
            } else {
                acumulado += p[i];
            }
        }
        return grupos;
    };
 
    // Búsqueda binaria de la mínima "suma máxima" S alcanzable
    // usando a lo sumo C grupos (competidores).
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (gruposNecesarios(mid) <= c) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
 
    long long S = lo;                       // suma máxima óptima que come un competidor
    long long respuesta = (S + t - 1) / t;   // techo(S / T)
 
    cout << respuesta << "\n";
    return 0;
}