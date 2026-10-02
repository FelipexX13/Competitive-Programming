# <3
# Tema: Implementation / Maquina de Estados por Objeto
# Resumen: Una lista de pickup y putdown; decir si la secuencia es consistente
# O: (n), una maquina de estados por objeto
# Detalle: Resuelve "Fraud" (RPC 2026-07, problema F): una lista de pickup y putdown; decir si
# la secuencia es consistente, o sea que cada objeto se recoge una vez y se suelta una vez.
# Tecnica: un diccionario con el estado de cada objeto, 0 sin tocar, 1 recogido y 2 soltado. Un
# pickup solo vale desde 0 y un putdown solo desde 1. Al final se exige que TODOS hayan quedado
# en 2, que es el chequeo que se olvida: la secuencia puede ser valida paso a paso y dejar un
# objeto en la mano.

from collections import defaultdict

n = int(input())

state = defaultdict(int)
ans = 'yes'

for _ in range(n):
    inst, item = input().split()

    if inst == 'pickup':
        if state[item] != 0:
            ans = 'no'
            break
        state[item] = 1

    else:
        if state[item] != 1:
            ans = 'no'
            break
        state[item] = 2

if any(x != 2 for x in state.values()):
    ans = 'no'

print(ans)
