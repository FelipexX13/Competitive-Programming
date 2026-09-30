# <3
# Tema: LeetCode Hub / Probar Todos los Pares
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3633 "Earliest Finish Time for Land and Water Rides I": hay que subirse a una atraccion
# de tierra y una de agua, en cualquier orden; minimizar cuando se termina.
# Tecnica: probar todas las parejas en los dos ordenes, O(n*m). Lo importante es el if: si al
# terminar la primera ya paso la hora de apertura de la segunda, se arranca de una; si no, hay que
# esperar. Ese max(hora de llegada, apertura) es el corazon del problema.
# Hay que probar los DOS ordenes porque tierra-agua y agua-tierra dan resultados distintos.

class Solution:
    def earliestFinishTime(self, landStartTime: List[int], landDuration: List[int], waterStartTime: List[int], waterDuration: List[int]) -> int:
        menor = 9999999999999999999999999999999
        c1 = menor
        c2 = menor
        for i in range(len(landStartTime)):
            for j in range(len(waterStartTime)):
                if(landStartTime[i]+landDuration[i]>waterStartTime[j]):
                    c1 = landStartTime[i]+landDuration[i]+waterDuration[j]
                else:
                    c1 = waterStartTime[j]+waterDuration[j]
                
                if(c1<menor):
                    menor = c1

        for i in range(len(waterStartTime)):
            for j in range(len(landStartTime)):
                if(waterStartTime[i]+waterDuration[i]>landStartTime[j]):
                    c2 = waterStartTime[i]+waterDuration[i]+landDuration[j]
                else:
                    c2 = landStartTime[j]+landDuration[j]
                if(c2<menor):
                    menor = c2


        return menor

        