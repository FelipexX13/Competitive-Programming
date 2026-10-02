# <3
# Tema: LeetCode Hub / Repetido y Faltante
# Resumen: En un arreglo de 1 a n, cual valor se duplico y cual falta
# O: (n log n) por el sort; con las sumas de Gauss seria (n)
# Detalle: LeetCode 645 "Set Mismatch": en un arreglo de 1 a n, cual valor se duplico y cual
# falta. Tecnica: ordenar y mirar los vecinos. Si dos son iguales, ese es el repetido; si la
# diferencia es mayor que 1, el faltante es el de la mitad. Los if del final cubren cuando falta
# el 1 o el n, que no tienen vecino de un lado. Sin ordenar tambien sale con las sumas: la suma
# real menos la de Gauss da repetido - faltante.

class Solution:
    def findErrorNums(self, nums: List[int]) -> List[int]:
        nums = sorted(nums)
        f = []
        r = 0
        fa = 0
        for i in range(1,len(nums)):
            if(nums[i]== nums[i-1]):
                r = nums[i]
            elif(nums[i]-1!= nums[i-1]):
                fa = nums[i]-1

        if(fa == 0):
            if(nums[0]== 1):
                fa = nums[i]+1
            else:
                fa = 1

        f = [r,fa]
        return f