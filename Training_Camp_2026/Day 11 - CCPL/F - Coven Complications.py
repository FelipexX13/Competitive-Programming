# <3
# Tema: Greedy / Sorting (Prefix Sums)
# Resuelve "Coven Complications" (Kattis): un grafo de n comunidades brujas unidas por m
# portales, donde las comunidades con f_i=0 son propias y las que tienen f_i>0 ferrets son
# rivales. Cada dia se sella una comunidad propia sin sellar, y ese dia todas las demas
# comunidades propias aun sin sellar pierden brujas iguales a la suma de ferrets de sus
# comunidades rivales vecinas directas; pide el minimo total de brujas perdidas hasta sellar
# todas las comunidades propias. Calcula para cada comunidad propia su perdida diaria fija
# (`citiesW`, suma de ferrets de los vecinos rivales via las aristas), y aplica la estrategia
# greedy clasica de minimizar sumas de tiempos de finalizacion: ordena esas perdidas de forma
# ascendente y suma las sumas prefijas (`pre`) salvo la ultima, sellando primero las comunidades
# con mayor perdida diaria.

n, c = list(map(int, input().split()))

hurones = list(map(int, input().split()))

citiesW = [0]*(n+1)
for i in range(c):
    a, b = list(map(int, input().split()))
    a, b = (hurones[a-1], a), (hurones[b-1], b)
    if a[0] == 0 or b[0] == 0:
        obj = min(a,b)
        citiesW[obj[1]] += max(a[0],b[0])
pre = []
citiesW.sort()
prev = 0
for i in citiesW:
    prev += i
    if i != 0: 
        pre.append(prev)

sol = 0
for i in range(len(pre)-1):
    sol += pre[i]
    
print(sol)