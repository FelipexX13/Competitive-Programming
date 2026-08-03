from collections import defaultdict
class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        colors = defaultdict(int)
        res = True
        visited = set()
        def dfs(curr):
            nonlocal res
            visited.add(curr)

            if curr not in colors:
                colors[curr] = 1

            for node in graph[curr]:
                if node not in colors:
                    colors[node] = -colors[curr]
                    dfs(node)
                elif colors[node] == colors[curr]:
                    res = False
        for i in range(len(graph)):
            if i not in visited:
                dfs(i)
        return res
