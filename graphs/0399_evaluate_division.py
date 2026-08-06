from collections import defaultdict

class Solution:
    def calcEquation(self, equations, values, queries):

        graph = defaultdict(list)

        for (a, b), v in zip(equations, values):
            graph[a].append((b, v))
            graph[b].append((a, 1 / v))

        def dfs(curr, target, visited):

            if curr == target:
                return 1

            visited.add(curr)

            for nxt, weight in graph[curr]:
                if nxt in visited:
                    continue

                ans = dfs(nxt, target, visited)

                if ans != -1:
                    return weight * ans

            return -1

        res = []

        for a, b in queries:

            if a not in graph or b not in graph:
                res.append(-1.0)
                continue

            res.append(dfs(a, b, set()))

        return res
