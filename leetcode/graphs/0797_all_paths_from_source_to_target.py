# <3
# Tema: LeetCode Hub / Backtracking de Caminos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (2^n * n) en el peor caso, porque esa es la cantidad de caminos
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 797 "All Paths From Source to Target": todos los caminos del nodo 0 al ultimo en un
# DAG. Tecnica: DFS con backtracking. path.append al entrar, path.pop al salir, y cuando se
# llega al destino se guarda una COPIA de path (sin el .copy() se guardaria la misma lista que
# sigue cambiando, que es el error clasico). Aca marca ARISTAS visitadas; en un DAG no hace
# falta marcar nada, basta el backtracking.

from collections import deque
class Solution:
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
            visited = set()
            res = []
            path = []
            def dfs(curr, par):
                path.append(curr)
                if curr == len(graph)-1:
                    res.append(path.copy())
                for node in graph[curr]:
                    if (curr, node) in visited:
                        continue
                    visited.add((curr, node))
                    dfs(node, curr)
                if par != -1:
                    visited.remove((par, curr))
                path.pop()
            dfs(0, -1)
            return res
