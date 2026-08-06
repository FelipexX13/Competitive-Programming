class Solution:
    def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
        safe = set()
        visited = set()

        def dfs(curr):
            if curr in safe:
                return True

            if curr in visited:
                return False

            visited.add(curr)

            for node in graph[curr]:
                if not dfs(node):
                    visited.discard(curr)
                    return False

            visited.discard(curr)
            safe.add(curr)
            return True

        res = []

        for i in range(len(graph)):
            visited.clear()
            if dfs(i):
                res.append(i)

        return res
