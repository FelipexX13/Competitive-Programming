# <3
# Tema: LeetCode Hub / Observacion que Colapsa el Problema
# Resumen: Escoger k subarreglos y sumar (max - min) de cada uno; maximizar
# O: (n), solo el maximo y el minimo
# Detalle: LeetCode 3689 "Maximum Total Subarray Value I": escoger k subarreglos y sumar (max -
# min) de cada uno; maximizar. Tecnica: tres lineas. El mejor subarreglo posible es el arreglo
# COMPLETO, que da max - min, y como los subarreglos se pueden repetir, la respuesta es (max -
# min) * k. Otra vez: leer bien antes de programar. Aqui no hay que escoger nada.

class Solution:
    def maxTotalValue(self, nums: List[int], k: int) -> int:
        ma = max(nums)
        mi = min(nums)
        p = ma - mi
        return p*k
        