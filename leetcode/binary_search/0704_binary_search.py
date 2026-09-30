class Solution:
    def search(self, nums: List[int], target: int) -> int:
        ini = 0
        fin = len(nums)-1
        while ini <= fin:
            mitad = (ini+fin)//2
            if(nums[mitad]==target):
                return mitad
            elif(nums[mitad]<target):
                ini = mitad+1
            else:
                fin = mitad-1
        return -1
        