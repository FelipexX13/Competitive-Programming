n = int(input())
l = []
for i in range(n):
    l.append(int(input()))

ma = max(l)
if(ma == l[0]):
    print("S")
else:
    print("N")
