# <3
# Tema: Graph / Tree Reconstruction (BFS por capas)
# Resuelve "Expansion of the road network" (Maratona SBC de Programacao 2025, Problem E): el
# mapa actual de N ciudades y M caminos pudo haber surgido de un arbol original (un camino unico
# entre cada par de ciudades) al que se le agrego una carretera directa entre cada par de
# ciudades cuyo camino original pasaba por exactamente una ciudad intermedia (distancia 2 en el
# arbol). Hay que decidir si el mapa actual es consistente con ese proceso y, de serlo,
# reconstruir un arbol original valido (o imprimir "*" si es imposible). El codigo hace BFS desde
# el nodo 1 para ubicar una hoja candidata del arbol original (la de menor grado en la ultima
# capa), luego hace BFS desde esa hoja para obtener las capas "layer[]", identifica los posibles
# vertices "soporte" intersectando pares de padres de los nodos de profundidad >= 2, construye el
# arbol candidato asignando "parent[]" capa por capa segun la paridad de profundidad, y por
# ultimo "verify" comprueba que los caminos de distancia 1 y 2 de ese arbol coincidan exactamente
# con las M aristas dadas antes de imprimirlo.

import sys
from collections import deque

def solve(data):
    n = int(data[0]); m = int(data[1])
    B = n + 1
    adj = [[] for _ in range(B)]
    eset = set()
    ptr = 2
    for _ in range(m):
        a = int(data[ptr]); b = int(data[ptr + 1]); ptr += 2
        adj[a].append(b); adj[b].append(a)
        eset.add(a * B + b if a < b else b * B + a)

    # Grafo completo <=> el arbol original era una estrella
    if m == n * (n - 1) // 2:
        return '\n'.join('1 %d' % i for i in range(2, n + 1))

    def bfs(src):
        dist = [-1] * B
        dist[src] = 0
        q = deque([src])
        while q:
            u = q.popleft()
            du = dist[u] + 1
            for v in adj[u]:
                if dist[v] < 0:
                    dist[v] = du
                    q.append(v)
        return dist

    # 1) Hoja garantizada del arbol original:
    #    el de grado minimo dentro de la ultima capa BFS
    d1 = bfs(1)
    maxd = max(d1[1:])
    leaf = -1; best = float('inf')
    for v in range(1, n + 1):
        if d1[v] == maxd and len(adj[v]) < best:
            best = len(adj[v]); leaf = v

    # 2) Capas BFS desde la hoja: la capa k contiene las profundidades
    #    2k-2 y 2k-1 del arbol enraizado en el soporte de la hoja
    layer = bfs(leaf)
    inK = bytearray(B)
    for v in adj[leaf]:
        inK[v] = 1

    # 3) Candidatos a soporte: todo vertice externo con exactamente 2 vecinos
    #    dentro de N(hoja) es "nieto" del soporte y esos 2 vecinos son
    #    {soporte, su padre}. Interseccion de esos pares => <= 2 candidatos.
    cand = None
    for z in range(1, n + 1):
        if layer[z] >= 2:
            c = 0; p1 = 0; p2 = 0
            for y in adj[z]:
                if inK[y]:
                    c += 1
                    if c == 1: p1 = y
                    elif c == 2: p2 = y
                    else: break
            if c == 2:
                if cand is None:
                    cand = {p1, p2}
                else:
                    cand.intersection_update((p1, p2))
                    if not cand:
                        return '*'
    if not cand:
        return '*'

    maxl = max(layer[1:])
    layers = [[] for _ in range(maxl + 1)]
    for v in range(1, n + 1):
        layers[layer[v]].append(v)

    def build(w):
        parent = [0] * B
        role = bytearray(B)   # 1 = prof. par ("arriba"), 2 = prof. impar ("abajo")
        role[w] = 1
        parent[leaf] = w
        for v in layers[1]:
            if v != w:
                role[v] = 2
                parent[v] = w
        for k in range(2, maxl + 1):
            lows = []
            km1 = k - 1
            for x in layers[k]:
                c = 0; a = 0; b = 0
                for y in adj[x]:
                    if layer[y] == km1:
                        c += 1
                        if c == 1: a = y
                        elif c == 2: b = y
                        else: return None
                if c == 2:
                    ra = role[a]
                    if ra == role[b]: return None
                    if ra == 1: a, b = b, a
                    if parent[a] != b: return None   # el "arriba" debe ser el abuelo
                    role[x] = 1
                    parent[x] = a
                elif c == 1:
                    if role[a] != 2: return None     # unico vecino previo = abuelo
                    role[x] = 2
                    lows.append((x, a))
                else:
                    return None
            for x, g in lows:
                p = 0
                for y in adj[x]:
                    if layer[y] == k and role[y] == 1 and parent[y] == g:
                        p = y; break
                if not p: return None
                parent[x] = p
        return parent

    def verify(parent, root):
        degT = [0] * B
        for v in range(1, n + 1):
            if v != root:
                degT[v] += 1
                degT[parent[v]] += 1
        extra = m - (n - 1)
        s = 0
        for v in range(1, n + 1):
            d = degT[v]
            s += d * (d - 1) // 2
            if s > extra: return False
        if s != extra: return False
        ch = [[] for _ in range(B)]
        for v in range(1, n + 1):
            if v != root:
                p = parent[v]
                ch[p].append(v)
                key = v * B + p if v < p else p * B + v
                if key not in eset: return False
        for v in range(1, n + 1):
            nb = ch[v]
            if v != root:
                nb = nb + [parent[v]]
            ln = len(nb)
            for i in range(ln - 1):
                x = nb[i]
                for j in range(i + 1, ln):
                    y = nb[j]
                    key = x * B + y if x < y else y * B + x
                    if key not in eset: return False
        return True

    for w in cand:
        parent = build(w)
        if parent is not None and verify(parent, w):
            out = []
            ap = out.append
            for v in range(1, n + 1):
                if v != w:
                    ap('%d %d' % (v, parent[v]))
            return '\n'.join(out)
    return '*'

def main():
    data = sys.stdin.buffer.read().split()
    sys.stdout.write(solve(data) + '\n')

if __name__ == '__main__':
    main()