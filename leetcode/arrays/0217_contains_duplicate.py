# <3
# Tema: LeetCode Hub / Buscar Repetidos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 217 "Contains Duplicate": decir si hay algun valor repetido. Tecnica: diccionario
# como set, y se corta en el primer repetido. Cortar temprano es la unica gracia; tambien sale
# con len(set(nums)) != len(nums).

class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        l = {}
        for i in range(len(nums)):
            if nums[i] in l:
                return True
            else:
                l[nums[i]] = 1
        return False