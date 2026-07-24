class Solution:
    def maxIceCream(self, costs: List[int], coins: int) -> int:
        s = sorted(costs)
        c = 0
        cant = 0
        for i in s:
            c+=i
            if(c > coins):
                break
            
            
            cant+=1
        return cant 
        