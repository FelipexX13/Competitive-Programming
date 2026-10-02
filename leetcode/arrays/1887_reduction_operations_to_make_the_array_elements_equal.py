# <3
# Tema: LeetCode Hub / Contar por Escalones
# Resumen: Operaciones para igualar todo al minimo, bajando cada vez el maximo al siguiente valor distinto
# O: (n log n) por el sort; contar escalones es lineal
# Detalle: LeetCode 1887 "Reduction Operations to Make the Array Elements Equal": operaciones
# para igualar todo al minimo, bajando cada vez el maximo al siguiente valor distinto. Tecnica:
# ordenar y en cada cambio de valor sumar cuantos elementos quedan a la derecha. Cada uno de
# esos va a tener que bajar ese escalon. Contar por escalones en vez de simular es lo que lo
# vuelve O(n log n).

class Solution:
    def reductionOperations(self, nums: List[int]) -> int:
        a = sorted(nums)
        c = 0
        k = a[0]
        for i in range(1,len(a)):
            if(a[i]!=a[i-1]):
                c += len(a)-i
        return c
                
            
            
                
        