# <3
# Tema: LeetCode Hub / Fuerza Bruta
# Resumen: El menor numero mayor o igual que n cuyo producto de digitos sea multiplo de t
# O: (respuesta - n) * digitos; con los limites del problema la respuesta esta cerca
# Detalle: LeetCode 3345 "Smallest Divisible Digit Product I": el menor numero mayor o igual que
# n cuyo producto de digitos sea multiplo de t. Tecnica: probar n, n+1, n+2, ... calculando
# math.prod de los digitos. Con los limites del problema (t hasta 10) la respuesta esta muy
# cerca, asi que la fuerza bruta alcanza. Sirve de recordatorio de math.prod, que ahorra
# escribir el ciclo del producto.

import math
class Solution:
    def smallestNumber(self, n: int, t: int) -> int:
        while True:
            s = str(n)
            u = math.prod(list(map(int,s)))
            if(u%t == 0):
                break
            n += 1
        return n


        