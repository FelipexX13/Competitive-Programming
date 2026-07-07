import math
n = int(input())
m = bin(n)[2:]
j = m.count("1")
print(2**j)
