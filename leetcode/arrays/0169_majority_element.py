# <3
# Tema: LeetCode Hub / Elemento Mayoritario
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n) tiempo y memoria; Boyer-Moore lo hace con (1)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 169 "Majority Element": el que aparece mas de n/2 veces. Tecnica: diccionario de
# frecuencias y se toma el maximo. O(n) tiempo, O(n) memoria. El algoritmo de Boyer-Moore lo
# hace con O(1) de memoria: se lleva un candidato y un contador, se suma si coincide y se resta
# si no; cuando llega a 0 se cambia de candidato. Vale la pena conocerlo, aparece en maraton.

class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        l = {}
        for i in range(len(nums)):
            if (nums[i] in l):
                l[nums[i]]+=1
            else:
                l[nums[i]]=1
        mas = 0
        v = 0
        for i,j in l.items():
            if(j > mas):
                mas = j
                v = i
        
        return v
        