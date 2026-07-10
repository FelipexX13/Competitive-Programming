t, v, n = list(map(int,input().split()))
c = [0]
for i in range(n):
    c.append(int(input()))
c.append(v)

f = False
for i in range(len(c)-1):
    if(t <= abs(c[i]-c[i+1])):
        f = True
        break
if(f):
    print("Y")
else:
    print("N")

    