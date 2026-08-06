from collections import defaultdict

class Solution:
    def findRedundantDirectedConnection(self, edges: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        indegree = defaultdict(int)
        nodes = set()

        for a, b in edges:
            graph[a].append(b)
            indegree[b] += 1
            nodes.add(a)
            nodes.add(b)

        visiting = set()
        visited = set()
        stack = []
        edgeStack = []
        ciclo = set()

        def dfs(node):
            visiting.add(node)
            stack.append(node)

            for nxt in graph[node]:
                if nxt in visiting:
                    idx = stack.index(nxt)
                    for i in range(idx, len(edgeStack)):
                        ciclo.add(edgeStack[i])
                    ciclo.add((node, nxt))
                    return True

                if nxt not in visited:
                    edgeStack.append((node, nxt))
                    if dfs(nxt):
                        return True
                    edgeStack.pop()

            stack.pop()
            visiting.remove(node)
            visited.add(node)
            return False

        for node in nodes:
            if node not in visited:
                if dfs(node):
                    break

        # Buscar si existe un nodo con dos padres
        doble = -1
        for node in nodes:
            if indegree[node] == 2:
                doble = node
                break

        # Caso 1: solo ciclo
        if doble == -1:
            for a, b in reversed(edges):
                if (a, b) in ciclo:
                    return [a, b]

        # Caso 2 o 3: nodo con dos padres
        candidatos = []
        for a, b in edges:
            if b == doble:
                candidatos.append([a, b])

        # Si una de las dos aristas pertenece al ciclo
        for a, b in candidatos:
            if (a, b) in ciclo:
                return [a, b]

        # Si ninguna pertenece al ciclo
        return candidatos[-1]
