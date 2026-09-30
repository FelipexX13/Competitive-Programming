# <3
# Tema: LeetCode Hub / Binaria sobre la Respuesta en un DAG
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3620 "Network Recovery Pathways": maximizar el peso MINIMO de las aristas del camino,
# con el costo total del camino acotado por k.
# Tecnica: binaria sobre la respuesta. Se fija un umbral mid, se borran todas las aristas de peso
# menor, y con el orden topologico se calcula el camino mas BARATO que queda; si cabe en k, el
# umbral es alcanzable y se busca mas arriba.
# Maximizar un minimo casi siempre sale asi: binaria sobre el valor y una verificacion facil.
# El orden topologico es lo que permite el camino minimo en O(m) sin Dijkstra, porque es un DAG.

from collections import deque

class Solution:
    def findMaxPathScore(self, edges: List[List[int]], online: List[bool], k: int) -> int:
        n = len(online)

        graph = [[] for _ in range(n)]
        indeg = [0] * n
        pesos = []

        for u, v, w in edges:
            graph[u].append((v, w))
            indeg[v] += 1
            pesos.append(w)

        # Orden topologico
        topo = []
        q = deque()

        for i in range(n):
            if indeg[i] == 0:
                q.append(i)

        while q:
            u = q.popleft()
            topo.append(u)
            for v, _ in graph[u]:
                indeg[v] -= 1
                if indeg[v] == 0:
                    q.append(v)

        def check(mid):
            INF = 10**30
            dp = [INF] * n
            dp[0] = 0

            for u in topo:
                if dp[u] == INF:
                    continue

                if u != 0 and u != n - 1 and not online[u]:
                    continue

                for v, w in graph[u]:
                    if w < mid:
                        continue

                    if v != n - 1 and not online[v]:
                        continue

                    if dp[u] + w < dp[v]:
                        dp[v] = dp[u] + w

            return dp[n - 1] <= k

        if not pesos:
            return -1

        l = 0
        r = max(pesos)
        ans = -1

        while l <= r:
            mid = (l + r) // 2

            if check(mid):
                ans = mid
                l = mid + 1
            else:
                r = mid - 1

        return ans