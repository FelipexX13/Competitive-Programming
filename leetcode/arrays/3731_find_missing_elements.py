# <3
# Tema: LeetCode Hub / Faltantes entre el Minimo y el Maximo
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n * rango) por el 'in' sobre la lista; con set seria (rango)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3731 "Find Missing Elements": los valores que faltan estrictamente entre el minimo y
# el maximo del arreglo. Tecnica: recorrer el rango preguntando si cada valor esta. OJO: usa if
# i in nums sobre la LISTA, que es O(n) cada vez, asi que el total es O(n*rango). Con set(nums)
# la consulta es O(1) y queda O(rango).

class Solution:
    def findMissingElements(self, nums: List[int]) -> List[int]:
        mi = min(nums)
        ma = max(nums)
        fal = []
        for i in range(mi+1,ma):
            if(i in nums):
                continue
            fal.append(i)
        return fal
        