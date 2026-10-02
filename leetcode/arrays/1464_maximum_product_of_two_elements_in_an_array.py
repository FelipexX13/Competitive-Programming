# <3
# Tema: LeetCode Hub / Los Dos Mayores
# Resumen: Maximizar (a-1)*(b-1)
# O: (n log n) por el sort; con una pasada seria (n)
# Detalle: LeetCode 1464 "Maximum Product of Two Elements in an Array": maximizar (a-1)*(b-1).
# Tecnica: ordenar y tomar los dos ultimos. Como los valores son positivos, los dos mayores dan
# el producto mayor sin tener que probar nada. Con una pasada guardando los dos maximos sale en
# O(n) sin ordenar.

class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        t = sorted(nums)
        return (t[len(t)-1]-1)*(t[len(t)-2]-1)
        