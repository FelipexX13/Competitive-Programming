# <3
# Tema: LeetCode Hub / Fijar el Mejor Primero
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3635 "Earliest Finish Time for Land and Water Rides II": lo mismo que el 3633, pero con
# arreglos grandes.
# Tecnica: no hace falta probar todos los pares. Para la primera atraccion solo interesa la que
# termina mas temprano (el minimo de inicio + duracion), porque llegar antes a la segunda nunca es
# peor. Con eso quedan dos barridos lineales, uno por cada orden.
# Esa reduccion de O(n*m) a O(n+m) es la diferencia entre la version I y la II.
# OJO: deja un print(val) adentro del ciclo.

class Solution:
    def earliestFinishTime(self, landStartTime: List[int], landDuration: List[int], waterStartTime: List[int], waterDuration: List[int]) -> int:
        res1 = [x + y for x, y in zip(landStartTime, landDuration)]
        res2 = [x + y for x, y in zip(waterStartTime, waterDuration)]

        men1 = min(res1)
        men2 = min(res2)

        f1 = 999999999999999999999
        f2 = 999999999999999999999
        for i in range(len(res2)):
            if(men1<waterStartTime[i]):
                val = men1+(waterStartTime[i]-men1)+waterDuration[i]
            else:
                val = men1+waterDuration[i]
            print(val)
            if(val<f1):
                f1 = val

        for i in range(len(res1)):
            if(men2<landStartTime[i]):
                val = men2+(landStartTime[i]-men2)+landDuration[i]
            else:
                val = men2+landDuration[i]
            if(val<f2):
                f2 = val

        if(f1<f2):
            return f1
        else:
            return f2