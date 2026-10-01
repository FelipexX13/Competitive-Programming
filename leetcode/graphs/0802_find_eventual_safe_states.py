# <3
# Tema: LeetCode Hub / Nodos que No Llegan a un Ciclo
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n*(n+m)) por el visited.clear() de cada nodo; con tres colores es (n+m)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 802 "Find Eventual Safe States": los nodos desde los que todo camino termina en un
# nodo sin salidas. Tecnica: DFS que devuelve True si desde el nodo no se alcanza ningun ciclo,
# con el set safe como memoria de los ya confirmados. OJO: hace visited.clear() antes de cada
# nodo, asi que repite trabajo. Lo limpio es el DFS de tres colores (blanco, gris, negro) en una
# sola pasada, o Kahn sobre el grafo INVERTIDO.

class Solution:
    def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
        safe = set()
        visited = set()

        def dfs(curr):
            if curr in safe:
                return True

            if curr in visited:
                return False

            visited.add(curr)

            for node in graph[curr]:
                if not dfs(node):
                    visited.discard(curr)
                    return False

            visited.discard(curr)
            safe.add(curr)
            return True

        res = []

        for i in range(len(graph)):
            visited.clear()
            if dfs(i):
                res.append(i)

        return res
