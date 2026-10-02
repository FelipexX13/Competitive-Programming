# <3
# Tema: LeetCode Hub / Asignacion por Bloques de 8
# Resumen: Costo minimo de teclear la palabra, con 8 teclas disponibles y sin letras repetidas
# O: (n), orden de aparicion
# Detalle: LeetCode 3014 "Minimum Number of Pushes to Type Word I": costo minimo de teclear la
# palabra, con 8 teclas disponibles y sin letras repetidas. Tecnica: las primeras 8 letras
# distintas cuestan 1 pulsacion, las siguientes 8 cuestan 2, y asi. Se va asignando el costo en
# orden de aparicion porque en la version I cada letra aparece una sola vez y el orden no cambia
# nada.

class Solution:
    def minimumPushes(self, word: str) -> int:
        dic = {}
        c = 0
        t = 0
        va  = 1
        for i in word:
            if(i in dic):
                c+=dic[i]
            else:
                dic[i] = va
                c += va
            t+=1
            if(t==8):
                t= 0
                va +=1
        return c
        