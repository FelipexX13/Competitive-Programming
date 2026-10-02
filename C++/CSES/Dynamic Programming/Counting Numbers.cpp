// <3
// Tema: CSES / Digit DP con Estado 'ya Empezo'
// Resumen: Cuantos numeros entre a y b no tienen dos digitos iguales seguidos
// O: (digitos * 11 * 2 * 2 * 10), o sea constante para 10^18
// Uso: count(b) - count(a-1); el estado es (pos, digito previo, tight, started)
// Detalle: Digit DP con CUATRO cosas en el estado, y la cuarta es la que cuesta ver: pos (que
// digito se esta poniendo), prev (el digito anterior, 10 como 'ninguno'), tight (si el prefijo
// sigue pegado al de X) y started (si ya se puso un digito distinto de cero). started EXISTE
// POR LOS CEROS A LA IZQUIERDA: mientras no se empieza, poner otro cero no cuenta como 'dos
// iguales seguidos', porque esos ceros no son parte del numero. Sin esa bandera el 101 se
// contaria mal. El rango [a, b] se hace como siempre, count(b) - count(a-1).

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll dp[20][11][2][2];
bool vis[20][11][2][2];

vector<int> dig;

ll solve(int pos, int prev, bool tight, bool started)
{
    if(pos == dig.size())
        return 1;

    if(vis[pos][prev][tight][started])
        return dp[pos][prev][tight][started];

    vis[pos][prev][tight][started] = true;

    ll ans = 0;

    int limit = tight ? dig[pos] : 9;

    for(int d = 0; d <= limit; d++)
    {
        bool ntight = tight && (d == dig[pos]);

        if(!started && d == 0)
        {
            ans += solve(pos + 1, 10, ntight, false);
        }
        else
        {
            if(started && d == prev)
                continue;

            ans += solve(pos + 1, d, ntight, true);
        }
    }

    return dp[pos][prev][tight][started] = ans;
}

ll count(ll x)
{
    if(x < 0)
        return 0;

    string s = to_string(x);

    dig.clear();

    for(char c : s)
        dig.push_back(c - '0');

    memset(vis, false, sizeof(vis));

    return solve(0, 10, true, false);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    cin >> a >> b;

    cout << count(b) - count(a - 1) << '\n';
}
