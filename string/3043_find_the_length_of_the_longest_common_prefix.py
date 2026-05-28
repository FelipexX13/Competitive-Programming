class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:

        v1 = set()
        for i in arr1:
            k = str(i)
            l = ""
            for j in k:
                l += j
                v1.add(l) 
        v2 = set()
        for i in arr2:
            k = str(i)
            l = ""
            for j in k:
                l += j
                v2.add(l)
        v1 = sorted(v1)
        c = 0
        for i in v1:
            if(i in v2 and c<int(i)):
                c = int(i)

        if(c==0):
            return 0
        else:
            return len(str(c))
