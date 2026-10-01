# <3
# Tema: LeetCode Hub / Dos Ventanas sin Traslape
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n log n) por ordenar los candidatos por donde terminan
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1477 "Find Two Non-overlapping Sub-arrays Each With Target Sum": dos subarreglos que
# sumen target cada uno y que juntos sean lo mas cortos posible. Tecnica: primero una ventana
# deslizante saca TODOS los subarreglos con suma target (los valores son positivos, por eso la
# ventana funciona). Despues se ordenan por donde terminan y con un puntero se va guardando el
# mas corto que termina ANTES de que empiece el actual. Ese mejor-hasta-ahora es lo que evita
# comparar todos los pares.

class Solution:
    def minSumOfLengths(self, arr: list[int], target: int) -> int:
        rango = {}
        c = []
        can = 0
        van = 0
        i = 0
        while i < len(arr):
            can += arr[i]
            van += 1
            if(can<=target):
                if(can == target):
                    if(can in rango):
                        rango[can].append([van, i-van+1,i])
                        c.append(van)
                    else:
                        rango[can] = [[van,i-van+1,i]]
                        c.append(van)
            else:
                voy = van
                for j in range(i-voy+1,i+1):
                    can -= arr[j]
                    van -= 1
                    if(can <= target):
                        break
                if(can == target):
                    if(can in rango):
                        rango[can].append([van,i-van+1,i])
                        c.append(van)
                    else:
                        rango[can] = [[van,i-van+1,i]]
                        c.append(van)
            i+=1
        if(len(c)<2):
            return -1
        l = sorted(rango[target], key=lambda x: x[2])

        mini = float("inf")
        mejor = float("inf")
        p = 0

        for actual in l:

            longitud, inicio, fin = actual

            while p < len(l) and l[p][2] < inicio:
                mejor = min(mejor, l[p][0])
                p += 1

            if mejor != float("inf"):
                mini = min(mini, longitud + mejor)
        if(mini==float("inf")):
            return -1
        return mini
                
        