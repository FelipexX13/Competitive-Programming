class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        parents = {}
        for a,b in edges:
            parents[a] = a
            parents[b] = b
        def find(node):
            if parents[node] == node:
                return node
            return find(parents[node])
        def union(a,b):
            fatherA = find(a)
            fatherB = find(b)
            if fatherA == fatherB:
                return False
            parents[fatherA] = fatherB
            return True
        
        for a,b in edges:
            if not union(a,b):
                return [a,b]
