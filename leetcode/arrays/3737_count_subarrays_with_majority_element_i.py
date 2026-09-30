
import math

class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        conteo = nums.count(target)
        valF = 0
        valF += conteo
        j = 0
        while j < len(nums):
            c = 0
            k = j
            if(nums[j]==target):
                while k < len(nums):
                    if(nums[k]==target):
                        c+=1
                    else:
                        k+=1
                        break
                    k+=1
            j=k
            for i in range(1,c+1):
                valF += c-i 
            j+=1   

        

        return valF


        