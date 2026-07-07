class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        l = {}
        for i in range(len(nums)):
            if nums[i] in l:
                return True
            else:
                l[nums[i]] = 1
        return False