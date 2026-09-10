class Solution:
    def firstStableIndex(self, nums: list[int], k: int) -> int:
        mayor = 0
        mayores = []
        for i in nums:
            if i > mayor:
                mayor = i
            mayores.append(mayor)
        nums2 = nums[::-1]    
        menor = float('inf')
        menores = []
        for i in nums2:
            if i < menor:
                menor = i
            menores.insert(0, menor)
        
        for i in range(len(nums)):
            if(mayores[i]-menores[i] <= k):
                return i
        return -1
            
        