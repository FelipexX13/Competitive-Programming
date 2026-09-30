# <3
# Tema: LeetCode Hub / DP de Intervalos con Binaria
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3414 "Maximum Score of Non-Overlapping Intervals": escoger hasta 4 intervalos que no
# se traslapen maximizando el peso, y devolver los indices mas pequenos en orden lexicografico.
# Tecnica: ordenar por extremo DERECHO y dp[i][j] = mejor puntaje usando los primeros i
# intervalos con j escogidos. Para saltar a los compatibles se usa bisect_left, que encuentra
# el primer intervalo que termina antes de que empiece el actual.
# El desempate lexicografico se arrastra en una lista de indices paralela a la dp, que es la
# parte molesta del problema.

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        arr = [
            (intervals[i][1], intervals[i][0], intervals[i][2], i)
            for i in range(n)
        ]
        # Sort by right endpoint.
        arr.sort(key=lambda x: x[0])

        dp = [[0] * 5 for _ in range(n + 1)]
        indices = [[[] for _ in range(5)] for _ in range(n + 1)]

        for i in range(n):
            r, l, weight, idx = arr[i]
            # Use binary search to find intervals whose right endpoints are smaller than l.
            k = bisect_left(arr, (l,), hi=i)

            for j in range(1, 5):
                s1 = dp[i][j]
                s2 = dp[k][j - 1] + weight
                if s1 > s2:
                    dp[i + 1][j] = dp[i][j]
                    indices[i + 1][j] = indices[i][j].copy()
                    continue

                new_index = indices[k][j - 1].copy()
                new_index.append(idx)
                new_index.sort()
                if s1 == s2 and indices[i][j] < new_index:
                    new_index = indices[i][j].copy()
                dp[i + 1][j] = s2
                indices[i + 1][j] = new_index

        return indices[n][4]