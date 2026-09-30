# <3
# Tema: Math / Combinatorics
# Resuelve "Less Coin Tosses" (Maratona de Programacao da SBC 2019, Day 1 problem L): hay que
# repartir las 2^N cadenas binarias de longitud N entre Carla y Daniel de forma que la
# probabilidad de ganar sea igual sin importar el sesgo de la moneda, lo cual solo se logra
# emparejando equitativamente las cadenas dentro de cada nivel de peso de Hamming k (ya que P(s)
# depende solo de k), y pide el minimo numero de cadenas que quedan sin asignar. Por el teorema
# de Kummer, C(N,k) es impar solo cuando k es submascara de los bits de N, y hay exactamente
# 2^popcount(N) de esos k; por eso basta calcular 2 elevado a la cantidad de bits en 1 de N.

import math
n = int(input())
m = bin(n)[2:]
j = m.count("1")
print(2**j)
