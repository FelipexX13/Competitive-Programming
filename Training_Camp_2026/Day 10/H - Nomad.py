# <3
# Tema: Greedy / Constructive Algorithms
# Resuelve "Nomad": Kai debe dormir exactamente D noches alternando entre N lugares,
# cada uno con un limite d_i de dias CONSECUTIVOS que tolera antes de expulsarlo; hay
# que construir un plan de D dias que nunca exceda ningun limite, o reportar -1 si es
# imposible. Busca los primeros dos indices d1, d2 con tolerancia distinta de cero: si
# hay al menos dos lugares utilizables, alterna entre ellos (d1+1, d2+1, d1+1, ...)
# durante los D dias, lo que garantiza como maximo 1 dia consecutivo en cada uno y por
# lo tanto siempre respeta cualquier limite >= 1. Si solo hay un lugar utilizable, la
# unica opcion es quedarse fijo ahi todos los D dias, lo cual solo es valido si su
# tolerancia l[d1] alcanza para cubrir los D dias consecutivos; en cualquier otro caso
# (ningun lugar utilizable, o el unico disponible no aguanta los D dias) imprime -1.

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
