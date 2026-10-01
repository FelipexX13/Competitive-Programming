# <3
# Tema: Greedy / Emparejar Extremos
# Resumen: NO ES MIO: codigo de Stiven Correa, del repo del equipo (carpeta RPC/)
# O: (n log n) por ordenar los diametros de cada eje
# Detalle: NO ES MIO: codigo de Stiven Correa, del repo del equipo (carpeta RPC/). Resuelve
# "Axles" (RPC 2026-07, problema A): las ruedas se agrupan por eje y en cada eje se emparejan de
# dos en dos; minimizar la suma de los desbalances. Tecnica: por cada eje se ordenan los
# diametros en un deque y se emparejan el MAS PEQUENO con el MAS GRANDE (popleft con pop), se
# sigue hacia el centro y se acumula log(mayor/menor). El logaritmo convierte el producto de
# razones en una suma, que es lo que se puede acumular en un solo acumulador sin desbordar ni
# perder precision.

from collections import defaultdict, deque
import math

dicc= defaultdict(list)

n = int(input())

for _ in range(n):
    s, c = map(int, input().split())
    dicc[s].append(c)


diccS = dict()
for key, val in dicc.items():
    diccS[key] = deque(sorted(dicc[key]))

res = 0
for key, val in diccS.items():
    while(len(val) > 1):
        a, b = val.popleft(), val.pop()
        res += math.log(max(a,b)/min(a,b))
print(res)
