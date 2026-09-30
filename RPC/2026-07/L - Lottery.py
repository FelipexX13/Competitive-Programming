# <3
# Tema: Implementation / Umbral de Frecuencia
# NO ES MIO: codigo de Stiven Correa, del repo del equipo (carpeta RPC/).
# Resuelve "Lottery" (RPC 2026-07, problema L): de todos los numeros jugados, los que aparecen mas
# de 2n veces, en orden; -1 si no hay ninguno.
# Tecnica: diccionario de frecuencias y se agrega al resultado en el momento en que uno pasa el
# umbral, no al final. El set evita repetirlo si sigue apareciendo.
# El print(*res) desempaca la lista en argumentos y la imprime separada por espacios, que es la
# forma corta de sacar una lista en una sola linea en Python.

from collections import defaultdict
n = int(input())

dicc = defaultdict(int)
res = set()
total = 5*10*n
for _ in range(10*n):
    nums = list(map(int, input().split()))
    for i in nums:
        dicc[i] += 1
        if dicc[i] > 2*n:
            res.add(i)
res = sorted(list(res))
if len(res) == 0:
    print(-1)
else:
    print(*res)
