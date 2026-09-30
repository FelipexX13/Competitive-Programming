# <3
# Tema: Dynamic Programming / Subset Sum (Knapsack)
# Resuelve "Karamell" (Maratona SBC de Programacao 2024, Problem K): Alice y Bob reciben N
# bolsas de caramelos que se reparten en el orden dado, entregando cada bolsa a quien tenga menos
# caramelos en ese momento (en caso de empate, a Alice); hay que encontrar un orden de las bolsas
# tal que ambos terminen con la misma cantidad de caramelos, o determinar que es imposible.
# El codigo primero descarta el caso de suma total impar. Luego usa una DP de subset-sum
# (dp[i][s], con bytearray por fila para ahorrar memoria) para determinar si existe un
# subconjunto de bolsas cuya suma sea la mitad del total, y reconstruye ese subconjunto (sub).
# Finalmente separa las bolsas en dos grupos (alice/bob) segun pertenezcan o no a ese subconjunto
# y las intercala de forma greedy, dandole siempre la siguiente bolsa al que menos lleva
# acumulado, reproduciendo la regla de reparto del enunciado para garantizar el empate final.

import sys
input = sys.stdin.readline
 
n = int(input())
ka = sorted(map(int, input().split()))
suma = sum(ka)
 
if suma % 2 != 0:
    print(-1)
else:
    mit = suma // 2
 
    # ---- subset-sum DP: reemplaza el rec exponencial ----
    # dp[i][s] = con los primeros i elementos se puede formar la suma s
    dp = [bytearray(mit + 1) for _ in range(n + 1)]
    dp[0][0] = 1
    for i in range(1, n + 1):
        w = ka[i - 1]
        cur = dp[i]
        prev = dp[i - 1]
        for s in range(mit + 1):
            if prev[s] or (s >= w and prev[s - w]):
                cur[s] = 1
 
    if not dp[n][mit]:
        print(-1)
    else:
        # reconstruyo el subconjunto que suma mit (queda como sub ordenado, igual que f[0])
        sub = []
        s = mit
        for i in range(n, 0, -1):
            w = ka[i - 1]
            if s >= w and dp[i - 1][s - w]:   # este elemento entra al subconjunto
                sub.append(w)
                s -= w
        sub.reverse()                          # ascendente, como lo esperaba tu código
 
        # ---- de aquí en adelante: TU MISMA reconstrucción ----
        alice = []
        bob = []
        pos = 0
        for j in range(len(ka)):
            if pos < len(sub) and sub[pos] == ka[j]:
                alice.append(j)
                pos += 1
            else:
                bob.append(j)
 
        alice1 = 0
        bob1 = 0
        posA = 0
        posB = len(bob) - 1
        imp = []
        for _ in range(len(ka)):
            if alice1 < bob1:
                v = ka[alice[posA]]; posA += 1
                alice1 += v
            else:
                v = ka[bob[posB]]; posB -= 1
                bob1 += v
            imp.append(str(v))
        print(" ".join(imp))