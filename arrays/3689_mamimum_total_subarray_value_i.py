class Solution:
    def maxTotalValue(self, nums: List[int], k: int) -> int:
        ma = max(nums)
        mi = min(nums)
        p = ma - mi
        return p*k
        