# <3
# Tema: Data Structures / Persistencia (DFS + Rollback)
# Resuelve "The Declaration of Independence" (Contest 05 [Avanzados], problema D): el documento
# empieza vacio (version 0) y cada query crea una nueva version a partir de otra version v ya
# existente: "E v x" copia la version v y agrega la oracion x al final, "D v" copia la version v
# y elimina la primera oracion; para cada query D hay que imprimir la oracion eliminada.
# Modela las versiones como un arbol (dicc[v] guarda los hijos que se crearon a partir de v) y
# recorre ese arbol con un DFS (funcion dfs) manteniendo un unico deque global "arr" que
# representa el documento actual; al entrar a un nodo aplica su operacion (append o popleft) y
# al salir la deshace (rollback), simulando asi todas las versiones sin copiar el documento.

import sys
from collections import deque


sys.setrecursionlimit(3*10**6)
n = int(input())
queries = []

dicc = {0: []}
deletes = []
for i in range(1, n+1):
    q = input().split(" ")
    kind = q[0]
    
    if kind == 'E':
        father = int(q[1])
        num = int(q[2])
        if father not in dicc:
            dicc[father] = [(i, num)]
        else:
            dicc[father].append((i, num))
    else:
        father = int(q[1])
        deletes.append(i)
        if father not in dicc:
            dicc[father] = [(i, kind)]
        else:
            dicc[father].append((i, kind))
arr = deque([])
res = [0] * (n + 1)
def dfs(currNode):
    global arr
    quitado = 0
    if currNode[1] == "D":
        if len(arr) > 0:
            quitado = arr.popleft()
    else:
        if currNode[1] != None:
            arr.append(currNode[1])
    res[currNode[0]] = quitado

    if currNode[0] in dicc:
        for son in dicc[currNode[0]]:
            dfs(son)
            
    if currNode[1] == "D":
        arr.appendleft(quitado)
    else:
        if len(arr) > 0:
            arr.pop()

dfs((0, None))

for i in deletes:
    print(res[i], end=" ")

    