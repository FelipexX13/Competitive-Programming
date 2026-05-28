class Solution(object):
    def countPermutations(self, complexity):
        import math
        menor = complexity[0]
        for i in range(1,len(complexity)):
            if(menor>= complexity[i]):
                return 0
        return math.factorial(len(complexity)-1)%((10**9)+7)
        