grado = int(input())
val = list(reversed(list(map(int,input().split()))))

m = [1, 1]
c = 0
while val.count(1) > 1 or val[0] != 1:
    #print(val)
    if(val[0] == 1):
        n = [0] * len(val)
        for i in range (len(val)):
            if(val[i]==0):
                continue
            for j in range(len(m)):
                try:
                    n[i+j]+=1
                except:
                    n.append(1)
        n[0]+=1
        for i in range (len(val)):
            if(n[i]>=2):
                n[i]=0
        val = n
    else:
        val.pop(0)
    #if(c==5):
    #    break
    c+= 1
print(c)
    
