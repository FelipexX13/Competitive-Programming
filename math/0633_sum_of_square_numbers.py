import math
class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        if(c == 0):
            return True
        b1 = math.floor(math.sqrt(c))
        for a2 in range(b1):
            a1 = math.floor(math.sqrt(c-(b1*b1)))
            b2 = math.floor(math.sqrt(c-(a2*a2)))
            
            if(((a1*a1)+(b1*b1)) == c):
                return True
            elif(((a2*a2)+(b2*b2)) == c):
                return True
            b1 -= 1
        return False
        