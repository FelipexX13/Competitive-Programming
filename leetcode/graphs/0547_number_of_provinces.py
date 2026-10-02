# <3
# Tema: LeetCode Hub / Componentes Conexas
# Resumen: Cuantos grupos de ciudades conectadas hay
# O: (n^2), que es leer la matriz de adyacencia
# Detalle: LeetCode 547 "Number of Provinces": cuantos grupos de ciudades conectadas hay.
# Tecnica: contar componentes conexas con DFS y un set de visitados. Cada vez que se arranca un
# DFS nuevo se suma una componente. OJO: recorre los nodos del diccionario graph, no el rango
# 0..n-1. Si una ciudad no tiene ninguna arista no queda en el diccionario; aca no falla porque
# la matriz siempre marca la diagonal, pero con lista de adyacencia habria que recorrer
# range(n).

from collections import defaultdict
class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        graph = defaultdict(list)
        for i in range(len(isConnected)):
            for j in range(len(isConnected)):
                if isConnected[i][j] == 1:
                    graph[i].append(j)
                    graph[j].append(i)
        visited = set()
        def dfs(curr):
            visited.add(curr)
            for node in graph[curr]:
                if node not in visited:
                    dfs(node)
        res = 0
        for node in graph:
            if node not in visited:
                dfs(node)
                res+=1
        return res
