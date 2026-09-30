class Solution:
    def maximumLengthSubstring(self, s: str) -> int:
        dic = {}
        inicio = 0
        fin = 0
        tam = []
        while fin < len(s):
            if(s[fin] not in dic):
                dic[s[fin]] = 1
            else:
                dic[s[fin]]+=1
            if(dic[s[fin]] > 2):
                tam.append(fin-inicio)
                while dic[s[fin]] > 2:
                    dic[s[inicio]]-=1
                    inicio += 1
            fin += 1
        if(len(tam)==0):
            return fin
        tam.append(fin-inicio)
        return max(tam)
        