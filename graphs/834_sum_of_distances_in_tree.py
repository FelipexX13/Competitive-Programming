from collections import defaultdict
class Solution:
    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:
        if len(edges) == 0:
            return [0]
        tree = defaultdict(list)
        for a, b in edges:
            tree[a].append(b)
            tree[b].append(a)

        sizes = defaultdict(int)
        def dfs(curr, par):
            total = 1
            for node in tree[curr]:
                if node != par:
                    total += dfs(node, curr)
            sizes[curr] = total
            return total
        dfs(0, None)

        res = [0]*n
        def dfs2(curr, depth, par):
            res[0] += depth
            for node in tree[curr]:
                if node != par:
                    dfs2(node, depth+1, curr)
        dfs2(0, 0, None)

        def dfs3(curr, prev, par):
            currSum = 0
            if res[curr] != 0:
                currSum = res[curr]
            else:
                currSum = prev - sizes[curr] + (n-sizes[curr])
            res[curr] = currSum
            for node in tree[curr]:
                if node!= par:
                    dfs3(node, currSum, curr)
        dfs3(0, 0, None)
        return res
            
