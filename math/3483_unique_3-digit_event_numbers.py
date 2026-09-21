class Solution:
    def totalNumbers(self, digits: List[int]) -> int:
        res = set()
        fre = [0]*10
        for i in digits:
            fre[i] += 1
        
        for C in range(0,10,2):
            if(fre[C]==0):
                continue
            fre[C]-=1
            for A in range(1,10):
                if(fre[A]==0):
                    continue
                fre[A]-=1
                for B in range(0,10):
                    if(fre[B]==0):
                        continue
                    res.add(int(str(A)+str(B)+str(C)))
                fre[A]+=1
            fre[C]+=1
        return len(res)
                


        