class Solution:
    def evaluate(self, s: str, knowledge: list[list[str]]) -> str:
        dic = {}
        for i in knowledge:
            dic[i[0]] = i[1]
        res = ""
        i=0
        while i < len(s):
            if(s[i]=="("):
                ini = i+1
                fin = i+2
                pal = s[ini]
                while (s[fin] != ")"):
                    pal += s[fin]
                    fin += 1
                if(pal in dic):
                    res += dic[pal]
                else: 
                    res += "?"
                i = fin
            else:
                res+= s[i]
            i+=1
        return res
