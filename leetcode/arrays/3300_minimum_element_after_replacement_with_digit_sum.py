# <3
# Tema: LeetCode Hub / Suma de Digitos
# Resumen: El minimo despues de cambiar cada numero por la suma de sus digitos
# O: (n * digitos)
# Detalle: LeetCode 3300 "Minimum Element After Replacement With Digit Sum": el minimo despues
# de cambiar cada numero por la suma de sus digitos. Tecnica: pasar a string, sumar los digitos
# y quedarse con el minimo. Una pasada.

class Solution:
    def minElement(self, nums: List[int]) -> int:
        me = 9999999999999
        for i in nums:
            h = str(i)
            ca = 0
            for j in h:
                ca += int(j)
            if(ca<me):
                me = ca
        return me