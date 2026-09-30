class Solution:
    def threeSumClosest(self, nums: list[int], target: int) -> int:
        nums = sorted(nums)
        tam = len(nums)
        mejor = float("inf")
        guar = 0
        for i in range(0,tam):
            l = i+1
            r = len(nums)-1
            while l<r:
                suma = nums[i]+nums[l]+nums[r]
                abso = abs(target-suma)
                if(suma>target):
                    r -= 1
                elif(suma<target):
                    l += 1
                else:
                    return target
                if(abso < mejor):
                    mejor = abso
                    guar = suma
        return guar