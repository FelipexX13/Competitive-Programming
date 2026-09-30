class Solution:
    def minimumPushes(self, word: str) -> int:
        dic = {}
        c = 0
        t = 0
        va  = 1
        for i in word:
            if(i in dic):
                c+=dic[i]
            else:
                dic[i] = va
                c += va
            t+=1
            if(t==8):
                t= 0
                va +=1
        return c
        