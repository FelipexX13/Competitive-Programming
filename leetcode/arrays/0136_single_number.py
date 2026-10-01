# <3
# Tema: LeetCode Hub / El que Aparece Una Vez
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 136 "Single Number": el unico elemento que no esta repetido. Tecnica: diccionario de
# frecuencias y se busca el que da 1. El truco elegante es el XOR de todo el arreglo: a ^ a = 0,
# asi que los pares se cancelan y queda el impar. Es O(1) de memoria y una sola linea; ese es el
# que piden.

class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        dic = {}
        for i in nums:
            if(i in dic):
                dic[i]+=1
            else:
                dic[i] = 1
        for clave,val in dic.items():
            if(val == 1):
                return clave
        