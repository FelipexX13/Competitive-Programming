# <3
# Tema: Simulation / Circular Queue
# Resuelve "Eeny Meeny" (Kattis): un grupo de ninios en circulo es dividido en dos equipos
# aplicando repetidamente una rima (como "eeny meeny miny moe"): se cuenta en sentido horario,
# saltando a los ninios ya elegidos, hasta la ultima palabra de la rima, que selecciona al
# siguiente ninio para el equipo actual, alternando de equipo en cada ronda. Pide reconstruir
# los dos equipos en el orden en que fueron elegidos. Simula la ronda con un indice `curr` que
# recorre circularmente la lista `people`, el conjunto `fuera` para saltar a los ya
# seleccionados, y un contador `currN` que cuenta palabras hasta llegar a `n` (longitud de la
# rima), alternando el equipo destino `group` cada vez que se elige a alguien.

n = input().split()

n = len(n)

k = int(input())

people = []

for i in range(k):
    nombre = input()
    people.append(nombre)

curr = 0
fuera = set()
group = 0
groups = [[], []]
curr = 0
currN = 0
while(len(fuera) != len(people)):
    if curr == k:
        curr = 0
    while curr in fuera:
        curr+=1
        if curr == k:
            curr = 0
    currN += 1
    if currN == n:
        groups[group].append(people[curr])
        fuera.add(curr)
        currN = 0
        if group == 1:
            group = 0
        else:
            group = 1
    curr += 1

for i in groups:
    print(len(i))
    for j in i:
        print(j)
