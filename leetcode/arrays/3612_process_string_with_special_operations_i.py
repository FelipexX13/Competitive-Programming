class Solution:
    def processStr(self, s: str) -> str:
        res = ""
        for i in s:
            if(i not in "*#%"):
                res += i
            elif(i == "*" and len(res) > 0):
                res = res[:-1]
            elif(i == "#"):
                res += res
            elif(i == "%"):
                res = res[::-1]
        return res