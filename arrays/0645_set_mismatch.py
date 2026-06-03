class Solution:
    def findErrorNums(self, nums: List[int]) -> List[int]:
        nums = sorted(nums)
        f = []
        r = 0
        fa = 0
        for i in range(1,len(nums)):
            if(nums[i]== nums[i-1]):
                r = nums[i]
            elif(nums[i]-1!= nums[i-1]):
                fa = nums[i]-1

        if(fa == 0):
            if(nums[0]== 1):
                fa = nums[i]+1
            else:
                fa = 1

        f = [r,fa]
        return f