# <3
# Tema: LeetCode Hub / DP en Dos Cadenas
# Resumen: Cuantas subsecuencias de s son iguales a t
# O: (n*m) tiempo y memoria
# Detalle: LeetCode 115 "Distinct Subsequences": cuantas subsecuencias de s son iguales a t.
# Tecnica: dp[i][j] = de cuantas formas se forma t[j:] usando s[i:]. Si las letras coinciden hay
# dos opciones, usarla o no, y se SUMAN; si no coinciden solo queda avanzar en s. Los dp[i][n] =
# 1 son el caso base, t ya se termino. Va de atras hacia adelante, que es lo natural cuando el
# estado son sufijos.

class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        m, n = len(s), len(t)
        if m < n:
            return 0
        
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(m + 1):
            dp[i][n] = 1
        
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if s[i] == t[j]:
                    dp[i][j] = dp[i + 1][j + 1] + dp[i + 1][j]
                else:
                    dp[i][j] = dp[i + 1][j]
        
        return dp[0][0]