# <3
# Tema: LeetCode Hub / Ordenar y Buscar
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3759 "Count Elements With At Least K Greater Values": cuantos elementos tienen al
# menos k elementos estrictamente mayores. Tecnica: ordenar y para cada posicion buscar con
# binaria el primer valor mayor que el actual; si desde ahi quedan k o mas, cuenta. El break
# cuando faltan k o menos elementos es la poda. Ordenado, tambien sale de un tiron: cuenta
# cuantos hay estrictamente mayores por frecuencias.

class Solution:
    def countElements(self, nums: List[int], k: int) -> int:
        if(k==0):
            return len(nums)
        nums.sort()
        contF = 0
        for i in range(len(nums)):
            cont=0
            if(len(nums)-i <= k):
                break
            else:
                j = i
                fi = len(nums)-1
                while j <= fi:
                    mitad = (j+fi)//2
                    if(nums[i]<nums[mitad]):
                        if(len(nums)-mitad >= k):
                            contF+=1  
                            break
                        else:
                            fi = mitad -1
                    else:
                        j = mitad + 1
        return contF 