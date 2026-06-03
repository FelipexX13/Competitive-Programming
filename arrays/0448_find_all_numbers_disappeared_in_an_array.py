class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        num = set(nums)
        fal = []
        for i in range(1,len(nums)+1):
            if(i in num):
                continue
            fal.append(i)
        return fal
        