# <3
# Tema: LeetCode Hub / Diferencia Minima en Ordenado
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1200 "Minimum Absolute Difference": todos los pares con la diferencia absoluta
# minima. Tecnica: ordenar. La diferencia minima SIEMPRE esta entre dos vecinos del arreglo
# ordenado, asi que basta una pasada para hallarla y otra para recolectar los pares que la
# alcanzan. Esa observacion es la que convierte un problema de pares (O(n^2)) en uno lineal.

class Solution:
    def minimumAbsDifference(self, arr: List[int]) -> List[List[int]]:
        a = sorted(arr)
        mi = float("inf")
        for i in range(1,len(arr)):
            if(a[i]-a[i-1] < mi):
                mi = a[i]-a[i-1]
        
        fin = []
        for i in range(1,len(arr)):
            if(a[i]-a[i-1] == mi):
                fin.append([a[i-1], a[i]])
        return fin

        