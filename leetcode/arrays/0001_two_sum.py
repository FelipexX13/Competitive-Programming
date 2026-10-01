# <3
# Tema: LeetCode Hub / Fuerza Bruta O(n^2)
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1 "Two Sum": los indices de los dos numeros que suman target. Tecnica: dos ciclos
# anidados probando todas las parejas. La version buena es un diccionario valor -> indice en una
# sola pasada: para cada numero se pregunta si target - numero ya se vio. Eso es O(n) y es el
# patron que hay que tener de memoria.

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for i in range(len(nums)):
            for j in range(len(nums)):
                if((nums[i]+nums[j])==target and i!=j):
                    return [i, j]