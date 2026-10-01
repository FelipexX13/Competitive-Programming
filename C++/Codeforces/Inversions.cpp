// <3
// Tema: Combinatorics / Conteo de Inversiones (cadena repetida)
// Resumen: Cuenta las inversiones de S repetida N veces (N hasta 1e12) modulo 1e9+7
// O: (n log n) con Fenwick sobre la cadena repetida
// Detalle: Cuenta las inversiones de S repetida N veces (N hasta 1e12) modulo 1e9+7, es decir
// pares i<j donde la letra de i va despues en el alfabeto que la de j. No se puede construir la
// cadena, asi que se cuenta la contribucion de cada posicion por separado. Una posicion i con
// letra c aporta dos cosas: dentro de su propia copia aporta suf = cuantas letras menores que c
// hay de i en adelante, y eso ocurre igual en las N copias (N*suf); contra las copias
// posteriores le sirven TODAS las letras menores que c de la cadena completa (freqGod[c]), una
// vez por cada par ordenado de copias, o sea N(N-1)/2. freqAtras[i] guarda cuantas letras
// menores que cada letra quedan desde i hasta el final, y freqGod acumula las frecuencias
// globales. La division entre 2 va con inverso modular (Fermat, modpow(b, MOD-2)) porque
// N(N-1)/2 ya se calcula en modulo. Nota: el if de freqGod == freqAtras es redundante, las dos
// ramas dan el mismo valor (cuando suf == freqGod[c], N(N+1)/2*freqGod == N(N-1)/2*freqGod +
// N*suf).

#include <bits/stdc++.h>
using namespace std;

long long MOD = 1000000007;

long long modpow(long long a, long long e) {
    long long ans = 1;

    while (e) {
        if (e & 1)
            ans = ans * a % MOD;

        a = a * a % MOD;
        e >>= 1;
    }

    return ans;
}

long long division_mod(long long a, long long b) {
    return a % MOD * modpow(b, MOD - 2) % MOD;
}



int main()
{
    string s; cin >> s;
    long long n; cin >>n;

    vector<vector<long long>> freqAtras;
    vector<long long> freq(26,0);
    vector<long long> vectorsito(26,0);

    for(long long i = s.size()-1; i >=0;i--)
    {
        char letra = s[i];
        freq[letra-'0'-49]++;
        for(long long j = 0; j < 26 ; j++)
        {
            if(letra-'0'-49 <j)
            {
                vectorsito[j]++;
            }
        }
        freqAtras.push_back(vectorsito);
    }

    vector<long long> freqGod(26,0);
    long long sum = 0;
    for(long long i =1 ; i <26; i++)
    {
        sum += freq[i-1];
        freqGod[i] = sum;
    }


    long long GOD = 0;
    for(long long i = 0 ; i < s.size();i++)
    {
        if(freqGod[s[i]-'0'-49] == freqAtras[s.size()-i-1][s[i]-'0'-49])
        {
            GOD = (GOD + division_mod((n % MOD) * ((n + 1) % MOD) % MOD  , 2) * freqGod[s[i]-'0'-49] % MOD) % MOD;
        }
        else
        {
            GOD = (GOD + division_mod(((n-1) % MOD) * ((n) % MOD) % MOD  , 2) * freqGod[s[i]-'0'-49] % MOD) % MOD;
            GOD = (GOD + (freqAtras[s.size()-i-1][s[i]-'0'-49] * n) % MOD ) % MOD;
        }


    }

    cout << GOD << endl;

    return 0;
}
