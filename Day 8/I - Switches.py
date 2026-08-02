# <3
# Tema: Simulation / Cycle Detection
# Resuelve "Switches": hay N interruptores que alternan (encienden/apagan) subconjuntos de M
# focos; el conserje los presiona en el orden fijo 1,2,...,N,1,2,... y se detiene apenas
# todos los focos quedan apagados a la vez; dado el estado inicial de los focos y los focos
# asociados a cada interruptor, hay que contar cuantas veces presiona interruptores hasta
# lograrlo, o -1 si con esa estrategia nunca se apagan todos a la vez.
# Simula presionando los interruptores en orden ciclico, y guarda en el set "pos" cada estado
# visto como (configuracion de focos + indice del interruptor); si ese mismo par
# (estado,interruptor) se repite antes de apagar todo, esta en un ciclo sin solucion y
# responde -1.

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
            
    
        
