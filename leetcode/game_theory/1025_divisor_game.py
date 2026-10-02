# <3
# Tema: LeetCode Hub / Paridad
# Resumen: Se resta un divisor propio de n y pierde quien no puede mover
# O: (1), es la paridad de n
# Detalle: LeetCode 1025 "Divisor Game": se resta un divisor propio de n y pierde quien no puede
# mover. Tecnica: con n par siempre se puede restar 1 y dejarle un impar al rival; con n impar
# todos los divisores son impares y toca dejarle un par. Asi que gana el primero si n es par.

class Solution:
    def divisorGame(self, n: int) -> bool:
        if(n%2 == 0):
            return True
        else:
            return False