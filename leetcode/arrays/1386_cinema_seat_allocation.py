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