# <3
# Tema: LeetCode Hub / DSU sobre Parejas
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2) en el peor caso: el find no comprime caminos
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 765 "Couples Holding Hands": intercambios minimos para que cada pareja quede junta.
# Tecnica: se piensa por SILLAS, no por personas. Cada par de sillas (0,1), (2,3), ... es un
# nodo, y si las dos personas sentadas ahi son de parejas distintas se unen los dos nodos con
# DSU. La respuesta es la suma de (tamano del grupo - 1) sobre todos los grupos. Un ciclo de k
# parejas mal sentadas se arregla con k-1 intercambios, y eso es lo que se esta sumando.

from collections import defaultdict
class Solution:
    def minSwapsCouples(self, row: List[int]) -> int:
        n = len(row)
        parent = [i for i in range(n//2)]
        def find(i):
            if parent[i] == i:
                return i
            return find(parent[i])
        def unite(i, j):
            irep = find(i)
            jrep = find(j)
            parent[irep] = jrep
        def get_groups():
            groups = defaultdict(list)
            for element in parent:
                root = find(element)
                groups[root].append(element)
            return list(groups.values())
            
        coach = [-1] * (n)

        for i, val in enumerate(row):
            coach[val] = i//2

        graph = defaultdict(list)
        for i in range(0, n-1, 2):
            curr = coach[i]
            nxt = coach[i+1]
            if curr != nxt:
                unite(curr, nxt)
        groups = get_groups()
        res = 0
        for i in groups:
            res += len(i)-1
        return res
