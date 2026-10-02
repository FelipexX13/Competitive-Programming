# <3
# Tema: LeetCode Hub / DP con Resta de Repetidos
# Resumen: Cuantas subsecuencias DISTINTAS tiene una cadena
# O: (n), duplicar y restar la aparicion previa
# Detalle: LeetCode 940 "Distinct Subsequences II": cuantas subsecuencias DISTINTAS tiene una
# cadena. Tecnica: cada letra nueva duplica las subsecuencias (con y sin ella), asi que dp =
# dp*2. Para no contar repetidas se RESTA el dp de la vez anterior que aparecio esa misma letra.
# El -1 del final quita la subsecuencia vacia. Cinco lineas, pero el patron duplicar y restar la
# aparicion previa vale mucho.

class Solution(object):
    def distinctSubseqII(self, S):
        dp = [1]
        last = {}
        for i, x in enumerate(S):
            dp.append(dp[-1] * 2)
            if x in last:
                dp[-1] -= dp[last[x]]
            last[x] = i

        return (dp[-1] - 1) % (10**9 + 7)