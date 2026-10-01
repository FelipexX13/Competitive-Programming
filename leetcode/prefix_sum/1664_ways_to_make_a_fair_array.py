# <3
# Tema: LeetCode Hub / Prefijos Pares e Impares por Separado
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1664 "Ways to Make a Fair Array": cuantos indices se pueden borrar para que la suma
# de posiciones pares quede igual a la de impares. Tecnica: DOS arreglos de prefijos, uno de las
# posiciones pares y otro de las impares. Al borrar un indice, todo lo que esta a la derecha
# CAMBIA de paridad, asi que la suma par nueva es (par hasta i) + (impar desde i+1 hasta el
# final). Ese cruce es todo el problema.

class Solution:
    def waysToMakeFair(self, nums: List[int]) -> int:
        par = [0]
        sumap = 0
        impar = [0]
        sumai = 0
        for i in range(len(nums)):
            if(i%2==0):
                sumap += nums[i]
            else: 
                sumai += nums[i]
            par.append(sumap)
            impar.append(sumai)
        van = 0
        for i in range(len(nums)):
            sumap = par[i] + impar[-1] - impar[i+1]
            sumai = impar[i] + par[-1] - par[i+1]
            if(sumap == sumai):
                van += 1
        return van

        