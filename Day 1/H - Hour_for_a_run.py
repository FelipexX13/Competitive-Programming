# <3
# Tema: Math / Implementation
# Resuelve "Hour for a Run" (Maratona de Programacao da SBC 2019, Day 1 problem H): Vinicius
# corre V vueltas a una pista con N carteles igualmente espaciados y quiere saber, para cada
# decil (10%, 20%, ..., 90% del entrenamiento), cuantos carteles debe contar como minimo para
# garantizar que ya completo esa fraccion. Calcula ceil(V*N*i/10) para i de 1 a 9 e imprime los
# 9 valores.

import math

n,c = list(map(int, input().split()))

mult = c*n
res = ""
for i in range(1, 10):
    res += str(math.ceil((mult*i)/10))+" "
print(res)
