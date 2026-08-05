class Solution:
    def findMissingElements(self, nums: List[int]) -> List[int]:
        mi = min(nums)
        ma = max(nums)
        fal = []
        for i in range(mi+1,ma):
            if(i in nums):
                continue
            fal.append(i)
        return fal
        