class Solution:
    def missingInteger(self, nums: List[int]) -> int:
        c = [nums[0]]
        v = nums[0]
        i = 1
        while i<len(nums):
            if(nums[i]-1 == nums[i-1]):
                v += nums[i]
            else:
                c.append(v)
                break
            i+=1
        c.append(v)
        print(c)
        mas = max(c)
        k = set(nums)
        while True:
            if(mas not in k):
                return mas
            mas += 1

        