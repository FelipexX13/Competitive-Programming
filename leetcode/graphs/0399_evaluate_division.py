# <3
# Tema: LeetCode Hub / Grafo con Pesos Multiplicativos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 399 "Evaluate Division": dadas razones a/b, responder consultas de otras razones.
# Tecnica: grafo donde la arista a -> b pesa a/b y la inversa b -> a pesa 1/v. La respuesta de
# una consulta es el PRODUCTO de los pesos del camino, asi que un DFS que multiplica lo
# resuelve. Traducir division a camino en grafo es el truco; el -1 marca que no hay camino. La
# otra forma es DSU con pesos, que responde en casi O(1) por consulta.

from collections import defaultdict

class Solution:
    def calcEquation(self, equations, values, queries):

        graph = defaultdict(list)

        for (a, b), v in zip(equations, values):
            graph[a].append((b, v))
            graph[b].append((a, 1 / v))

        def dfs(curr, target, visited):

            if curr == target:
                return 1

            visited.add(curr)

            for nxt, weight in graph[curr]:
                if nxt in visited:
                    continue

                ans = dfs(nxt, target, visited)

                if ans != -1:
                    return weight * ans

            return -1

        res = []

        for a, b in queries:

            if a not in graph or b not in graph:
                res.append(-1.0)
                continue

            res.append(dfs(a, b, set()))

        return res
