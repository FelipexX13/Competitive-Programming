import math
class Solution:
    def smallestNumber(self, n: int, t: int) -> int:
        while True:
            s = str(n)
            u = math.prod(list(map(int,s)))
            if(u%t == 0):
                break
            n += 1
        return n


        