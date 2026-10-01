# <3
# Tema: LeetCode Hub / Residuos de Prefijos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n), residuo de prefijo -> ultima posicion
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1590 "Make Sum Divisible by P": quitar el subarreglo mas corto para que lo que queda
# sea multiplo de p. Tecnica: si la suma total deja residuo f, el subarreglo que se quita tiene
# que dejar residuo f tambien. Con prefijos: se busca un residuo anterior igual a (suma_actual -
# f) mod p en un diccionario residuo -> ultima posicion. El (suma - f) % p en Python ya sale
# positivo. La condicion longitud < len(nums) es porque no se puede quitar todo el arreglo.

class Solution:
    def minSubarray(self, nums: List[int], p: int) -> int:
        j = sum(nums) 
        f = j % p
        if(j%p == 0):
            return 0
        dic = {0: -1} #esto es que ya encontro
        suma = 0
        g = []
        for pos in range(len(nums)):
            actual = nums[pos]
            suma += actual%p
            suma %= p #voy mirando cuanto me aporta cada numero
            
            n = (suma - f)%p #Esta ecuacion me dice cuanto hace falta para poder eliminarlo
            if(n in dic):
                longitud = pos - dic[n] 
                if longitud < len(nums): #El ejercicio dice que no puedo quitar todos los numeros
                    g.append(longitud)
            dic[suma] = pos
        
        if(len(g) == 0):
            return -1
        return min(g)

            

        
        
        
        