# <3
# Tema: LeetCode Hub / DFS con Memoizacion en Matriz
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 329 "Longest Increasing Path in a Matrix": el camino mas largo que siempre sube.
# Tecnica: DFS con memoizacion. Como solo se puede ir a celdas MAYORES, el grafo no tiene ciclos
# y se puede memoizar sin peligro: dicc[(i,j)] guarda el camino mas largo que arranca ahi. Esa
# es la idea clave, la condicion de crecer es la que vuelve el grafo un DAG.

from collections import defaultdict

class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        paths = set()
        for i in range(len(matrix)):
            for j in range(len(matrix[i])):
                paths.add((i,j))
        dicc = defaultdict(int)
        def explore(i,j):
            best = 1
            if i+1 < len(matrix) and matrix[i+1][j] > matrix[i][j]:
                if (i+1, j) in paths:
                    best = max(best, 1 + explore(i+1, j))
                    paths.discard((i+1, j))
                else:
                    best = max(best, 1 +  dicc[(i+1, j)])
            if i-1 >= 0 and matrix[i-1][j] > matrix[i][j]:
                if (i-1, j) in paths:
                    paths.discard((i-1, j))
                    best = max(best, 1 + explore(i-1, j))
                else:
                    best = max(best, 1 +  dicc[(i-1, j)])
            if j+1 < len(matrix[i]) and matrix[i][j+1] > matrix[i][j]:
                if (i, j+1) in paths:
                    paths.discard((i, j+1))
                    best = max(best, 1 + explore(i, j+1))
                else:
                    best = max(best, 1 +  dicc[(i, j+1)])
            if j-1 >= 0 and matrix[i][j-1] > matrix[i][j]:
                if (i, j-1) in paths:
                    paths.discard((i, j-1))
                    best = max(best, 1 + explore(i, j-1))
                else:
                    best = max(best, 1 + dicc[(i, j-1)])
            dicc[(i, j)] = best
            return best

        while(True):
            if(len(paths) > 0):
                nextP = paths.pop()
                explore(nextP[0], nextP[1])
            else:
                break
        return max(dicc.values())
