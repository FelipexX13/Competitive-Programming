# <3
# Tema: LeetCode Hub / Secuencia Autodescriptiva
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n), con el s += optimizado de CPython
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 481 "Magical String": la cadena de 1 y 2 donde los grupos de iguales tienen las
# longitudes que la cadena misma describe; contar los 1 entre los primeros n. Tecnica: se
# construye hacia adelante leyendo con un puntero chi la cantidad que toca escribir, y una
# bandera alterna si el bloque es de 1 o de 2. La cadena se va alimentando de si misma, y ese
# puntero que persigue al final es toda la idea. El if de i <= n es para no contar los 1 que se
# pasan del limite.

class Solution:
    def magicalString(self, n: int) -> int:
        chi = 2
        cant = 1
        s = "122"
        F = True
        i = 3
        while i < n:
            if(F):
                can = int(s[chi])
                chi+=1
                so = "1"*can
                s += so
                i += can
                if(i<=n):
                    cant += can
                else:
                    cant += 1
                F= False
            else:
                can = int(s[chi])
                chi+=1
                so = "2"*can
                s += so
                i += can
                F= True

        return cant
