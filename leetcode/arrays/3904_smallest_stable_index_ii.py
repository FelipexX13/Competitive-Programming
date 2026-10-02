# <3
# Tema: LeetCode Hub / Maximo por Prefijo y Minimo por Sufijo
# Resumen: El primer indice donde (maximo del prefijo) menos (minimo del sufijo) no pasa de k
# O: (n) tiempo y memoria
# Detalle: LeetCode 3904 "Smallest Stable Index II": el primer indice donde (maximo del prefijo)
# menos (minimo del sufijo) no pasa de k. Tecnica: se precalcula el minimo de cada SUFIJO
# recorriendo de derecha a izquierda, y despues se barre de izquierda a derecha llevando el
# maximo del prefijo en una variable. Con eso cada indice se responde en O(1). Ese par
# prefijo-maximo / sufijo-minimo es una herramienta que aparece muchisimo. OJO: menores queda al
# reves (se lleno con append recorriendo hacia atras), de ahi el indice len(menores)-1-i, que es
# facil de equivocar.

class Solution:
    def firstStableIndex(self, nums: list[int], k: int) -> int:
        menor = float('inf')
        menores = []
        for i in range(len(nums)-1,-1,-1):
            if nums[i] < menor:
                menor = nums[i]
            menores.append(menor)

        mayor = 0
        for i in range(len(nums)):
            if nums[i] > mayor:
                mayor = nums[i]
            if(mayor-menores[len(menores)-1-i] <= k):
                return i
        return -1
            
        