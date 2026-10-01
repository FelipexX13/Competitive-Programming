# <3
# Tema: LeetCode Hub / Coloreo a Dos Colores
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 785 "Is Graph Bipartite?": decir si el grafo se puede partir en dos grupos sin
# aristas internas. Tecnica: DFS pintando 1 y -1 alternado. Si alguna arista une dos nodos del
# MISMO color, no es bipartito. El ciclo externo por todos los nodos es porque el grafo puede
# venir desconectado. Bipartito equivale a no tener ciclos de longitud impar, y esto es la forma
# de verificarlo.

from collections import defaultdict
class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        colors = defaultdict(int)
        res = True
        visited = set()
        def dfs(curr):
            nonlocal res
            visited.add(curr)

            if curr not in colors:
                colors[curr] = 1

            for node in graph[curr]:
                if node not in colors:
                    colors[node] = -colors[curr]
                    dfs(node)
                elif colors[node] == colors[curr]:
                    res = False
        for i in range(len(graph)):
            if i not in visited:
                dfs(i)
        return res
