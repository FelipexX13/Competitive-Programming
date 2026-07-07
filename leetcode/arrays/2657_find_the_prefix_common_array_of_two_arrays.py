class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        i = 0
        c = []
        cont = 0
        while i < len(A):
            set1 = set(A[0:i+1])
            set2 = set(B[0:i+1])
            cont = 0
            for j in set1:
                if(j in set2):
                    cont+= 1
            c.append(cont)
            i+=1
        return c