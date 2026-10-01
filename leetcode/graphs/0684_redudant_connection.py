# <3
# Tema: LeetCode Hub / DSU (Union-Find)
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 684 "Redundant Connection": la arista que sobra en un arbol al que le agregaron una.
# Tecnica: DSU. Se van uniendo las aristas en orden y la PRIMERA que encuentre los dos extremos
# ya en el mismo grupo es la que cierra el ciclo, o sea la respuesta. OJO: el find no tiene
# compresion de caminos ni el union por tamano, asi que en el peor caso es O(n) por consulta y
# en Python puede reventar el limite de recursion. Con compresion queda casi O(1): if parents[x]
# != x: parents[x] = find(parents[x]).

class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        parents = {}
        for a,b in edges:
            parents[a] = a
            parents[b] = b
        def find(node):
            if parents[node] == node:
                return node
            return find(parents[node])
        def union(a,b):
            fatherA = find(a)
            fatherB = find(b)
            if fatherA == fatherB:
                return False
            parents[fatherA] = fatherB
            return True
        
        for a,b in edges:
            if not union(a,b):
                return [a,b]
