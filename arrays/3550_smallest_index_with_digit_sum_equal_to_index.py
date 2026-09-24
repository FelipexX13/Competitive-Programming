class Solution:
    def smallestIndex(self, nums: List[int]) -> int:
        for i in range(len(nums)):
            val = sum(list(map(int,str(nums[i]))))
            if(val == i):
                return i
        return -1
        