# <3
# Tema: LeetCode Hub / Buscar el Intervalo de la Derecha
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 436 "Find Right Interval": para cada intervalo, el de inicio mas pequeno que empiece
# despues de que este termine.
# Tecnica: para cada final se recorren todos los inicios buscando el menor que sea mayor o igual.
# Es O(n^2).
# La version buena: ordenar los inicios y hacer binaria (lower_bound) por cada final, O(n log n).

class Solution:
    def findRightInterval(self, intervals: list[list[int]]) -> list[int]:
        ic = {}

        for i in range(len(intervals)):
            if intervals[i][0] in ic:
                ic[intervals[i][0]].append(i)
            else:
                ic[intervals[i][0]] = [i]

        res = []

        for i in intervals:
            fin = i[1]

            mejor = float("inf")
            indice = -1

            for inicio in ic:
                if inicio >= fin and inicio < mejor:
                    mejor = inicio
                    indice = ic[inicio][0]

            res.append(indice)

        return res