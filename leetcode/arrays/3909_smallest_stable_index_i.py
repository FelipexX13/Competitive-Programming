# <3
# Tema: LeetCode Hub / Maximo por Prefijo y Minimo por Sufijo
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2) por el insert(0,...) de cada paso; con append y [::-1] seria (n)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3909 "Smallest Stable Index I": la version chica del 3904. Tecnica: la misma, pero
# guardando los dos arreglos completos, maximos por prefijo y minimos por sufijo, y
# comparandolos posicion por posicion. Se lee mas facil que la version II. OJO: usa insert(0,
# ...) para llenar el arreglo de minimos, que es O(n) cada vez y deja el total en O(n^2). Con
# append y luego [::-1] queda lineal.

class Solution:
    def firstStableIndex(self, nums: list[int], k: int) -> int:
        mayor = 0
        mayores = []
        for i in nums:
            if i > mayor:
                mayor = i
            mayores.append(mayor)
        nums2 = nums[::-1]    
        menor = float('inf')
        menores = []
        for i in nums2:
            if i < menor:
                menor = i
            menores.insert(0, menor)
        
        for i in range(len(nums)):
            if(mayores[i]-menores[i] <= k):
                return i
        return -1
            
        