class Solution:
    def sumAndMultiply(self, n: int) -> int:
        h = ""
        j = str(n)
        for i in j:
            if(i!="0"):
                h+=i
        sums = 0
        for i in h:
            sums+=int(i)
        try:
            return int(h)*sums
        except:
            return 0
        