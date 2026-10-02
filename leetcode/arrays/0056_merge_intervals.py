# <3
# Tema: LeetCode Hub / Fusionar Intervalos
# Resumen: Unir los intervalos que se traslapan
# O: (n log n), manda el sort; el barrido es lineal
# Detalle: LeetCode 56 "Merge Intervals": unir los intervalos que se traslapan. Tecnica: ordenar
# por inicio y barrer con un intervalo abierto; si el siguiente empieza antes de que el actual
# termine, se estira el final al maximo, y si no, se cierra y se abre uno nuevo. Ordenar por
# inicio es lo que garantiza que solo hay que mirar el intervalo anterior. Es el molde de casi
# todos los problemas de intervalos.

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        a= sorted(intervals)
        final = []
        ini = a[0][0]
        fin = a[0][1]
        for i in a:
            if(ini == i[0] and fin == i[1]):
                continue
            else:
                if(i[0]>= ini and i[0]<= fin):
                    if(i[1]>fin):
                        fin = i[1]
                else:
                    final.append([ini,fin])
                    ini = i[0]
                    fin = i[1]
        final.append([ini,fin])
        return final