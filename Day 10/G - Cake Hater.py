# <3
# Tema: Simulation / Brute Force
# Resuelve "Cake Hater": una receta de pastel con N pasos, cada uno con su propia lista
# de ingredientes; Antonio omite un conjunto fijo de B ingredientes que no le gustan
# (donts) de un total de A. El pastel se arruina en el primer paso donde faltan MAS de
# un tercio de sus ingredientes. Simula paso por paso: para cada paso cuenta cuantos de
# sus ingredientes estan en el set donts (counter) y compara contra ingreds[0]/3 (el
# tamano del paso); en cuanto counter supera ese umbral, imprime el indice del paso
# (i+1) y detiene la busqueda; si ningun paso lo supera, imprime -1.

n = int(input())

a, b = list(map(int, input().split()))

donts = set(map(int, input().split()))

sol = False
for i in range(n):
    ingreds = list(map(int, input().split()))
    
    counter = 0
    if not sol:
        for j in range(1, ingreds[0]+1):
            if ingreds[j] in donts:
                counter += 1
            if counter > ingreds[0]/3:
                print(i+1)
                sol = True
                break
if not sol:
    print(-1)