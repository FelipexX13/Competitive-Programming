# <3
# Tema: LeetCode Hub / Repetir hasta Contener
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (|a|*|b|): se repite a hasta |b|/|a| + 5 veces y el 'in' cuesta
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 686 "Repeated String Match": cuantas veces hay que repetir a para que b quede
# adentro. Tecnica: repetir a mientras no contenga b. El limite len(b)//len(a) + 5 es la parte
# importante: si con esa cantidad no aparecio, ya nunca va a aparecer. En realidad bastan +2
# copias, una para cubrir el desfase inicial y otra el final. Sin ese limite el ciclo no termina
# cuando la respuesta es -1.

class Solution:
    def repeatedStringMatch(self, a: str, b: str) -> int:
        tam1 = len(a)
        tam2 = len(b)
        ne = tam2//tam1 + 5
        j = a
        n = 1
        while n<ne:
            if(b in j):
                return n
            n+=1
            j+=a
        return -1
        
        