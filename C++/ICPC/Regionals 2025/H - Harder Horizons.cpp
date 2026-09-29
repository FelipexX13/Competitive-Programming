// <3
// Tema: Implementation / Conteo de Records
// Resuelve "Harder Horizons" (problema H, Regionals 2025): cuenta cuantos elementos son mayores que
// TODOS los anteriores, o sea los "records" o maximos de prefijo.
// Una sola pasada llevando el maximo visto: si el actual lo supera, se cuenta y se actualiza. O(n)
// y memoria O(1), sin guardar el arreglo.
// El maxi arranca en -1 en vez de 0, que importa si los valores pueden ser 0: con maxi = 0 un primer
// elemento igual a 0 no se contaria. Si los valores pudieran ser negativos habria que arrancar en
// LLONG_MIN, o tratar el primer elemento aparte.
// Ojo con el ESTRICTO: se cuenta solo si x > maxi. Si el enunciado considerara record a un empate
// habria que usar >=, y es el tipo de detalle que cambia la respuesta sin que el codigo se vea
// distinto.
// Comprobado a mano: con 1 3 2 5 4 los records son 1, 3 y 5, o sea 3.
// El mismo barrido sirve para "cuantas veces cambia el maximo", "desde cuantas posiciones se ve el
// horizonte" y los problemas de edificios que tapan a otros.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    ll maxi = -1;
    ll res = 0;
    while(n--)
    {
        ll x; cin >> x;
        if(x>maxi)
        {
            res++;
            maxi = x;
        }

    }

    cout << res << endl;

    return 0;
}
