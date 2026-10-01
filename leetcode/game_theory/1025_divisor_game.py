# <3
# Tema: LeetCode Hub / Paridad
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1025 "Divisor Game": se resta un divisor propio de n y pierde quien no puede mover.
# Tecnica: con n par siempre se puede restar 1 y dejarle un impar al rival; con n impar todos
# los divisores son impares y toca dejarle un par. Asi que gana el primero si n es par.

class Solution:
    def divisorGame(self, n: int) -> bool:
        if(n%2 == 0):
            return True
        else:
            return False