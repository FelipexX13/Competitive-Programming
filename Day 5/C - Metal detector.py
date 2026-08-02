# <3
# Tema: Math / Recursion (Simulacion tipo Josephus)
# Resuelve "Metal detector" (Contest 05 [Avanzados], problema C): en una fila de N personas,
# un detector defectuoso se activa en forma alternada (la persona 1 no lo activa, la 2 si, la 3
# no, y asi sucesivamente), cada persona que lo activa se manda al final de la fila, y para la
# persona que esta en la posicion i hay que hallar en que turno j finalmente pasara sin
# activarlo.
# Simula el proceso por rondas sin construir la fila explicita: la variable "cual" indica si en
# esta ronda pasan sin activar las posiciones pares o impares, acumula en "llevo" cuantas
# personas ya pasaron libres, y reduce n y p a la mitad (floor) para continuar con la sub-fila
# restante hasta que la posicion p caiga del lado que no activa el detector.

import math
t = int(input())
for i in range(t):
    n, p = list(map(int,input().split()))
    if(p%2 != 0):
        print(math.ceil(p/2))
        continue
    llevo = 0
    cual = 1
    q = n
    while True:
        if(cual == 1):
            if(p%2!=0):
                print(llevo + math.ceil(p/2))
                break
            a = math.ceil(n/2)
            llevo += a
            n = math.floor(n/2)
            p = math.floor(p/2)
        else:
            if(p%2!=1):
                print(llevo + math.ceil(p/2))
                break
            a = math.ceil(n/2)
            llevo += a
            n = math.floor(n/2)
            p = math.floor(p/2)
            
        if(q%2==0):
            cual = 1
        else:
            cual = 2
            
        q = n
        

