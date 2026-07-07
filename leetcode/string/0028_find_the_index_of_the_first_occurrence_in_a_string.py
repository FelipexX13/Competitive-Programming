class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        try:
            p = haystack.index(needle)
            return p
        except:
            return -1
        