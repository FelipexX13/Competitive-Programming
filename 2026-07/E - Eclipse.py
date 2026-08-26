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

# Dirección del eje mayor
ux = (x2 - x1) / d
uy = (y2 - y1) / d

# Dirección perpendicular
vx = -uy
vy = ux

# Extensión en X
rx = math.sqrt((A * ux) ** 2 + (B * vx) ** 2)

# Extensión en Y
ry = math.sqrt((A * uy) ** 2 + (B * vy) ** 2)

print(cx - rx, cy - ry, cx + rx, cy + ry)
