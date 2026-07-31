class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        t = sorted(nums)
        return (t[len(t)-1]-1)*(t[len(t)-2]-1)
        