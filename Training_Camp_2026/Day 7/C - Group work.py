# <3
# Tema: Math / Combinatorics
# Resuelve "Group work": dada una clase de N estudiantes, cuenta cuantos grupos distintos de al
# menos 2 estudiantes se pueden formar (dos grupos son distintos si difieren en al menos un
# estudiante).
# La respuesta es la suma de combinaciones C(n,m) para m=2..n (equivalente a 2^n menos los
# subconjuntos de tamano 0 y 1); el codigo usa math.comb para sumar directamente esas
# combinaciones.

import math
n = int(input())

suma = 0
for m in range(2,n+1):
    suma+=math.comb(n,m)
print(suma)
