# <3
# Tema: LeetCode Hub / Counting Sort Parcial
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 215 "Kth Largest Element in an Array": el k-esimo mas grande. Tecnica: frecuencias en
# un diccionario y barrido del maximo hacia abajo acumulando hasta pasar de k. Es O(n + rango).
# OJO: ma arranca en 0, asi que con todos los valores negativos el barrido empieza mal. Con los
# datos del problema no falla, pero el ma deberia inicializarse en -infinito. Con un heap de
# tamano k es O(n log k), y con quickselect O(n) promedio.

class Solution:
    def findKthLargest(self, nums: list[int], k: int) -> int:
        mi = float("inf")
        ma = 0
        dic = {}
        for i in nums:
            if(i>ma):
                ma = i
            if(i<mi):
                mi = i
            if(i in dic):
                dic[i]+=1
            else:
                dic[i]=1
        c = 0
        for i in range(ma,mi-1,-1):
            try:
                c += dic[i]
                if(c>=k):
                    break
            except:
                continue
        return i
        