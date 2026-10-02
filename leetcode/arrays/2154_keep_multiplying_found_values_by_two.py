# <3
# Tema: LeetCode Hub / Duplicar mientras Exista
# Resumen: Mientras original este en el arreglo, se duplica; devolver el valor final
# O: (n log maximo): cada 'in' sobre la lista es (n); con set seria (log maximo)
# Detalle: LeetCode 2154 "Keep Multiplying Found Values by Two": mientras original este en el
# arreglo, se duplica; devolver el valor final. Tecnica: simulacion directa. El in sobre una
# lista es O(n); con set(nums) queda O(1) por vuelta.

class Solution:
    def findFinalValue(self, nums: List[int], original: int) -> int:
        if original in nums:
            while True:
                original*=2
                if original in nums:
                    continue
                else:
                    break
        return original
        