# <3
# Tema: LeetCode Hub / Observacion que Colapsa el Problema
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3760 "Maximum Substrings With Distinct Start": la mayor cantidad de subcadenas que se
# pueden escoger empezando todas con letras distintas.
# Tecnica: dos lineas, len(set(s)). Cada letra distinta puede ser el inicio de una subcadena y
# ninguna mas, asi que la respuesta es cuantas letras distintas hay.
# Buen recordatorio de leer bien antes de programar: la respuesta a veces es una sola expresion.

class Solution:
    def maxDistinct(self, s: str) -> int:
        h = set(s)
        return (len(h))