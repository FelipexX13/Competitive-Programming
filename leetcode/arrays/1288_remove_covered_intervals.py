# <3
# Tema: LeetCode Hub / Intervalos Cubiertos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2); ordenando bien seria (n log n)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1288 "Remove Covered Intervals": cuantos intervalos quedan despues de borrar los que
# estan contenidos en otro. Tecnica: comparar todos los pares, O(n^2). La version buena: ordenar
# por inicio creciente y, en empate, por final DECRECIENTE. Asi basta recordar el mayor final
# visto, y todo intervalo con final menor o igual esta cubierto. O(n log n) y sin comparar
# pares. Ese criterio de desempate es el detalle que la gente olvida.

class Solution:
    def removeCoveredIntervals(self, intervals: List[List[int]]) -> int:
        n = len(intervals)
        deleted = set()
        for i in range(len(intervals)):
            for j in range(len(intervals)):
                if i != j:
                    if intervals[i][0] <= intervals[j][0] and intervals[i][1] >= intervals[j][1] and (intervals[j][0], intervals[j][1]) not in deleted:
                        n -= 1
                        deleted.add((intervals[j][0], intervals[j][1]))
        return n