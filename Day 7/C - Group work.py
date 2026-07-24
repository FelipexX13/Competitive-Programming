import math
n = int(input())

suma = 0
for m in range(2,n+1):
    suma+=math.comb(n,m)
print(suma)
