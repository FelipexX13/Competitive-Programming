# <3
# Tema: LeetCode Hub / Concatenacion
# Resumen: Devolver el arreglo pegado consigo mismo
# O: (n)
# Detalle: LeetCode 1929 "Concatenation of Array": devolver el arreglo pegado consigo mismo.
# Tecnica: nums + nums. Una linea.

class Solution:
    def getConcatenation(self, nums: List[int]) -> List[int]:
        return nums+nums