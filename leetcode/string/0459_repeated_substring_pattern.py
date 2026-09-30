# <3
# Tema: LeetCode Hub / Periodo de una Cadena
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 459 "Repeated Substring Pattern": decir si la cadena es un bloque repetido.
# Tecnica: probar cada largo de bloque de 1 hasta n/2 y verificar que la cadena entera sea ese
# bloque repetido. Es O(n^2) en el peor caso.
# El truco corto: la cadena es periodica si esta dentro de (s+s)[1:-1]. Y con KMP el periodo
# sale directo de la funcion de prefijo, n - pi[n-1], que es lo que esta en el notebook.

class Solution:
    def repeatedSubstringPattern(self, s: str) -> bool:
        if(len(s)==1):
            return False
        i = 1
        f = False
        while i<len(s)//2+1:
            pal = s[0:i]
            k = 0
            while k <len(s):
                try:
                    if(pal == s[k:k+i]):
                        k+=i
                        continue
                    else:
                        break
                except:
                    break
            if(k == len(s)):
                return True
            i+=1
        return False
        