# <3
# Tema: Ad-hoc / Simulation
# Resuelve "Enigma of the Jewelry Case" (Maratona SBC de Programacao 2024, Problem E): la
# princesa de Nlogonia tenia una caja NxN donde los valores crecen estrictamente por fila y por
# columna (de izquierda a derecha y de arriba a abajo); su hermana roto la caja 90 grados en
# sentido horario un numero desconocido de veces (0 a 3), y hay que hallar el minimo numero de
# rotaciones antihorarias necesarias para devolverla a su estado original.
# Como en el arreglo original el valor minimo siempre esta en la esquina superior izquierda, el
# codigo solo necesita mirar las 4 esquinas de la matriz recibida (pos), encontrar cual de ellas
# tiene el valor minimo (me = min(pos)) y su indice dentro de esa lista indica directamente,
# por la simetria de la rotacion, cuantas rotaciones antihorarias hacen falta.

n = int(input())
matrix = []
for i in range(n):
    matrix.append(list(map(int,input().split())))
pos = [matrix[0][0], matrix[0][n-1], matrix[n-1][n-1], matrix[n-1][0]]
me = min(pos)
print(pos.index(me))
