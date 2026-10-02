# <3
# Tema: LeetCode Hub / Frecuencias con Letras Repetidas
# Resumen: Cuantas veces se puede armar la palabra balloon
# O: (n), contar cinco letras
# Detalle: LeetCode 1189 "Maximum Number of Balloons": cuantas veces se puede armar la palabra
# balloon. Tecnica: contar b, a, l, o, n y dividir entre lo que pide la palabra. La trampa es
# que la l y la o van DOS veces, asi que esas se dividen entre 2, y la respuesta es el minimo.
# Con Counter sale en dos lineas: min(cnt[c] // necesita[c]) sobre las cinco letras.

class Solution:
    def maxNumberOfBalloons(self, text: str) -> int:
        dic = {"b":0,"a":0,"l":0,"o":0,"n":0}
        for i in text:
            if(i in dic):
                dic[i] += 1
        lt = dic["l"]
        ot = dic["o"]
        mi = dic["b"]
        for cla, val in dic.items():
            if(val < mi):
                mi = val
        if (lt < 2 or ot < 2):
            return 0
        else:
            h = min(int(lt/2), int(ot/2))
            if(h == mi):
                return mi
            elif(h>mi):
                return mi
            else:
                return h
        