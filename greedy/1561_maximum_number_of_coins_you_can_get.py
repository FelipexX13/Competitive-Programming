class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        k = sorted(piles)
        c = 0
        while len(k)>0:
            k.pop()
            c += k[len(k)-1]
            k.pop(0)
            k.pop()
        return c

        