# <3
# Tema: Geometry / Bounding Box de una Elipse Rotada
# Resumen: Dados los dos focos de una elipse y el largo a de la cuerda
# O: (1), formulas de la elipse rotada
# Detalle: Resuelve "Eclipse" (RPC 2026-07, problema E): dados los dos focos de una elipse y el
# largo a de la cuerda, dar el rectangulo mas pequeno (alineado a los ejes) que la contiene.
# Tecnica: de la definicion de elipse, el semieje mayor es A = a/2 y la distancia del centro a
# cada foco es c = d/2, asi que el semieje menor sale de B = raiz(A^2 - c^2). El centro es el
# punto medio de los focos. La parte que vale: la elipse esta ROTADA (el eje mayor va en la
# direccion de un foco al otro), y la extension en X de una elipse rotada es raiz((A*ux)^2 +
# (B*vx)^2), donde u es el vector unitario del eje mayor y v el perpendicular. Igual para Y. Es
# la formula del bounding box de una elipse en cualquier orientacion, y no es obvia si uno no la
# ha visto.

import math

x1, y1, x2, y2, a = map(int, input().split())

# Distancia entre los focos
d = ((x2 - x1)**2 + (y2 - y1)**2)**(1/2)

# Semieje mayor
A = a / 2

# Distancia del centro a cada foco
c = d / 2

# Semieje menor
B = math.sqrt(A * A - c * c)

# Centro
cx = (x1 + x2) / 2
cy = (y1 + y2) / 2

# Direccion del eje mayor
ux = (x2 - x1) / d
uy = (y2 - y1) / d

# Direccion perpendicular
vx = -uy
vy = ux

# Extension en X
rx = math.sqrt((A * ux) ** 2 + (B * vx) ** 2)

# Extension en Y
ry = math.sqrt((A * uy) ** 2 + (B * vy) ** 2)

print(cx - rx, cy - ry, cx + rx, cy + ry)
