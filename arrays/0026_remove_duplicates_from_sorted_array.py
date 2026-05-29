class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        cont = 0
        for i in range(len(nums)-1,0,-1):
            if(nums[i]==nums[i-1]):
                nums.pop(i)
        return len(nums)