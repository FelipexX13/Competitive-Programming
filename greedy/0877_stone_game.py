class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        piles = sorted(piles)
        A = 0
        B = 0
        va = True
        i = len(piles)-1
        while i > -1:
            if(va):
                A += piles[i]
                va = not va
            else:
                B += piles[i]
                va = not va
            i-=1
        if(A > B):
            return True
        else:
            return False


        #return True always