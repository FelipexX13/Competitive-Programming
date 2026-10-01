# <3
# Tema: LeetCode Hub / Grupos de Sillas por Fila
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (r log r) con r reservas; NO depende de n, que llega a 10^9
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1386 "Cinema Seat Allocation": maximo de familias de 4 que se pueden sentar juntas,
# con algunas sillas reservadas. Tecnica: en cada fila solo hay tres bloques posibles de 4
# sillas contiguas sin cruzar el pasillo, 2-5, 4-7 y 6-9, y los bloques 1 y 3 son los unicos que
# caben a la vez. Se revisa cada fila con reservas y las n - f filas vacias aportan 2 cada una.
# La clave es no recorrer las n filas (n llega a 10^9), solo las que aparecen en la lista.

class Solution:
    def maxNumberOfFamilies(self, n: int, reservedSeats: List[List[int]]) -> int:
        filas = {}
        for i in range(len(reservedSeats)):
            if(reservedSeats[i][0] in filas):
                filas[reservedSeats[i][0]].append(reservedSeats[i][1])
            else:
                filas[reservedSeats[i][0]] = [reservedSeats[i][1]]
        set1 = {2,3,4,5}
        set2 = {4,5,6,7}
        set3 = {6,7,8,9}
        c = 0
        f = 0
        for clave,valor in filas.items():
            a = [1,1,1]
            for i in valor:
                if(i in set1):
                    a[0] = 0
                if(i in set2):
                    a[1] = 0
                if(i in set3):
                    a[2] = 0
            if(a[0]==1 and a[2]==1):
                c+=2
            else:
                c += min(1,sum(a))
            f+=1

        faltantes = n-f
        c+= 2*faltantes
        
        return c