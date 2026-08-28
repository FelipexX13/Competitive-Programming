class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if(len(nums)==1):
            return False
        dic = {0: -1}
        res = 0
        ini = 0
        for i in range(len(nums)):
            ini += nums[i]
            res = ini%k
            if(res not in dic):
                dic[res] = i
            else:
                if i - dic[res] >= 2:
                    return True
        return False