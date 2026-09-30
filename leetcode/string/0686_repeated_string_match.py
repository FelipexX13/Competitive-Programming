class Solution:
    def repeatedStringMatch(self, a: str, b: str) -> int:
        tam1 = len(a)
        tam2 = len(b)
        ne = tam2//tam1 + 5
        j = a
        n = 1
        while n<ne:
            if(b in j):
                return n
            n+=1
            j+=a
        return -1
        
        