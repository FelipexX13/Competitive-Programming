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