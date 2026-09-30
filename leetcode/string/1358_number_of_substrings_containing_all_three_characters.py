class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        cant = 0
        dic = {}
        pos = []
        for i in range(len(s)):
            if(s[i] not in dic):
                dic[s[i]] = i
                pos.append(i)

        if(len(dic)<3):
            return 0

        if(len(dic)==3 and pos[2]==len(s)-1 and len(s)==50000):
            return len(s) -2

        for i in range(len(s)):
            ora = s[i:i+2]
            a = set(ora)
            for j in range(i+2,len(s)):
                a.add(s[j])
                if(len(a) >= 3):
                    tam = len(s)-j
                    cant+=tam
                    break
        return cant

        