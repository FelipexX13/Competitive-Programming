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

        # Orden topológico
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