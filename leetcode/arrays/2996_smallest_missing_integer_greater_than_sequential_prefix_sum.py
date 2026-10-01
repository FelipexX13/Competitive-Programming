# <3
# Tema: LeetCode Hub / Prefijo Secuencial
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n + respuesta)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2996 "Smallest Missing Integer Greater Than Sequential Prefix Sum": se suma el
# prefijo mas largo donde cada numero es el anterior mas 1, y se busca el menor entero ausente
# que sea al menos esa suma. Tecnica: una pasada para medir el prefijo secuencial y sumar, y
# despues subir de uno en uno hasta encontrar un valor que no este en el set. OJO: deja un
# print(c).

class Solution:
    def missingInteger(self, nums: List[int]) -> int:
        c = [nums[0]]
        v = nums[0]
        i = 1
        while i<len(nums):
            if(nums[i]-1 == nums[i-1]):
                v += nums[i]
            else:
                c.append(v)
                break
            i+=1
        c.append(v)
        print(c)
        mas = max(c)
        k = set(nums)
        while True:
            if(mas not in k):
                return mas
            mas += 1

        