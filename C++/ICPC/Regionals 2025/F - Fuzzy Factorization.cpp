// <3
// Tema: Number Theory / Factorizacion de un Numero Gigante Redondeado
// Resumen: Factorizar un numero que llega como cadena y que esta redondeado
// Detalle: Resuelve "Fuzzy Factorization" (problema F, Regionals 2025): factorizar un numero
// que llega como cadena y que esta redondeado, o sea que todo lo que sigue despues de los
// primeros digitos significativos son ceros. LA OBSERVACION QUE LO RESUELVE: si el numero tiene
// D digitos y solo los primeros 10 son significativos, entonces vale (primeros 10 digitos) *
// 10^(D-10). Y 10^k aporta exactamente k factores 2 y k factores 5, sin tener que tocar el
// numero grande. Por eso el primer for solo suma +1 al 2 y al 5 por cada digito de mas. Lo que
// queda es factorizar Y, un numero de a lo sumo 10 digitos, con division por tentativa hasta la
// raiz: O(sqrt(Y)) = unas 10^5 operaciones. El if(Y > 1) del final es OBLIGATORIO: si despues
// de dividir por todo hasta la raiz queda algo mayor que 1, ese resto es un primo y hay que
// contarlo. Olvidarlo es el error mas comun de esta plantilla, y solo se nota cuando el numero
// tiene un factor primo grande. El map deja los primos ordenados automaticamente, que es lo que
// pide la salida, y ademas fusiona los 2 y los 5 que vienen de las dos fuentes (los ceros del
// final y la factorizacion de Y).

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SIZE(c) int((c).size())
#define forn(i,n) for(int i = 0 ; i < n ; i++ )

const int DIGITS = 10;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;

    cin >> s;

    map<ll,int> f;
    forn(t,SIZE(s)-DIGITS)
    {
        f[2]++;
        f[5]++;
    }
    ll Y = stoll(s.substr(0,min(10, SIZE(s))));

    for(ll p = 2; p*p <= Y;p++)
    {
        while(Y % p == 0)
        {
            Y /= p;
            f[p]++;

        }
    }

    if(Y>1)
        f[Y]++;


    cout << SIZE(f) << "\n";
    for(auto it : f)
        cout << it.first << " " << it.second << "\n";

    return 0;
}


