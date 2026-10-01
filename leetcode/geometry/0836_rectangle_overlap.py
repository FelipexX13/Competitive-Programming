# <3
# Tema: LeetCode Hub / Interseccion de Rectangulos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (1)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 836 "Rectangle Overlap": decir si dos rectangulos alineados a los ejes se traslapan
# en area. Tecnica: la interseccion de dos rectangulos es otro rectangulo, con ancho
# min(derechas) - max(izquierdas) y alto min(arribas) - max(abajos). Hay traslape si los dos
# salen positivos. Vale la pena aprenderselo asi, sin listas de casos.

class Solution:
    def isRectangleOverlap(self, rec1: List[int], rec2: List[int]) -> bool:
        ancho = min(rec1[2], rec2[2]) - max(rec1[0], rec2[0])
        alto = min(rec1[3], rec2[3]) - max(rec1[1], rec2[1])

        return ancho > 0 and alto > 0