# <3
# Tema: LeetCode Hub / Simulacion de Turnos
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3222 "Find the Winning Player in Coin Game": cada turno se toma una moneda de 75 y
# cuatro de 10, y pierde quien no alcanza a completar los 115.
# Tecnica: simular el turno mientras queden x >= 1 y y >= 4, alternando una bandera. Quien no
# puede mover pierde, asi que decide la paridad de la cantidad de turnos. Sale directo con
# min(x, y // 4) pero la simulacion es igual de valida.

class Solution:
    def winningPlayer(self, x: int, y: int) -> str:
        j = True
        while True:
            if(x>=1 and y>=4):
                x-=1
                y-=4
                j = not j
            else:
                break
        if(j):
            return "Bob"
        else:
            return "Alice"
        