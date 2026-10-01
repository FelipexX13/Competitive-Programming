# <3
# Tema: LeetCode Hub / Paridad con el Menor Impar
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3876 "Construct Uniform Parity Array II": lo mismo que el 3875 pero con arreglos
# grandes. Tecnica: solo hacen falta el menor par y el menor IMPAR del arreglo. Para volver
# impar un numero par basta restarle el menor impar, y eso solo se puede si el resultado sigue
# siendo positivo, de ahi el i - menor_impar >= 1. Dos pasadas lineales en vez de los pares del
# 3875. Quedarse con el minimo de cada paridad es lo que convierte el O(n^2) en O(n).

class Solution:
    def uniformArray(self, nums1: list[int]) -> bool:
        menor_par = float('inf')
        posP = 0
        menor_impar = float('inf')
        posI = 0
        pos = 0
        for x in nums1:
            if x % 2 == 0:
                if(menor_par > x):
                    menor_par = x
                    posP = pos
            else:
                if(menor_impar > x):
                    menor_impar = x
                    posI = pos
            pos+=1
        #if(menor_par == float('inf') or menor_impar == float('inf')):
        #    return False
        
        cp = 0
        ci = 0
        pos = 0
        for i in nums1:
            if(i %2 == 0):
                cp+=1
            elif(pos != posI and i-menor_impar >= 1):
                cp+=1

            if(i %2 == 1):
                ci+=1
            elif(pos != posI and i-menor_impar >= 1):
                ci+=1
            pos+=1

        if(ci == len(nums1) or cp == len(nums1)):
            return True

        return False