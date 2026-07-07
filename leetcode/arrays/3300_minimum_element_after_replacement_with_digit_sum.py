class Solution:
    def minElement(self, nums: List[int]) -> int:
        me = 9999999999999
        for i in nums:
            h = str(i)
            ca = 0
            for j in h:
                ca += int(j)
            if(ca<me):
                me = ca
        return me