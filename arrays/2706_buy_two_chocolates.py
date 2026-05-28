class Solution:
    def buyChoco(self, prices: List[int], money: int) -> int:
        val = []
        for i in range(0,len(prices)):
            for j in range(i+1, len(prices)):
                val.append(prices[i]+prices[j])
        minimo = min(val)
        if(minimo>money):
            return money
        else:
            return money-minimo