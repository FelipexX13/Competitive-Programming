# <3
# Tema: LeetCode Hub / Orden de Primera y Ultima Aparicion
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3121 "Count the Number of Special Characters II": igual que la I, pero exigiendo que la
# ULTIMA minuscula aparezca antes de la PRIMERA mayuscula.
# Tecnica: un barrido con varios sets (l, u, esta, ya) que va sumando cuando encuentra la mayuscula
# despues de la minuscula y RESTANDO si despues vuelve a aparecer la minuscula, que romperia el
# orden. Ese descuento es el corazon del problema.
# Sale mas claro guardando ultima posicion de la minuscula y primera de la mayuscula y comparando.

class Solution:
    def numberOfSpecialChars(self, word: str) -> int:
        l = set()
        u = set()
        c = 0
        esta = set()
        ya = set()
        for i in word:
            if(i.islower() and i not in l):
                l.add(i)
            elif(i in esta and i not in ya):
                c-=1
                ya.add(i)
            elif(i.isupper() and i.lower() in l and i not in u):
                c+=1
                esta.add(i.lower())
            if(i.isupper()):
                u.add(i)
        return c