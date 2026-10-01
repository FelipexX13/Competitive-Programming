// <3
// Tema: Implementation / Maximizar Area del Rectangulo Envolvente
// Resumen: Dados unos reyes en el plano y k movimientos, maximizar el area del rectangulo que
// los encierra a todos
// Detalle: Resuelve "Kings Conquest" (problema K, Regionals 2025): dados unos reyes en el plano
// y k movimientos, maximizar el area del rectangulo que los encierra a todos. Solo importa el
// BOUNDING BOX, o sea minX, maxX, minY, maxY: el area es (ancho)*(alto) y los reyes de adentro
// no cambian nada. Con esa reduccion hay dos formas de gastar los k movimientos: - bestTwoKing:
// repartir los k entre ancho y alto, probando las k+1 divisiones posibles. Sale de estirar la
// caja por lados opuestos. - bestOneKing: mover UN rey hacia una de las cuatro diagonales (+-k,
// +-k) y recalcular la caja. Cubre el caso en que conviene sacar un solo rey lejos en vez de
// repartir. Se toma el maximo de las dos. El caso n == 1 va aparte: con un solo rey el area es
// 1 y las formulas no aplican. OJO CON EL DESBORDE: el area es ancho por alto y las coordenadas
// pueden ser grandes, asi que todo va en long long. Es el tipo de problema donde la respuesta
// cabe pero el producto intermedio no, si se descuida el tipo. El +1 en w y h es porque se
// cuentan CASILLAS y no distancias: de la coordenada 3 a la 7 hay 5 casillas, no 4. OJO: usa
// structured bindings (auto [a, b]), que piden C++17. En el juez compila, pero con un g++ viejo
// hay que volver a .first y .second.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SIZE(c) int((c).size())
#define forn(i,n) for(int i = 0 ; i < n ; i++ )

const int DIGITS = 10;

ll bestTwoKing(ll w, ll h, ll k)
{
    ll maxi = -1;

    forn(a, k + 1)
    {
        maxi = max(maxi, (w + a) * (h + k - a));
    }

    return maxi;
}

ll bestOneKing(vector<pair<ll,ll>>& reyes,
               ll minX, ll maxX,
               ll minY, ll maxY,
               ll w, ll h, ll k)
{
    ll best = w * h;

    vector<pair<ll,ll>> movimientos = {
        {-k, -k},
        {-k,  k},
        { k, -k},
        { k,  k}
    };

    for(auto [x, y] : reyes)
    {
        for(auto [dx, dy] : movimientos)
        {
            ll nx = x + dx;
            ll ny = y + dy;

            ll wc = max(maxX, nx) - min(minX, nx) + 1;
            ll hc = max(maxY, ny) - min(minY, ny) + 1;

            ll opcion = wc * hc;

            best = max(best, opcion);
        }
    }

    return best;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,k;
    cin >> n >> k;

    vector<pair<ll,ll>> reyes(n);

    forn(i,n)
    {
        cin >> reyes[i].first  >> reyes[i].second;
    }

    if(n==1)
    {
        cout << 1 << endl;
        return 0;
    }

    ll maxX = LLONG_MIN;
    ll maxY = LLONG_MIN;
    ll minX = LLONG_MAX;
    ll minY = LLONG_MAX;

    for (auto [x, y] : reyes) {
        maxX = max(maxX, x);
        maxY = max(maxY, y);
        minX = min(minX, x);
        minY = min(minY, y);
    }

    ll w = maxX - minX + 1;
    ll h = maxY - minY +1;

    ll one = bestOneKing(reyes, minX, maxX, minY, maxY, w, h, k);
    ll two = bestTwoKing(w, h, k);

    cout << max(one, two) << endl;


    return 0;
}


