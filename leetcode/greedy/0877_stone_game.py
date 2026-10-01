# <3
# Tema: LeetCode Hub / Greedy que Acierta por Casualidad
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 877 "Stone Game": dos jugadores toman de los extremos de una fila de montones y gana
# quien junte mas piedras. Tecnica del codigo: ordena los montones y los reparte alternando de
# mayor a menor. OJO: eso NO es el juego, en el juego solo se puede tomar de los EXTREMOS. Pasa
# porque con una cantidad par de montones el primero siempre gana y la respuesta es True
# siempre, como dice el comentario del final. Sirve de ejemplo de que pasar no es lo mismo que
# estar bien.

class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        piles = sorted(piles)
        A = 0
        B = 0
        va = True
        i = len(piles)-1
        while i > -1:
            if(va):
                A += piles[i]
                va = not va
            else:
                B += piles[i]
                va = not va
            i-=1
        if(A > B):
            return True
        else:
            return False


        #return True always