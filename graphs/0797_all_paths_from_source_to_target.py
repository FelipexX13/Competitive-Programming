from collections import deque
class Solution:
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
            visited = set()
            res = []
            path = []
            def dfs(curr, par):
                path.append(curr)
                if curr == len(graph)-1:
                    res.append(path.copy())
                for node in graph[curr]:
                    if (curr, node) in visited:
                        continue
                    visited.add((curr, node))
                    dfs(node, curr)
                if par != -1:
                    visited.remove((par, curr))
                path.pop()
            dfs(0, -1)
            return res
