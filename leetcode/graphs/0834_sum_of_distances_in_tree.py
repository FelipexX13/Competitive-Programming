# <3
# Tema: LeetCode Hub / Rerooting en Arbol
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 834 "Sum of Distances in Tree": para cada nodo, la suma de distancias a todos los
# demas. Tecnica: tres DFS. El primero calcula el TAMANO de cada subarbol, el segundo la
# respuesta de la raiz, y el tercero la propaga a los hijos con la formula clave: res[hijo] =
# res[padre] - tamano(hijo) + (n - tamano(hijo)) que dice que al mover la raiz un paso, los
# nodos del subarbol quedan uno mas cerca y el resto uno mas lejos. Esa es la tecnica de
# REROOTING y aparece mucho en arboles. OJO: dfs3 usa res[curr] != 0 como marca de ya calculado,
# que es fragil si la respuesta real fuera 0.

from collections import defaultdict
class Solution:
    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:
        if len(edges) == 0:
            return [0]
        tree = defaultdict(list)
        for a, b in edges:
            tree[a].append(b)
            tree[b].append(a)

        sizes = defaultdict(int)
        def dfs(curr, par):
            total = 1
            for node in tree[curr]:
                if node != par:
                    total += dfs(node, curr)
            sizes[curr] = total
            return total
        dfs(0, None)

        res = [0]*n
        def dfs2(curr, depth, par):
            res[0] += depth
            for node in tree[curr]:
                if node != par:
                    dfs2(node, depth+1, curr)
        dfs2(0, 0, None)

        def dfs3(curr, prev, par):
            currSum = 0
            if res[curr] != 0:
                currSum = res[curr]
            else:
                currSum = prev - sizes[curr] + (n-sizes[curr])
            res[curr] = currSum
            for node in tree[curr]:
                if node!= par:
                    dfs3(node, currSum, curr)
        dfs3(0, 0, None)
        return res
            
