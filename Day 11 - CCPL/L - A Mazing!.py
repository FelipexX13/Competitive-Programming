# <3
# Tema: Graph / DFS
# Resuelve "A Mazing!" (Kattis): un problema interactivo donde hay que explorar un laberinto de
# celdas cuadradas moviendose (up/down/left/right) segun las respuestas del juez ("wall", "ok",
# "solved"), sin conocer el mapa de antemano, hasta encontrar una salida o determinar que no
# existe ninguna (reportando "no way out"). Implementa un DFS iterativo sobre el grafo implicito
# de celdas: `todo` guarda por celda las direcciones aun no probadas (en un deque, excluyendo la
# direccion opuesta a la usada para entrar a esa celda) y `parent` guarda la celda predecesora;
# al agotar las direcciones de la celda actual, retrocede (backtrack) hacia su padre repitiendo
# el movimiento inverso, como una pila explicita de DFS.

import sys
from collections import deque

dirs = {
    "up": (0, 1),
    "down": (0, -1),
    "left": (-1, 0),
    "right": (1, 0),
}

opposite = {
    "up": "down",
    "down": "up",
    "left": "right",
    "right": "left",
}

curr = (0, 0)

todo = {
    curr: deque(["down", "right", "left", "up"])
}

parent = {}

while True:

    if todo[curr]:
        move = todo[curr].popleft()

        print(move, flush=True)
        ans = input()

        if ans == "solved" or ans == "wrong":
            break

        if ans == "wall":
            continue

        dx, dy = dirs[move]
        nxt = (curr[0] + dx, curr[1] + dy)

        if nxt not in todo:
            todo[nxt] = deque(["down", "right", "left", "up"])
            # Ya usamos la dirección opuesta para llegar aquí
            todo[nxt].remove(opposite[move])
            parent[nxt] = curr

        curr = nxt

    else:

        if curr == (0, 0):
            print("no way out", flush=True)
            ans = input()
            break

        par = parent[curr]

        dx = par[0] - curr[0]
        dy = par[1] - curr[1]

        if dx == 1:
            move = "right"
        elif dx == -1:
            move = "left"
        elif dy == 1:
            move = "up"
        else:
            move = "down"

        print(move, flush=True)
        ans = input()

        if ans == "solved" or ans == "wrong":
            break

        curr = par