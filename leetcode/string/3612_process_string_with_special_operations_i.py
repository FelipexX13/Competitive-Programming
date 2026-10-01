# <3
# Tema: LeetCode Hub / Simulacion de Operaciones
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3612 "Process String with Special Operations I": simular una cadena donde * borra el
# ultimo, # duplica todo y % invierte. Tecnica: simulacion directa sobre el string. Es O(n^2)
# porque duplicar e invertir copian todo. La version II no se puede simular (la cadena se vuelve
# gigantesca) y hay que ir AL REVES, rastreando de donde viene el caracter que se pide.

class Solution:
    def processStr(self, s: str) -> str:
        res = ""
        for i in s:
            if(i not in "*#%"):
                res += i
            elif(i == "*" and len(res) > 0):
                res = res[:-1]
            elif(i == "#"):
                res += res
            elif(i == "%"):
                res = res[::-1]
        return res