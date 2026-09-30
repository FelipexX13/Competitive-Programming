// <3
// Tema: Greedy / DP
// Resuelve "Exhibition of Clownfish" (Maratona de Programacao da SBC 2019, Day 1 problem E): N
// peceras con M machos y F hembras cada una; si al final de la noche una pecera queda con
// machos pero sin hembras, uno de ellos muta a hembra. Zelius puede mover un pez por noche entre
// peceras y quiere el numero minimo de movimientos para que todos los peces terminen siendo
// hembra. Para cada pecera define v = 1 + M - F (cuanto "aporta" dejarla vacia de machos vs.
// usarla como colector) y separa peceras vacias, solo-hembras y mixtas (con v positivo o
// negativo). Arma greedily una "familia" alrededor de un colector maximizando la suma de v de
// las mixtas positivas mas las vacias disponibles, y cuando faltan colectores vacios usa una DP
// tipo knapsack (dp[j] = costo minimo en v para "cubrir" un deficit de peso j) para decidir que
// peceras mixtas conviene sacrificar. El total de movimientos es 2*S menos el mejor ahorro
// encontrado (S = total de machos).

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if(!(cin >> n)) return 0;

    vector<long long> M(n), F(n);
    long long S = 0;                 // total males
    for(int i = 0; i < n; i++){
        cin >> M[i] >> F[i];
        S += M[i];
    }

    if(S == 0){ cout << 0 << "\n"; return 0; }  // ya todas hembras

    long long E = 0, femonly = 0, negmixed = 0;
    long long PosV = 0, PosM = 0;               // suma de v y de M sobre "mixtos positivos"
    long long bestSingle = LLONG_MIN;           // mejor v de una sola cámara
    vector<pair<long long,long long>> pos;       // (peso = M, valor = v) de mixtos con v>0

    for(int i = 0; i < n; i++){
        long long v = 1 + M[i] - F[i];
        bestSingle = max(bestSingle, v);
        if(M[i] == 0 && F[i] == 0) E++;                 // vacío
        else if(M[i] == 0) femonly++;                   // solo hembras
        else {                                          // mixto (M>0 => F>0 por restricción)
            if(v > 0){ PosV += v; PosM += M[i]; pos.push_back({M[i], v}); }
            else negmixed++;
        }
    }

    long long FM0 = S - PosM;   // machos libres provenientes de mixtos con v<=0

    // Familia principal: max sobre w in [0,E] de  bestPv(S-w) + w
    long long best_family = PosV + min(E, FM0);   // w <= FM0 : incluir todos los positivos

    if(E > FM0){
        long long T = E - FM0;                    // T <= E <= n <= 3000
        const long long INF = LLONG_MAX / 4;
        vector<long long> dp(T + 1, INF);
        dp[0] = 0;
        for(auto &pr : pos){                      // cover DP: min sum(v) para quitar >= j de peso
            long long w = pr.first, v = pr.second;
            for(long long j = T; j >= 0; j--){
                if(dp[j] < INF){
                    long long nj = (j + w >= T) ? T : (j + w);
                    if(dp[j] + v < dp[nj]) dp[nj] = dp[j] + v;
                }
            }
        }
        for(long long j = 1; j <= T; j++)
            if(dp[j] < INF)
                best_family = max(best_family, PosV + FM0 + (j - dp[j]));
    }

    bool family_valid = true;
    if(PosV == 0 && E == 0) family_valid = false;         // daría 0 cámaras

    // Caso frontera: TODOS los tanques son mixtos positivos -> hay que dejar 1 como drenaje
    if(E == 0 && femonly == 0 && negmixed == 0){
        long long minv = LLONG_MAX;
        for(auto &pr : pos) minv = min(minv, pr.second);
        best_family = PosV - minv;
        family_valid = true;
    }

    long long maxB = bestSingle;                          // cámara única (siempre válida, n>=2)
    if(family_valid) maxB = max(maxB, best_family);

    cout << (2 * S - maxB) << "\n";
    return 0;
}