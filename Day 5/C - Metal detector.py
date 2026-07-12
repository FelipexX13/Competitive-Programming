import math
t = int(input())
for i in range(t):
    n, p = list(map(int,input().split()))
    if(p%2 != 0):
        print(math.ceil(p/2))
        continue
    llevo = 0
    cual = 1
    q = n
    while True:
        if(cual == 1):
            if(p%2!=0):
                print(llevo + math.ceil(p/2))
                break
            a = math.ceil(n/2)
            llevo += a
            n = math.floor(n/2)
            p = math.floor(p/2)
        else:
            if(p%2!=1):
                print(llevo + math.ceil(p/2))
                break
            a = math.ceil(n/2)
            llevo += a
            n = math.floor(n/2)
            p = math.floor(p/2)
            
        if(q%2==0):
            cual = 1
        else:
            cual = 2
            
        q = n
        

