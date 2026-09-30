from collections import deque
from heapq import heappush, heappop
from typing import List

class Solution:
    def minMoves(self, classroom: List[str], energy: int) -> int:
        filas = len(classroom)
        columnas = len(classroom[0])

        # ---------------------------------------------------------
        # 1. Encontrar S, L y R
        # ---------------------------------------------------------

        especiales = []
        inicio = -1
        posiciones_L = {}

        for i in range(filas):
            for j in range(columnas):

                tipo = classroom[i][j]

                if tipo == 'S':
                    inicio = len(especiales)
                    especiales.append((i, j, 'S'))

                elif tipo == 'L':
                    indice = len(posiciones_L)
                    posiciones_L[(i, j)] = indice
                    especiales.append((i, j, 'L'))

                elif tipo == 'R':
                    especiales.append((i, j, 'R'))

        cantidad_L = len(posiciones_L)

        if cantidad_L == 0:
            return 0

        # ---------------------------------------------------------
        # 2. Posición -> nodo
        # ---------------------------------------------------------

        indice_especial = {}

        for i, (x, y, tipo) in enumerate(especiales):
            indice_especial[(x, y)] = i

        cantidad_nodos = len(especiales)

        # ---------------------------------------------------------
        # 3. Construir grafo
        # ---------------------------------------------------------

        grafo = [[] for _ in range(cantidad_nodos)]

        movimientos = [
            (1, 0),
            (-1, 0),
            (0, 1),
            (0, -1)
        ]

        for nodo, (sx, sy, _) in enumerate(especiales):

            cola = deque()
            cola.append((sx, sy, 0))

            visitados = {(sx, sy)}

            while cola:

                x, y, distancia = cola.popleft()

                if distancia > 0 and (x, y) in indice_especial:

                    destino = indice_especial[(x, y)]

                    grafo[nodo].append(
                        (destino, distancia)
                    )

                    # IMPORTANTE:
                    #
                    # No seguimos atravesando el nodo especial.
                    #
                    # Si es R, Dijkstra debe encargarse de la
                    # recarga antes de continuar.
                    continue

                for dx, dy in movimientos:

                    nx = x + dx
                    ny = y + dy

                    if 0 <= nx < filas and 0 <= ny < columnas:

                        if (nx, ny) not in visitados:

                            if classroom[nx][ny] != 'X':

                                visitados.add((nx, ny))

                                cola.append(
                                    (nx, ny, distancia + 1)
                                )

        # ---------------------------------------------------------
        # 4. Bitmask
        # ---------------------------------------------------------

        objetivo = (1 << cantidad_L) - 1

        # ---------------------------------------------------------
        # 5. Dijkstra + estados dominados
        # ---------------------------------------------------------

        #
        # Estado:
        #
        # (pasos, nodo, energia, mask)
        #

        heap = [
            (0, inicio, energy, 0)
        ]

        #
        # Para cada (nodo, mask) guardamos estados:
        #
        # (pasos, energia)
        #
        # Solo mantenemos estados NO dominados.
        #
        # Un estado A domina a B si:
        #
        # A tiene <= pasos
        # A tiene >= energia
        #

        frontera = {}

        frontera[(inicio, 0)] = [
            (0, energy)
        ]

        while heap:

            pasos, nodo, energia_actual, mask = heappop(heap)

            clave = (nodo, mask)

            # -----------------------------------------------------
            # Comprobar si este estado fue dominado
            # -----------------------------------------------------

            dominado = False

            for pasos_viejos, energia_vieja in frontera.get(
                clave, []
            ):

                if pasos_viejos <= pasos and energia_vieja >= energia_actual:

                    if pasos_viejos < pasos or energia_vieja > energia_actual:
                        dominado = True
                        break

            if dominado:
                continue

            # -----------------------------------------------------
            # Todas las L
            # -----------------------------------------------------

            if mask == objetivo:
                return pasos

            # -----------------------------------------------------
            # Explorar vecinos
            # -----------------------------------------------------

            for siguiente, costo in grafo[nodo]:

                if costo > energia_actual:
                    continue

                nueva_energia = energia_actual - costo
                nuevo_mask = mask

                x, y, tipo = especiales[siguiente]

                # -------------------------------------------------
                # L
                # -------------------------------------------------

                if tipo == 'L':

                    indice_L = posiciones_L[(x, y)]

                    nuevo_mask |= 1 << indice_L

                # -------------------------------------------------
                # R
                # -------------------------------------------------

                elif tipo == 'R':

                    nueva_energia = energy

                nuevos_pasos = pasos + costo

                nueva_clave = (siguiente, nuevo_mask)

                # -------------------------------------------------
                # ¿El nuevo estado está dominado?
                # -------------------------------------------------

                estados = frontera.get(nueva_clave, [])

                dominado = False

                for pasos_viejos, energia_vieja in estados:

                    if (
                        pasos_viejos <= nuevos_pasos
                        and energia_vieja >= nueva_energia
                    ):
                        dominado = True
                        break

                if dominado:
                    continue

                # -------------------------------------------------
                # El nuevo estado elimina estados que él domina
                # -------------------------------------------------

                nuevos_estados = []

                for pasos_viejos, energia_vieja in estados:

                    if not (
                        nuevos_pasos <= pasos_viejos
                        and nueva_energia >= energia_vieja
                    ):
                        nuevos_estados.append(
                            (pasos_viejos, energia_vieja)
                        )

                nuevos_estados.append(
                    (nuevos_pasos, nueva_energia)
                )

                frontera[nueva_clave] = nuevos_estados

                heappush(
                    heap,
                    (
                        nuevos_pasos,
                        siguiente,
                        nueva_energia,
                        nuevo_mask
                    )
                )

        return -1