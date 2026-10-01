# <3
# Tema: Math / Paridad
# Resumen: NO ES MIO: codigo de Stiven Correa, del repo del equipo (carpeta RPC/)
# O: (n)
# Detalle: NO ES MIO: codigo de Stiven Correa, del repo del equipo (carpeta RPC/). Resuelve
# "Call" (RPC 2026-07, problema C): contar cuantos de los n valores son impares. Tecnica: r % 2
# devuelve 1 si es impar y 0 si es par, asi que se suma directo sin ningun if.

n = int(input())

res = 0
for _ in range(n):
    r = int(input())
    res += r%2
print(res)
