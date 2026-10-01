# <3
# Tema: LeetCode Hub / Ventana con Frecuencias
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3090 "Maximum Length Substring With Two Occurrences": la subcadena mas larga donde
# ninguna letra aparece mas de dos veces. Tecnica: el mismo molde del 2958 pero con k fijo en 2.
# Diccionario de frecuencias, y cuando una letra llega a 3 se encoge por la izquierda hasta que
# vuelva a 2.

class Solution:
    def maximumLengthSubstring(self, s: str) -> int:
        dic = {}
        inicio = 0
        fin = 0
        tam = []
        while fin < len(s):
            if(s[fin] not in dic):
                dic[s[fin]] = 1
            else:
                dic[s[fin]]+=1
            if(dic[s[fin]] > 2):
                tam.append(fin-inicio)
                while dic[s[fin]] > 2:
                    dic[s[inicio]]-=1
                    inicio += 1
            fin += 1
        if(len(tam)==0):
            return fin
        tam.append(fin-inicio)
        return max(tam)
        