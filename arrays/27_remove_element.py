class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        cont2 = 0
        cont = 0
        i = 0
        while i< len(nums):
            if(nums[i]==val):
                nums.remove(val)
                cont+=1
                continue
            cont2+=1
            i+=1
        i=0
        while i<cont:
            nums.append("_")
            i+=1
        
        return cont2