# <3
# Tema: LeetCode Hub / Pila de Parentesis
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n), una pila
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 20 "Valid Parentheses": decir si una cadena de (), [] y {} esta bien balanceada.
# Tecnica: pila. Al abrir se empuja un codigo (1, 2, 3) y al cerrar se exige que la cima sea el
# que corresponde. Al final la pila tiene que quedar vacia. El try/except cubre el caso de
# cerrar con la pila vacia, que es un cierre sin apertura. En el notebook esta la version en C++
# con las 13 variantes de este problema.

class Solution:
    def isValid(self, s: str) -> bool:
        cola = []

        for i in range(len(s)):
            try:
                if(s[i]== "("):
                    cola.append(1)
                elif(s[i]== "["):
                    cola.append(2)
                elif(s[i]== "{"):
                    cola.append(3)
                elif(s[i]== ")" and cola[len(cola)-1]==1):
                    cola.pop(len(cola)-1)
                elif(s[i]== "]"and cola[len(cola)-1]==2):
                    cola.pop(len(cola)-1)
                elif(s[i]== "}"and cola[len(cola)-1]==3):
                    cola.pop(len(cola)-1)
                elif(s[i]== ")"):
                    break
                elif(s[i]== "]"):
                    break
                elif(s[i]== "}"):
                    break
            except:
                return False
        if(len(cola)==0):
            return True
        else:
            return False
        