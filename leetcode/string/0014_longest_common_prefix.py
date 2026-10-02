# <3
# Tema: LeetCode Hub / Prefijo Comun por Columnas
# Resumen: El prefijo comun mas largo de un arreglo de cadenas
# O: (n * largo del prefijo), comparando por columnas
# Detalle: LeetCode 14 "Longest Common Prefix": el prefijo comun mas largo de un arreglo de
# cadenas. Tecnica: comparar por COLUMNAS. Se mira la letra i de todas las palabras y en el
# primer desacuerdo se corta. El try/except cubre la palabra que se acaba antes.

class Solution(object):
    def longestCommonPrefix(self, strs):
        
        num = len(strs)
        pr = ""
        for i in range(len(strs[0])):
            l = strs[0][i]
            try:
                cont = 0
                for j in range(num):
                    if(strs[j][i] == l):
                        cont+=1
                if(cont==num):
                    pr+=l
                else:
                    break 
            except:
                break
        return (pr)


        """
        :type strs: List[str]
        :rtype: str
        """
        