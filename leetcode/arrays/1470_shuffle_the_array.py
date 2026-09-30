# <3
# Tema: LeetCode Hub / Intercalar Dos Mitades
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1470 "Shuffle the Array": intercalar la primera mitad con la segunda.
# Tecnica: cortar por la mitad y meter alternando. Directo.

class Solution:
    def shuffle(self, nums: List[int], n: int) -> List[int]:
        l = []
        nums2 = nums[len(nums)//2:len(nums)]
        
        for i in range(len(nums)//2):
            l.append(nums[i])
            l.append(nums2[i])
        return l 