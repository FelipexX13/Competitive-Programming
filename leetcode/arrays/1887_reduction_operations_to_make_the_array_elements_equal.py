class Solution:
    def reductionOperations(self, nums: List[int]) -> int:
        a = sorted(nums)
        c = 0
        k = a[0]
        for i in range(1,len(a)):
            if(a[i]!=a[i-1]):
                c += len(a)-i
        return c
                
            
            
                
        