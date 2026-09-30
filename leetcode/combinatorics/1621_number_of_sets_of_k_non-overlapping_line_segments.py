# <3
# Tema: LeetCode Hub / Stars and Bars
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1621 "Number of Sets of K Non-Overlapping Line Segments": cuantas formas hay de
# dibujar k segmentos que no se traslapen sobre n puntos.
# Tecnica: una sola linea, comb(n+k-1, 2k) mod 1e9+7. Sale de stars and bars: los 2k extremos
# de los segmentos se eligen entre n+k-1 posiciones porque dos segmentos SI pueden compartir
# un punto de borde, y ese k-1 extra es justo la holgura de los puntos compartidos.
# La leccion es que a veces la DP se vuelve un coeficiente binomial y nada mas.

class Solution:
    def numberOfSets(self, n: int, k: int) -> int:
        return math.comb(n+k-1,2*k)%(10**9+7)
        