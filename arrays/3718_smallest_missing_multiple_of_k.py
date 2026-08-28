class Solution:
    def missingMultiple(self, nums: List[int], k: int) -> int:
        t = set(nums)
        m = 1
        while True:
            if(m%k==0 and m not in t):
                return m
            m+=1
        