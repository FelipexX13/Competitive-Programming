# <3
# Tema: LeetCode Hub / Counting Sort
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 912 "Sort an Array": ordenar, sin usar el sort de la libreria. Tecnica: counting sort
# con diccionario de frecuencias y un barrido del minimo al maximo. Es O(n + rango), asi que
# solo conviene cuando el rango de valores es chico; aca los valores llegan a 5*10^4 y cabe. Con
# valores grandes y dispersos esto se vuelve lentisimo.

class Solution:
    def sortArray(self, nums: list[int]) -> list[int]:
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
        
        fin = [0]*len(nums)
        va = 0
        for i in range(mi,ma+1):
            try:
                c = dic[i]
                for j in range(c):
                    fin[va] = i
                    va += 1
            except:
                continue
        return fin