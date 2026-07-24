n,m = list(map(int,input().split()))
l = list(map(int,input().split()))
d1 = -1
d2 = -1
for i in range(len(l)):
    if(l[i]!= 0 and d1 == -1):
        d1 = i
    elif(l[i]!= 0 and d1 != -1):
        d2 = i
        break
if(d2 == -1):
    if(d1!= -1 and l[d1]>=m):
        for i in range(m):
            print(d1+1, end=" ")
    else:
        print(-1)
else:
    for i in range(m):
        if(i%2 == 0):
            print(d1+1, end=" ")
        else:
            print(d2+1, end=" ")
