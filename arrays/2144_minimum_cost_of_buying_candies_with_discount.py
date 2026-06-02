class Solution:
    def minimumCost(self, cost: List[int]) -> int:
        cost = sorted(cost)
        c = 0
        i = len(cost)-1
        t = 0
        while i>=0:
            if t==2:
                t=0
                i-=1
                continue
            c+=cost[i]
            t += 1
            i-=1
        return(c)
            
            