class Solution:
    def shuffle(self, nums: List[int], n: int) -> List[int]:
        l = []
        nums2 = nums[len(nums)//2:len(nums)]
        
        for i in range(len(nums)//2):
            l.append(nums[i])
            l.append(nums2[i])
        return l 