# <3
# Tema: LeetCode Hub / Clonar Grafo con Diccionario
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n+m), un DFS con el mapa original -> copia
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 133 "Clone Graph": copia profunda de un grafo no dirigido. Tecnica: DFS con un
# diccionario original -> copia. Antes de recorrer los vecinos se registra la copia en el
# diccionario, y ese orden es lo que evita el ciclo infinito cuando el grafo tiene ciclos. Si el
# nodo ya esta en el mapa se devuelve la copia que ya existia. Es el mismo patron que pide
# LeetCode 138 (lista con puntero random).

class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:

        if not node:
            return None

        visited = {}
        # original -> copia

        def creator(curr):

            if curr in visited:
                return visited[curr]

            copy = Node(curr.val)
            visited[curr] = copy

            for nxt in curr.neighbors:
                copy.neighbors.append(creator(nxt))

            return copy

        return creator(node)
