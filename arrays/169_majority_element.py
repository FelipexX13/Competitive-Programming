class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        l = {}
        for i in range(len(nums)):
            if (nums[i] in l):
                l[nums[i]]+=1
            else:
                l[nums[i]]=1
        mas = 0
        v = 0
        for i,j in l.items():
            if(j > mas):
                mas = j
                v = i
        
        return v
        