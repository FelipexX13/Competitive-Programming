# <3
# Tema: LeetCode Hub / Punto mas Cercano en un Rectangulo
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1401 "Circle and Rectangle Overlapping": decir si un circulo toca un rectangulo.
# Tecnica: el truco es el CLAMP. Se recorta el centro del circulo al rectangulo con max(x1,
# min(cx, x2)), lo que da el punto del rectangulo mas cercano al centro; si ese punto queda a
# distancia <= r, hay traslape. Dos lineas y cero casos especiales. Este clamp es muy
# reutilizable en geometria de cajas.

class Solution:
    def checkOverlap(self, r: int, cx: int, cy: int, x1: int, y1: int, x2: int, y2: int) -> bool:
        x = max(x1, min(cx, x2)) - cx
        y = max(y1, min(cy, y2)) - cy

        return x * x + y * y <= r * r
        