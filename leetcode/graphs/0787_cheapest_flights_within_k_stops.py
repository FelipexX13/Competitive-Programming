# <3
# Tema: LeetCode Hub / DP con Estado (nodo, saltos)
# Resumen: El vuelo mas barato con a lo mas k escalas
# O: (n*k*m) por los estados (nodo, saltos) memoizados
# Detalle: LeetCode 787 "Cheapest Flights Within K Stops": el vuelo mas barato con a lo mas k
# escalas. Tecnica: no es Dijkstra puro porque el limite de escalas mete una dimension mas. El
# estado es (nodo actual, vuelos restantes) y se memoiza con @cache. Ese decorador ahorra
# escribir la tabla a mano y vale la pena recordarlo en Python. La otra forma es Bellman-Ford
# limitado a k+1 rondas, que es la version clasica.

from collections import defaultdict
from functools import cache

class Solution:
    def findCheapestPrice(self, n, flights, src, dst, k):
        graph = defaultdict(list)

        for u, v, w in flights:
            graph[u].append((v, w))

        INF = float("inf")

        @cache
        def dp(curr, remaining):
            if curr == dst:
                return 0

            if remaining == 0:
                return INF

            ans = INF

            for nxt, cost in graph[curr]:
                ans = min(ans, cost + dp(nxt, remaining - 1))

            return ans

        ans = dp(src, k + 1)
        return -1 if ans == INF else ans
