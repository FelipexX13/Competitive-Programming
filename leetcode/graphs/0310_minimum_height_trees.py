# <3
# Tema: LeetCode Hub / Pelar Hojas (Centro del Arbol)
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 310 "Minimum Height Trees": las raices que dan el arbol de altura minima.
# Tecnica: pelar hojas por capas. Se meten a la cola todos los nodos de grado 1, se quitan todos
# a la vez, aparecen hojas nuevas, y se repite hasta que queden 1 o 2 nodos: esos son el CENTRO
# del arbol y la respuesta.
# Un arbol siempre tiene uno o dos centros, nunca tres, y eso es lo que justifica el while > 2.
# El mismo pelado por capas sirve para el diametro y para varios problemas de arboles.

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
