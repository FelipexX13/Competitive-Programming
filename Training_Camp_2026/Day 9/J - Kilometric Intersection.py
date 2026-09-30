# <3
# Tema: Math / Geometria 1D
# Resuelve "Kilometric Intersection": dados dos intervalos cerrados [a,b] y
# [c,d] sobre una recta (tramos de carretera en kilometros), se pide la
# longitud de su interseccion, siendo 0 si no se superponen o solo se tocan
# en un punto. Calcula el intervalo de interseccion tomando l = max(a,c) y
# r = min(b,d), e imprime max(0, r - l), que es exactamente la longitud del
# solapamiento (o 0 si l > r).

import sys

n = int(input())

for _ in range(n):
    a, b, c, d = map(int, input().split())

    l = max(a, c)
    r = min(b, d)

    print(max(0, r - l))