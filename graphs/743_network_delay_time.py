import heapq
from collections import defaultdict

class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        def dijkstra(grafo, inicio):
            distancias = {nodo: float('inf') for nodo in range(1, n+1)}
            distancias[inicio] = 0
            cola = [(0, inicio)]
            
            while cola:
                dist_actual, nodo_actual = heapq.heappop(cola)
                
                if dist_actual > distancias[nodo_actual]:
                    continue
                    
                for vecino, peso in grafo[nodo_actual].items():
                    distancia = dist_actual + peso
                    if distancia < distancias[vecino]:
                        distancias[vecino] = distancia
                        heapq.heappush(cola, (distancia, vecino))
                        
            return distancias

        graph = defaultdict(dict)

        for u,v,w in times:
            graph[u][v] = w
        distances = dijkstra(graph, k).values() 
        res = 0
        for i in list(distances):
            if i > res:
                res = i
        if res == float('inf'):
            return -1
        else:
            return res
