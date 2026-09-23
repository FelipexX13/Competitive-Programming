class Solution:
    def findMin(self, nums: List[int]) -> int:
        n = len(nums)
        ini = 0
        fin = n-1
        while (ini<fin):
            m = (fin+ini)//2
            if(nums[ini]>nums[m]):
                fin = m
            elif(nums[fin]<nums[m]):
                ini = m
            else:
                break
                
            if(fin-ini==1):
                break
        if(nums[ini] > nums[fin]):
            return (nums[fin])
        else:
            return(nums[ini])
            
            
        