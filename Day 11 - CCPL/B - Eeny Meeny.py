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
