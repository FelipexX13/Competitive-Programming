class Solution:
    def leftRightDifference(self, nums: List[int]) -> List[int]:
        f = []
        for i in range(len(nums)):
            ll = sum(nums[0:i])
            rr = sum(nums[i+1:len(nums)])
            f.append(abs(ll-rr))
        return f
        