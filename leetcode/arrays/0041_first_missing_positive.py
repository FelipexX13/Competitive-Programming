class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = set(nums)
        ma = max(nums)
        if(ma<1):
            return 1
        for i in range(1, ma):
            if(i in n):
                continue
            else:
                return i
        return ma+1
        