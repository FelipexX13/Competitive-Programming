# <3
# Tema: Data Structures / Hash Set
# Resuelve "Dangerous Dive" (Maratona de Programacao da SBC 2013, problem E): de N buzos
# voluntarios que fueron a una mision, se conocen los R que regresaron; hay que reportar, en
# orden ascendente, los identificadores de los que NO volvieron (o '*' si volvieron todos).
# Guarda los identificadores que regresaron en un set k para poder consultar pertenencia en
# O(1), recorre los identificadores de 1 a n y va concatenando a la salida los que no estan en
# k (es decir, los que faltan).

n, m = list(map(int,input().split()))
k = set(list(map(int,input().split())))
if(n == m):
    print("*")
fin = ""
for i in range(1,n+1):
    if(i not in k):
        fin+=(str(i)+" ")
print(fin)
