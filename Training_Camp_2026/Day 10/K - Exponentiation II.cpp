// <3
// Tema: Math / Exponenciacion Modular (Torre de Exponentes)
// Resuelve "Exponentiation II": calcula a^(b^c) modulo 1e9+7 para n consultas, con
// a, b, c hasta 1e9, donde el exponente b^c es demasiado grande para calcularlo
// directamente. Usa el Pequeno Teorema de Fermat: como MOD es primo, a^(MOD-1) = 1
// (para a no multiplo de MOD), asi que el exponente de la torre puede reducirse modulo
// MOD-1 antes de aplicarlo; el codigo llama expmod(b, c, MOD-1) para obtener ese
// exponente reducido y luego expmod(a, ese_valor, MOD) para el resultado final,
// reutilizando la misma exponenciacion binaria (fast power) para ambos niveles.

#include <iostream>
using namespace std;
typedef long long ll;
ll MOD = 1000000007;

ll expmod(ll b, ll e, ll m) 
{
    ll ans = 1;
    while (e) {
        if (e&1) ans = (1ll*ans*b) % m;
        b = (1ll*b*b) % m;
        e /= 2;
    }
    return ans;
}


int main()
{
    ll n; cin >> n;
    
    while(n--)
    {
        ll a , b , c; cin >> a >> b >> c;
        
        cout<< expmod(a,expmod(b,c,MOD-1),MOD)<< endl;
    }

    return 0;
}