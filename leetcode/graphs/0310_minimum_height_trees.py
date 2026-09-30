from collections import defaultdict, deque

class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:

        if n == 1:
            return [0]

        grafo = defaultdict(list)
        grado = [0] * n

        for u, v in edges:
            grafo[u].append(v)
            grafo[v].append(u)
            grado[u] += 1
            grado[v] += 1

        cola = deque()

        for i in range(n):
            if grado[i] == 1:
                cola.append(i)

        restantes = n

        while restantes > 2:
            hojas = len(cola)
            restantes -= hojas

            for _ in range(hojas):
                hoja = cola.popleft()

                for vecino in grafo[hoja]:
                    grado[vecino] -= 1
                    if grado[vecino] == 1:
                        cola.append(vecino)

        return list(cola)
