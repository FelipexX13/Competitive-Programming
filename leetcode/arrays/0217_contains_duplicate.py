# <3
# Tema: LeetCode Hub / Buscar Repetidos
# Resumen: Decir si hay algun valor repetido
# O: (n), cortando en el primer repetido
# Detalle: LeetCode 217 "Contains Duplicate": decir si hay algun valor repetido. Tecnica:
# diccionario como set, y se corta en el primer repetido. Cortar temprano es la unica gracia;
# tambien sale con len(set(nums)) != len(nums).

class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        l = {}
        for i in range(len(nums)):
            if nums[i] in l:
                return True
            else:
                l[nums[i]] = 1
        return False