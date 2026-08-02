# <3
# Tema: Math / Divisibilidad
# Resuelve "Archmage's Crystals" (Numeria): un archimago tiene n cristales con
# potencias a_i; cada hechizo de fusion toma dos cristales x,y y los reemplaza
# por uno de poder x+y, reduciendo la cantidad de cristales en 1. Se busca el
# minimo numero de hechizos para que el promedio de los cristales restantes sea
# un entero. La suma total nunca cambia con las fusiones, asi que solo hace
# falta hallar el mayor divisor i de la suma con i <= n (recorriendo i desde n
# hacia 1 con la variable c contando los intentos fallidos); la respuesta es
# n - i, es decir, la cantidad de fusiones necesarias para llegar a ese divisor.

n = int(input())
l = list(map(int,input().split()))

suma = sum(l)
c = 0
for i in range(n,0,-1):
    if(suma%i == 0):
        break
    c+=1
print(c)
