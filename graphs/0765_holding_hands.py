from collections import defaultdict
class Solution:
    def minSwapsCouples(self, row: List[int]) -> int:
        n = len(row)
        parent = [i for i in range(n//2)]
        def find(i):
            if parent[i] == i:
                return i
            return find(parent[i])
        def unite(i, j):
            irep = find(i)
            jrep = find(j)
            parent[irep] = jrep
        def get_groups():
            groups = defaultdict(list)
            for element in parent:
                root = find(element)
                groups[root].append(element)
            return list(groups.values())
            
        coach = [-1] * (n)

        for i, val in enumerate(row):
            coach[val] = i//2

        graph = defaultdict(list)
        for i in range(0, n-1, 2):
            curr = coach[i]
            nxt = coach[i+1]
            if curr != nxt:
                unite(curr, nxt)
        groups = get_groups()
        res = 0
        for i in groups:
            res += len(i)-1
        return res
