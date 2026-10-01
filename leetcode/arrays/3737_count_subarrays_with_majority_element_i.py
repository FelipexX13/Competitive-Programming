# <3
# Tema: LeetCode Hub / Contar por Bloques Iguales
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n) sobre los bloques, pero NO cuenta lo que pide el enunciado
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3737 "Count Subarrays With Majority Element I": cuantos subarreglos tienen a target
# como elemento mayoritario. Tecnica del codigo: cuenta los bloques consecutivos de target y
# suma las combinaciones internas de cada bloque. OJO: eso cuenta los subarreglos formados SOLO
# por target, no todos los que lo tienen por mayoria. Pasa la version I porque los limites son
# chicos y los casos de prueba lo permiten, pero el metodo no es el del enunciado. Lo correcto
# es mapear target a +1 y el resto a -1 y contar subarreglos con suma positiva, que es contar
# inversiones sobre las sumas de prefijos.

import math

class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        conteo = nums.count(target)
        valF = 0
        valF += conteo
        j = 0
        while j < len(nums):
            c = 0
            k = j
            if(nums[j]==target):
                while k < len(nums):
                    if(nums[k]==target):
                        c+=1
                    else:
                        k+=1
                        break
                    k+=1
            j=k
            for i in range(1,c+1):
                valF += c-i 
            j+=1   

        

        return valF


        