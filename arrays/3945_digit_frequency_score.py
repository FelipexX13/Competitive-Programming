class Solution:
    def digitFrequencyScore(self, n: int) -> int:
        v = str(n)
        dicc = {}
        for i in v:
            if(i in dicc):
                dicc[i]+=1
            else:
                dicc[i]=1
        value = 0
        for c,v in dicc.items():
            value += (int(c)*v)

        return value
            
        