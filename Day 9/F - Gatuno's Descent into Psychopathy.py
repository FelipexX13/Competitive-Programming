import math
n = int(input())

for _ in range(n):
    h, o, r = list(map(int, input().split()))
    
    r = (r-1)/r
    
    print(math.ceil(math.log(o/h, r)))