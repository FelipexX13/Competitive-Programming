class Solution:
    def maxDistinct(self, s: str) -> int:
        h = set(s)
        return (len(h))