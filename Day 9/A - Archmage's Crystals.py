n = int(input())
l = list(map(int,input().split()))

suma = sum(l)
c = 0
for i in range(n,0,-1):
    if(suma%i == 0):
        break
    c+=1
print(c)
