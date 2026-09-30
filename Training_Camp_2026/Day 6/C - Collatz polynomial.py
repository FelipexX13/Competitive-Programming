# <3
# Tema: Simulation / Ad Hoc
# Resuelve "Collatz polynomial" (Maratona SBC de Programacao 2025, Problem C): Aline crea una
# variante de la Conjetura de Collatz para polinomios con coeficientes 0 o 1. Si el polinomio
# tiene termino independiente, se multiplica por (x+1) y se le suma 1, descartando cualquier
# termino cuyo coeficiente resulte 2; si no tiene termino independiente, se divide entre x. Hay
# que contar cuantas operaciones hacen falta para llegar a P(x) = 1. El codigo simula el proceso
# literalmente sobre la lista "val" (coeficiente de x^i en la posicion i): hace val.pop(0) para
# dividir entre x, o construye una nueva lista "n" desplazando y sumando (multiplicacion por
# x+1, mas 1 en el termino independiente) y poniendo en 0 los coeficientes que dan 2, contando
# los pasos en "c" hasta que el polinomio quede reducido a 1.

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
    
