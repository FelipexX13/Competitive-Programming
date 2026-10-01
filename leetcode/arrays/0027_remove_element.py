# <3
# Tema: LeetCode Hub / Filtrar en el Sitio
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2): cada remove() recorre la lista
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 27 "Remove Element": quitar todas las apariciones de val y devolver cuantos quedaron.
# Tecnica: remove() en un while hasta que no quede ninguno, y despues rellena el final. OJO:
# rellena con el string "_" en un arreglo de enteros. Funciona porque el juez solo revisa los
# primeros k elementos, pero es un tipo mezclado. Lo limpio es el puntero de escritura: se
# recorre el arreglo y se copia hacia adelante solo lo que no es val.

class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        cont2 = 0
        cont = 0
        i = 0
        while i< len(nums):
            if(nums[i]==val):
                nums.remove(val)
                cont+=1
                continue
            cont2+=1
            i+=1
        i=0
        while i<cont:
            nums.append("_")
            i+=1
        
        return cont2