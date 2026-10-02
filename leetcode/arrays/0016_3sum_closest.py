# <3
# Tema: LeetCode Hub / Ordenar y Dos Punteros
# Resumen: Los tres numeros cuya suma quede mas cerca de target
# O: (n^2) tras ordenar en O(n log n)
# Detalle: LeetCode 16 "3Sum Closest": los tres numeros cuya suma quede mas cerca de target.
# Tecnica: ordenar, fijar el primero y barrer los otros dos con punteros desde los extremos. Si
# la suma se pasa se baja el derecho, si falta se sube el izquierdo. Ese ordenar + dos punteros
# es la plantilla de toda la familia 2Sum / 3Sum / 4Sum y baja de O(n^3) a O(n^2).

class Solution:
    def threeSumClosest(self, nums: list[int], target: int) -> int:
        nums = sorted(nums)
        tam = len(nums)
        mejor = float("inf")
        guar = 0
        for i in range(0,tam):
            l = i+1
            r = len(nums)-1
            while l<r:
                suma = nums[i]+nums[l]+nums[r]
                abso = abs(target-suma)
                if(suma>target):
                    r -= 1
                elif(suma<target):
                    l += 1
                else:
                    return target
                if(abso < mejor):
                    mejor = abso
                    guar = suma
        return guar