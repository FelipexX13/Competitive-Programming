// <3
// Tema: Binary Search / Busqueda Ternaria (Real y Entera)
// Resumen: Maximo o minimo de una funcion que sube y despues baja (unimodal), sin derivar
// O: (log rango) evaluaciones de f
// Uso: ternariaReal(lo, hi, f) y ternariaEntera(lo, hi, f) MAXIMIZAN; para minimizar, -f
// Detalle: Si f sube estrictamente hasta un punto y despues baja estrictamente, comparando
// f en dos puntos interiores m1 < m2 se puede descartar un tercio: si f(m1) < f(m2) el
// maximo no esta en [lo, m1]. En reales se hacen 200 iteraciones fijas: cada una deja 2/3
// del intervalo, asi que 100 dividen el rango por ~10^17.6 (10^18 queda en ~2.5, poco) y
// 200 por ~10^35. No usar un while con EPS: con rangos grandes puede no terminar nunca.
// En enteros NO conviene la ternaria de tercios (los +1 y -1 son una trampa): mejor binaria
// sobre la "derivada", buscando el primer m con f(m) >= f(m+1). Es exacta en log pasos.
// OJO con las MESETAS: si f tiene un tramo plano que NO es el maximo, ninguna de las dos
// sirve, porque comparando dos puntos iguales no se sabe hacia donde esta el pico.
// Senales de unimodal: distancia entre dos cosas que se mueven en linea recta (en funcion
// del tiempo), suma de |x - a_i| (convexa), costo = algo creciente + algo decreciente.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Argumento x en [lo, hi] que maximiza f (f unimodal en reales)
double ternariaReal(double lo, double hi, function<double(double)> f)
{
    for (int it = 0; it < 200; it++)
    {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) lo = m1;
        else hi = m2;
    }
    return (lo + hi) / 2;
}

// Entero x en [lo, hi] que maximiza f (estrictamente sube, despues estrictamente baja)
ll ternariaEntera(ll lo, ll hi, function<ll(ll)> f)
{
    while (lo < hi)
    {
        ll m = lo + (hi - lo) / 2;
        if (f(m) < f(m + 1)) lo = m + 1;   // todavia sube: el pico esta a la derecha
        else hi = m;
    }
    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
