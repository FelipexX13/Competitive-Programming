# <3
# Tema: LeetCode Hub / Suma Acumulada
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1732 "Find the Highest Altitude": la altitud maxima alcanzada, dados los desniveles.
# Tecnica: suma de prefijos arrancando en 0 y max() al final. El 0 inicial importa porque la
# respuesta puede ser el punto de partida si todos los tramos son de bajada.

class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        g = [0]
        for i in range(len(gain)):
            g.append(gain[i]+g[-1])
               
                
        return max(g)
        