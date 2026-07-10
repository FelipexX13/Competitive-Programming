import sys
sys.setrecursionlimit(300000)

n, m = map(int, input().split())

matrix = [[] for _ in range(n)]
matrix2 = [[] for _ in range(n)]

for _ in range(m):
    p, s = map(int, input().split())
    p -= 1
    s -= 1

    matrix[p].append(s)
    matrix2[s].append(p)


visited = [False] * n
cam = []

def dfs(start):
    stack = [(start, 0)]
    visited[start] = True

    while stack:
        nodo, estado = stack[-1]

        if estado < len(matrix[nodo]):
            vecino = matrix[nodo][estado]
            stack[-1] = (nodo, estado + 1)

            if not visited[vecino]:
                visited[vecino] = True
                stack.append((vecino, 0))

        else:
            cam.append(nodo)
            stack.pop()


for i in range(n):
    if not visited[i]:
        dfs(i)


visited = [False] * n
respuesta = [0] * n

def dfs_gay(start, reino):
    stack = [start]
    visited[start] = True

    while stack:
        nodo = stack.pop()
        respuesta[nodo] = reino

        for vecino in matrix2[nodo]:
            if not visited[vecino]:
                visited[vecino] = True
                stack.append(vecino)


voy = 0

for i in reversed(cam):
    if not visited[i]:
        voy += 1
        dfs_gay(i, voy)


print(voy)
print(*respuesta)
