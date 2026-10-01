# <3
# Tema: LeetCode Hub / Binaria sobre Monotonia
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 852 "Peak Index in a Mountain Array": la posicion del pico de un arreglo que sube y
# luego baja. Tecnica: binaria comparando con el vecino. Si arr[m] > arr[m+1] el pico esta en m
# o antes; si arr[m] > arr[m-1] esta en m o despues. No hace falta que el arreglo este ordenado,
# basta que la condicion sea monotona, y esa es la idea que se lleva uno. OJO: los dos if no son
# excluyentes y arr[mitad-1] con mitad = 0 lee el ultimo elemento (los indices negativos de
# Python no dan error). Con el arreglo del problema no falla, pero el invariante es fragil.

class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        ini = 0
        fin = len(arr)-1
        while ini < fin:
            mitad = (ini+fin)//2
            if(arr[mitad]>arr[mitad+1]):
                fin = mitad
            if(arr[mitad]>arr[mitad-1]):
                ini = mitad
        return mitad
            

        