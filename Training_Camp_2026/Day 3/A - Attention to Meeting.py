# <3
# Tema: Math / Ad-hoc
# Resuelve "Attention to the Meeting" (Maratona SBC de Programacao 2024, Problem A): Vinicius
# quiere saber la duracion maxima que puede tener cada uno de los N discursos de una reunion,
# sabiendo que todos duran lo mismo, que hay una pausa de 1 minuto entre discursos consecutivos,
# y que la reunion completa no debe superar K minutos.
# El problema se reduce a una simple desigualdad lineal: N*T + (N-1) <= K, asi que el codigo
# despeja T directamente con division entera, T = (K - (N-1)) // N, sin busqueda ni iteracion.

n = int(input())
t = int(input())

print((t - (n-1))//n)