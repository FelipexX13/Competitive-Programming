class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        c = []
        for i in range(len(nums)):
            can = 0
            for j in range(len(nums)):
                if(nums[i]>nums[j]):
                    can += 1

            c.append(can)
        return c
        