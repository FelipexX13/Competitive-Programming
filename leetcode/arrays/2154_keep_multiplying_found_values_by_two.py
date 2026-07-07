class Solution:
    def findFinalValue(self, nums: List[int], original: int) -> int:
        if original in nums:
            while True:
                original*=2
                if original in nums:
                    continue
                else:
                    break
        return original
        