# <3
# Tema: Constructive Algorithms / Hashing
# Resuelve "Handling the Blocks" (Training Camp 2026, Day 4 problema E): N bloques numerados
# 1..N tienen cada uno un color, y en cada turno se pueden intercambiar dos bloques que compartan
# color; hay que decidir si es posible ordenar la secuencia de forma ascendente por numero.
# Como los intercambios solo mueven numeros entre bloques del mismo color, la posicion i solo
# puede terminar con el numero (i+1) si ese numero pertenece al mismo color que el bloque
# originalmente ubicado en la posicion i; el codigo arma por color (lista l de sets) los numeros
# que comparten cada color y verifica esa condicion posicion por posicion.

n, k = list(map(int,input().split()))
l = []
for i in range(k):
    l.append(set())
val = []
for i in range(n):
    c, v = list(map(int,input().split()))
    l[v-1].add(c)
    val.append([c,v])


f = True    
for i in range(n):
    #h = val[i][0]
    if(i+1 in l[val[i][1]-1]):
        continue
    else:
        f = False
        break

if(f):
    print("Y")
else:
    print("N")

    

        
