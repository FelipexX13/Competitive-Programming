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
