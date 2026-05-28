class Solution:
    def countElements(self, nums: List[int], k: int) -> int:
        if(k==0):
            return len(nums)
        nums.sort()
        contF = 0
        for i in range(len(nums)):
            cont=0
            if(len(nums)-i <= k):
                break
            else:
                j = i
                fi = len(nums)-1
                while j <= fi:
                    mitad = (j+fi)//2
                    if(nums[i]<nums[mitad]):
                        if(len(nums)-mitad >= k):
                            contF+=1  
                            break
                        else:
                            fi = mitad -1
                    else:
                        j = mitad + 1
        return contF 