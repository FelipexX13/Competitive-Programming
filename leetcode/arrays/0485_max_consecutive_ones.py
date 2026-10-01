# <3
# Tema: LeetCode Hub / Racha Maxima
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 485 "Max Consecutive Ones": la racha mas larga de unos. Tecnica: un contador que se
# reinicia en cada cero. El if del final es porque si el arreglo termina en 1, la ultima racha
# nunca se comparo adentro del ciclo. Ese caso del final es el error clasico de todos los
# problemas de rachas.

class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        ma = 0
        co = 0
        for i in range(len(nums)):
            if(nums[i]==1):
                co += 1
            else:
                if(co>ma):
                    ma = co
                co = 0
        if(nums[-1]== 1 and co>ma):
            ma = co
        return ma