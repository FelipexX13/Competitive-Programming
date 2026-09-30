# <3
# Tema: LeetCode Hub / Prefijos en un Set
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3043 "Find the Length of the Longest Common Prefix": el prefijo comun mas largo entre
# cualquier numero del primer arreglo y cualquiera del segundo.
# Tecnica: se meten TODOS los prefijos de los numeros del primer arreglo en un set y se busca cual
# aparece tambien en el set del segundo. Eso evita comparar todos los pares.
# OJO: compara con int(i) para quedarse con el mayor, pero lo que se busca es el mas LARGO. Con
# numeros de la misma cantidad de digitos coincide, pero el criterio correcto es len().
# Con un trie esto es el ejercicio natural, y sale mas claro.

class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:

        v1 = set()
        for i in arr1:
            k = str(i)
            l = ""
            for j in k:
                l += j
                v1.add(l) 
        v2 = set()
        for i in arr2:
            k = str(i)
            l = ""
            for j in k:
                l += j
                v2.add(l)
        v1 = sorted(v1)
        c = 0
        for i in v1:
            if(i in v2 and c<int(i)):
                c = int(i)

        if(c==0):
            return 0
        else:
            return len(str(c))
