# <3
# Tema: LeetCode Hub / Fuerza Bruta O(n^2)
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1365 "How Many Numbers Are Smaller Than the Current Number": para cada numero,
# cuantos son menores. Tecnica: dos ciclos anidados. Con n hasta 500 alcanza. Con un arreglo de
# frecuencias y sumas de prefijos sale en O(n + rango), que es lo que se haria si n fuera
# grande.

class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        c = []
        for i in range(len(nums)):
            can = 0
            for j in range(len(nums)):
                if(nums[i]>nums[j]):
                    can += 1

            c.append(can)
        return c
        