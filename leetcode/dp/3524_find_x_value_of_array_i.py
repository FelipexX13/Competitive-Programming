# <3
# Tema: LeetCode Hub / DP sobre Residuos
# Resumen: Para cada residuo, cuantos subarreglos tienen producto congruente con ese residuo modulo k
# O: (n*k), un vector de residuos por posicion
# Detalle: LeetCode 3524 "Find X Value of Array I": para cada residuo, cuantos subarreglos
# tienen producto congruente con ese residuo modulo k. Tecnica: dp[i][r] = cuantos subarreglos
# que TERMINAN en i dejan residuo r. Cada uno se extiende de dp[i-1] multiplicando por nums[i]
# mod k, mas el que empieza en i. Al final se acumula. Es la version sin segment tree del 3525
# que esta en la carpeta segment_tree. OJO: usa try/except en vez de revisar si i es 0.

class Solution:
    def resultArray(self, nums: List[int], k: int) -> List[int]:
        result = [0] * k
        dp = {}
        for i in range(0,len(nums)):
            dp[i] = [0]*k
            dp[i][nums[i]%k] += 1
            for j in range(k):
                try:
                    if(dp[i-1][j] != 0):
                        res = (j*(nums[i]%k))%k
                        dp[i][res] += dp[i-1][j]
                except:
                    a = 1
            for j in range(k):
                result[j] += dp[i][j]

        return result


        