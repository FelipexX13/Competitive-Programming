# <3
# Tema: LeetCode Hub / Compresion de Coordenadas
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1331 "Rank Transform of an Array": reemplazar cada valor por su puesto en el orden.
# Tecnica: sorted(set(arr)) y un diccionario valor -> puesto. Eso es exactamente COMPRESION DE
# COORDENADAS, que es la herramienta para meter valores gigantes en un arreglo o un Fenwick.
# El notebook tiene la version en C++ (sort + unique + lower_bound).

class Solution:
    def arrayRankTransform(self, arr: List[int]) -> List[int]:
        k = sorted(list(set(arr)))
        dic = {}
        
        for i in range(len(k)):
            dic[k[i]] = i+1
        f = []
        for i in range(len(arr)):
            f.append(dic[arr[i]])
        return f
         