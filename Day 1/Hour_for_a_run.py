import math

n,c = list(map(int, input().split()))

mult = c*n
res = ""
for i in range(1, 10):
    res += str(math.ceil((mult*i)/10))+" "
print(res)
