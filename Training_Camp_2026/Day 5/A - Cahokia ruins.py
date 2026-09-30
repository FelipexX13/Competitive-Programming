# <3
# Tema: Math / Simulacion
# Resuelve "Cahokia ruins" (Contest 05 [Avanzados], problema A): al entrar a una sala
# rectangular H x W, las paredes este y oeste empiezan a moverse una hacia la otra a 1 m/s cada
# una; cada fila i tiene un ancho de pared (arreglos left y right en el codigo) medido desde su
# borde respectivo, y hay que calcular en cuanto tiempo chocan las paredes por primera vez.
# Para cada fila calcula el hueco libre restante, w - right[i] - left[i], y se queda con el
# minimo (variable mins), ya que esa fila es la que se cierra primero; como ambas paredes se
# acercan a 1 m/s, el tiempo de colision es ese hueco minimo dividido entre 2 (velocidad de
# cierre combinada).

h, w = list(map(int,input().split()))

left = list(map(int,input().split()))
right = list(map(int,input().split()))

mins = float("inf")
for i in range(len(right)):
    x = w - right[i]
    mins = min(mins, x-left[i])

if mins // 2 == mins / 2:
    print(int(mins/2))
else:
    print(mins/2)