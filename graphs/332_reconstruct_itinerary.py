from collections import defaultdict

class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        def encontrar_camino_euleriano(grafo, inicio="JFK"):
            grafo_copia = {k: sorted(list(v), reverse=True) for k, v in grafo.items()}
            
            pila = [inicio]
            camino = []

            while pila:
                nodo_actual = pila[-1]
                if nodo_actual in grafo_copia and grafo_copia[nodo_actual]:
                    siguiente_nodo = grafo_copia[nodo_actual].pop()
                    pila.append(siguiente_nodo)
                else:
                    # Si no hay más aristas salientes, fijamos el nodo en el camino
                    camino.append(pila.pop())

            camino.reverse()
            return camino

        itinerarios = {
            "JFK": ["SFO", "ATL"],
            "SFO": ["ATL"],
            "ATL": ["JFK", "SFO"]
        }

        graph = defaultdict(list)
        for a, b in tickets:
            graph[a].append(b)
        for node in graph:
            graph[node].sort()

        sol = encontrar_camino_euleriano(graph)

        return sol
