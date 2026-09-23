class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        ini = 0
        fin = 1
        dic = {nums[ini]: 1}
        cap = []
        f = True
        while fin < len(nums):
            if(nums[fin] in dic and f):
                dic[nums[fin]] += 1
            elif(f):
                dic[nums[fin]] = 1
            if dic[nums[fin]] == (k+1):
                cap.append(fin-ini)
                dic[nums[ini]] -= 1
                ini += 1
                f = False
            else:
                fin+=1
                f = True
        cap.append(fin-ini)
        return max(cap)
        