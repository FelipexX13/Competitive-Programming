n, k = list(map(int,input().split()))
l = []
for i in range(k):
    l.append(set())
val = []
for i in range(n):
    c, v = list(map(int,input().split()))
    l[v-1].add(c)
    val.append([c,v])


f = True    
for i in range(n):
    #h = val[i][0]
    if(i+1 in l[val[i][1]-1]):
        continue
    else:
        f = False
        break

if(f):
    print("Y")
else:
    print("N")

    

        
