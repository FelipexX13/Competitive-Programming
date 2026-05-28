class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        nu = len(nums)
        nums.sort()
        for i in range(0,nu):
            if(i == nums[i]):
                continue
            else:
                return i
        return nu