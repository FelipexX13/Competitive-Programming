class Solution:
    def dfs(self, nodo, dic, vis):
        if nodo not in vis and nodo != -1:
            vis.add(nodo)
            for i in dic[nodo]:
                self.dfs(i, dic, vis)

    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        dic = {}
        sol1 = []
        for i in range(n):
            dic[i] = [-1]
            sol1.append(i)
        for i in invocations:
            dic[i[0]].append(i[1])
        vis = set()
        self.dfs(k, dic, vis)
        
        sol = set()
        for i in range(n):
            for j in dic[i]:
                if(i not in vis and j not in vis):
                    sol.add(i)
                elif(i not in vis and j in vis):
                    return sol1
        return list(sol)