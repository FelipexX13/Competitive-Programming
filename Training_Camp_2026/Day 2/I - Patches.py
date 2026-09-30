# <3
# Tema: Dynamic Programming / Binary Search
# Resuelve "Patches" (Maratona de Programacao da SBC 2013, problem I): una llanta de
# circunferencia C tiene N agujeros a distancias F_i desde una marca de referencia; hay dos
# tipos de parche, de largo T1 y T2, y cada parche cubre de forma continua todos los agujeros
# que caigan dentro de su longitud. Hay que cubrir todos los agujeros usando el menor largo
# total de parches.
# rec(voy) es una recursion memoizada sobre el indice del siguiente agujero sin cubrir: prueba
# colocar un parche de largo t1 o de largo t2 empezando en l[voy], usa bisect_right para hallar
# en O(log N) el primer agujero que ya queda fuera del parche, y se queda con el minimo entre
# ambas opciones (largo del parche mas lo que falte cubrir despues, rec(i1) o rec(i2)).

from bisect import bisect_right

memo = {}

def rec(voy):
    if voy == n:
        return 0

    if voy in memo:
        return memo[voy]

    i1 = bisect_right(l, l[voy] + t1)
    i2 = bisect_right(l, l[voy] + t2)

    ans = min(
        t1 + rec(i1),
        t2 + rec(i2)
    )

    memo[voy] = ans
    return ans


n, c, t1, t2 = map(int, input().split())
l = list(map(int, input().split()))

print(rec(0))
