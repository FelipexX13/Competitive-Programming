class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        ini = 0
        fin = 1
        resp = 0
        l = set()
        if(len(s)==0):
            return 0
        elif(len(s)==1):
            return 1
        l.add(s[ini])
        while(ini<len(s)):
            print(ini, fin)
            if(s[fin] in l):
                l.remove(s[ini])
                ini += 1
                continue
            l.add(s[fin])
            print(l)
            if(fin-ini > resp):
                resp = (fin-ini)
            fin += 1
            if(fin >= len(s)):
                fin = len(s)-1
        return resp+1