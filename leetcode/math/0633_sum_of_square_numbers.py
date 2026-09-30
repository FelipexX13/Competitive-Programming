# <3
# Tema: LeetCode Hub / Dos Punteros sobre Cuadrados
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 633 "Sum of Square Numbers": decir si c se puede escribir como a^2 + b^2.
# Tecnica: se avanza a2 desde 0 y se baja b1 desde floor(sqrt(c)) al mismo tiempo, probando en
# cada paso si el complemento es un cuadrado perfecto. Es la idea de dos punteros desde los
# extremos, aunque escrita de forma poco obvia.
# La version clara: mientras a <= b, si a*a + b*b == c listo, si es menor sube a, si no baja b.

import math
class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        if(c == 0):
            return True
        b1 = math.floor(math.sqrt(c))
        for a2 in range(b1):
            a1 = math.floor(math.sqrt(c-(b1*b1)))
            b2 = math.floor(math.sqrt(c-(a2*a2)))
            
            if(((a1*a1)+(b1*b1)) == c):
                return True
            elif(((a2*a2)+(b2*b2)) == c):
                return True
            b1 -= 1
        return False
        