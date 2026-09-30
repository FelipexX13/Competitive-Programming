# <3
# Tema: Math / Logaritmos
# Resuelve "Gatuno's Descent into Psychopathy": el corazon de Gatuno de
# tamano H1 se reduce con cada mordida segun H_n = H1 * ((B-1)/B)^n, donde B
# es el "factor de brutalidad"; se pide el minimo numero de mordidas n para
# que H_n sea menor o igual a H2. Despeja n algebraicamente tomando logaritmo
# en base r = (B-1)/B de la razon H2/H1 (o/h en el codigo) con
# math.log(o/h, r), y redondea hacia arriba con math.ceil para obtener el
# minimo entero de mordidas que cumple la condicion.

import math
n = int(input())

for _ in range(n):
    h, o, r = list(map(int, input().split()))
    
    r = (r-1)/r
    
    print(math.ceil(math.log(o/h, r)))