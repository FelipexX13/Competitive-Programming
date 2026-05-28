class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        ma = 0
        co = 0
        for i in range(len(nums)):
            if(nums[i]==1):
                co += 1
            else:
                if(co>ma):
                    ma = co
                co = 0
        if(nums[-1]== 1 and co>ma):
            ma = co
        return ma