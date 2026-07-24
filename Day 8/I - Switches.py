n,m = list(map(int,input().split()))
bomb = ["0"]*m
k = list(map(int,input().split()))
for i in range(1,len(k)):
    bomb[k[i]-1]="1"

q = bomb.count("0")
c = 0
if(q == m):
    print(0)
else:
    entrada = []
    pos = set()
    c = 0
    for j in range(n):
        #print(bomb)
        w = input().split()
        s = list(map(int,w))
        entrada.append(s)
        for i in range(1,len(s)):
            if(bomb[s[i]-1] == "0"):
                bomb[s[i]-1] = "1"
            else:
                bomb[s[i]-1] = "0"
        q = bomb.count("0")
        c += 1
        if(q == m):
            break
        pos.add(str("".join(bomb))+str(j))
        
    if(q == m):
        print(c)
    else:
        i = 0
        while True:
            #print(bomb)
            s = entrada[i]
            for j in range(1,len(s)):
                if(bomb[s[j]-1] == "0"):
                    bomb[s[j]-1] = "1"
                else:
                    bomb[s[j]-1] = "0"
            q = bomb.count("0")
            c += 1
            if(q == m):
                print(c)
                break
            inte = str("".join(bomb))+str(i)
            if(inte in pos):
                print(-1)
                break
            pos.add(str("".join(bomb))+str(i))

            i+=1
            if(i >= len(entrada)):
                i = 0
            
    
        
