# <3
# Tema: LeetCode Hub / Posiciones Perdedoras
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (1), es n % 4 != 0
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 292 "Nim Game": se quitan 1, 2 o 3 piedras por turno y pierde quien no puede mover.
# Tecnica: quien recibe un multiplo de 4 pierde, porque el rival siempre puede completar 4 entre
# los dos turnos. Todo el problema es n % 4 != 0.

class Solution:
    def canWinNim(self, n: int) -> bool:
        if(n %4 == 0):
            return False
        else:
            return True
        