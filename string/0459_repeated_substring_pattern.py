class Solution:
    def repeatedSubstringPattern(self, s: str) -> bool:
        if(len(s)==1):
            return False
        i = 1
        f = False
        while i<len(s)//2+1:
            pal = s[0:i]
            k = 0
            while k <len(s):
                try:
                    if(pal == s[k:k+i]):
                        k+=i
                        continue
                    else:
                        break
                except:
                    break
            if(k == len(s)):
                return True
            i+=1
        return False
        