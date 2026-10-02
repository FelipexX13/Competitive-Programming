# <3
# Tema: LeetCode Hub / Ventana Deslizante con Set
# Resumen: La subcadena mas larga sin letras repetidas
# O: (n), cada letra entra y sale una vez
# Detalle: LeetCode 3 "Longest Substring Without Repeating Characters": la subcadena mas larga
# sin letras repetidas. Tecnica: dos punteros y un set con las letras de la ventana. Si la letra
# de la derecha ya esta, se encoge por la izquierda quitando del set; si no, se agrega y se
# estira. OJO: deja dos prints, y el clamp fin = len(s)-1 al final del ciclo es fragil; la
# version limpia recorre fin de 0 a n-1 y mueve ini con un while adentro.

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        ini = 0
        fin = 1
        resp = 0
        l = set()
        if(len(s)==0):
            return 0
        elif(len(s)==1):
            return 1
        l.add(s[ini])
        while(ini<len(s)):
            print(ini, fin)
            if(s[fin] in l):
                l.remove(s[ini])
                ini += 1
                continue
            l.add(s[fin])
            print(l)
            if(fin-ini > resp):
                resp = (fin-ini)
            fin += 1
            if(fin >= len(s)):
                fin = len(s)-1
        return resp+1