# <3
# Tema: LeetCode Hub / Busqueda Binaria
# Resumen: Buscar un valor en un arreglo ordenado
# O: (log n), la plantilla de libro
# Detalle: LeetCode 704 "Binary Search": buscar un valor en un arreglo ordenado. Tecnica: la
# binaria de libro con ini <= fin y los saltos mitad+1 / mitad-1. Es la plantilla mas corta y la
# que hay que tener en la cabeza; los dos archivos anteriores son la version complicada del
# mismo esqueleto.

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        ini = 0
        fin = len(nums)-1
        while ini <= fin:
            mitad = (ini+fin)//2
            if(nums[mitad]==target):
                return mitad
            elif(nums[mitad]<target):
                ini = mitad+1
            else:
                fin = mitad-1
        return -1
        