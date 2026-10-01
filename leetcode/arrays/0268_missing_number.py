# <3
# Tema: LeetCode Hub / Numero Faltante
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 268 "Missing Number": el numero de 0 a n que falta. Tecnica: ordenar y buscar la
# primera posicion donde nums[i] != i. Es O(n log n) por el sort. Sale en O(n) sin ordenar de
# dos formas: la suma de Gauss n*(n+1)/2 menos la suma real, o el XOR de todos los indices
# contra todos los valores.

class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        nu = len(nums)
        nums.sort()
        for i in range(0,nu):
            if(i == nums[i]):
                continue
            else:
                return i
        return nu