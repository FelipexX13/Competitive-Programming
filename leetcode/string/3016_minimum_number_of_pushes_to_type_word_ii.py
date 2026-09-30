class Solution:
    def minimumPushes(self, word: str) -> int:
        dic = {}
        for i in word:
            if(i in dic):
                dic[i]+= 1
            else:
                dic[i] = 1

        va  = 1
        c = 0
        t = 0
        dic = dict(sorted(dic.items(), key=lambda item: item[1], reverse=True))
        for clave,valor in dic.items():
            t += 1
            if(t > 8):
                t=1
                va +=1
            c += (valor*va)
            
        return c



        