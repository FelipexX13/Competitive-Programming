class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        c = len(digits)-1
        v = 0
        for i in digits:
            v+= (i*10**c)
            c-=1
        v+=1
        va = str(v)
        l = []
        for i in va:
            l.append(int(i))
        return l
        