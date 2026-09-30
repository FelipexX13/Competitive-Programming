# <3
# Tema: LeetCode Hub / Suma de Digitos
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3550 "Smallest Index With Digit Sum Equal to Index": el primer indice donde la suma de
# digitos del valor es igual al indice.
# Tecnica: sum(map(int, str(x))) por elemento, que es la forma corta de sumar digitos en Python.

class Solution:
    def smallestIndex(self, nums: List[int]) -> int:
        for i in range(len(nums)):
            val = sum(list(map(int,str(nums[i]))))
            if(val == i):
                return i
        return -1
        