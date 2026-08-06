from collections import defaultdict
class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        graph = defaultdict(list)
        for i in range(len(isConnected)):
            for j in range(len(isConnected)):
                if isConnected[i][j] == 1:
                    graph[i].append(j)
                    graph[j].append(i)
        visited = set()
        def dfs(curr):
            visited.add(curr)
            for node in graph[curr]:
                if node not in visited:
                    dfs(node)
        res = 0
        for node in graph:
            if node not in visited:
                dfs(node)
                res+=1
        return res
