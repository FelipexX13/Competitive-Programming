# <3
# Tema: Implementation / Arreglos
# Resuelve "Buffoon" (Maratona de Programacao da SBC 2019, Day 1 problem B): en la eleccion del
# bufon de la corte, N candidatos reciben votos y gana el mas votado, rompiendo empates a favor
# de quien se registro primero. Carlos se aseguro de ser el primero en registrarse, asi que basta
# comparar si sus votos (primer valor de la lista) son iguales al maximo del arreglo para saber
# si gano ("S") o no ("N").

n = int(input())
l = []
for i in range(n):
    l.append(int(input()))

ma = max(l)
if(ma == l[0]):
    print("S")
else:
    print("N")
