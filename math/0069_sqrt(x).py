class Solution:
    def mySqrt(self, x: int) -> int:
        for i in range(x//2+2):
            k = i*i
            if(k>x):
                return i-1
            elif(k==x):
                return i
            else:
                continue
        return 1