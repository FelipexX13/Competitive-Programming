# <3
# Tema: LeetCode Hub / Faltantes de 1 a n
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n) tiempo y memoria; se pedia (1) de memoria
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 448 "Find All Numbers Disappeared in an Array": los numeros de 1 a n que no aparecen.
# Tecnica: set con lo que hay y se recorre 1 a n preguntando. El problema tambien pide O(1) de
# memoria; el truco es marcar en el sitio poniendo negativo el valor de la posicion abs(v)-1, y
# al final las posiciones que quedaron positivas son las que faltan. Es el mismo truco del 41.

class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        num = set(nums)
        fal = []
        for i in range(1,len(nums)+1):
            if(i in num):
                continue
            fal.append(i)
        return fal
        