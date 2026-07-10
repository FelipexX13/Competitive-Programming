import copy
import sys

sys.setrecursionlimit(3*10**6)
m = input().strip()
n = input().strip()

ns = []
def generateBins(s, i, objective):
    if i < 0:
        objective.append(int("".join(s), 2))
        return
    elif s[i] == "*":
        way = copy.copy(s)
        way[i] = "1"
        generateBins(way, i-1, objective)
        way = copy.copy(s)
        way[i] = "0"
        generateBins(way, i-1, objective)
    else:
        generateBins(s, i-1, objective)

generateBins(list(n), len(n)-1, ns)


L = len(m)
estrellas = [idx for idx, c in enumerate(m) if c == "*"]
base = int("".join("0" if c == "*" else c for c in m), 2)   # M con todos los * = 0
peso  = [1 << (L - 1 - idx) for idx in estrellas]           # lo que suma poner un 1 en ese *

def generateAndCheck(t, val):
    if t == len(estrellas):
        for k in ns:
            if k != 0 and val % k == 0:
                print(bin(val)[2:].zfill(L))   # una sola vez, ya con la longitud correcta
                sys.exit(0)
        return
    generateAndCheck(t + 1, val + peso[t])     # ese * = 1
    generateAndCheck(t + 1, val)               # ese * = 0

generateAndCheck(0, base)
print(-1)