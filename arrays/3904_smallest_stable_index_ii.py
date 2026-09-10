class Solution:
    def firstStableIndex(self, nums: list[int], k: int) -> int:
        menor = float('inf')
        menores = []
        for i in range(len(nums)-1,-1,-1):
            if nums[i] < menor:
                menor = nums[i]
            menores.append(menor)

        mayor = 0
        for i in range(len(nums)):
            if nums[i] > mayor:
                mayor = nums[i]
            if(mayor-menores[len(menores)-1-i] <= k):
                return i
        return -1
            
        