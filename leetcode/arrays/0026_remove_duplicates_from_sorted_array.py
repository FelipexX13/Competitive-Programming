# <3
# Tema: LeetCode Hub / Quitar Repetidos en Ordenado
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 26 "Remove Duplicates from Sorted Array": dejar cada valor una vez, en el sitio.
# Tecnica: recorrer DE ATRAS hacia adelante y hacer pop cuando el actual es igual al anterior.
# Ir al reves es lo que permite borrar sin dananar los indices que faltan. pop(i) es O(n), asi
# que en total es O(n^2). Con dos punteros (uno de escritura y uno de lectura) queda en O(n) sin
# borrar nada.

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        cont = 0
        for i in range(len(nums)-1,0,-1):
            if(nums[i]==nums[i-1]):
                nums.pop(i)
        return len(nums)