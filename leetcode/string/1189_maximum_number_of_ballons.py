class Solution:
    def maxNumberOfBalloons(self, text: str) -> int:
        dic = {"b":0,"a":0,"l":0,"o":0,"n":0}
        for i in text:
            if(i in dic):
                dic[i] += 1
        lt = dic["l"]
        ot = dic["o"]
        mi = dic["b"]
        for cla, val in dic.items():
            if(val < mi):
                mi = val
        if (lt < 2 or ot < 2):
            return 0
        else:
            h = min(int(lt/2), int(ot/2))
            if(h == mi):
                return mi
            elif(h>mi):
                return mi
            else:
                return h
        